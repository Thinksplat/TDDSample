#include <gtest/gtest.h>
#include "tests/PinballProfile.h"
#include "tests/Sim.h"
#include "lib/PinballApp.h"
#include "tests/WalkingTime.h"
#include "tests/MockIntegerConsumer.h"
#include "tests/MockBoolean.h"
#include "tests/MockIntegerConsumerLambda.h"
#include "lib/TimeTimer.h"
#include "interface/IBSP.h"

// Kind of a heavy-weight testing framework to create an
// entire simulated BSP.  This will create a known profile
// and validate that the entire Pinball App runs as expected.

class TestBSP : public IBSP
{
public:
    static const int stable_time = 20 * 1000;
    TestBSP(IIntegerConsumer &consumer)
        : consumer(consumer), sim(time),
          time(10),                         // increment time by 10 microseconds each step
          keeprunning(Time(), 1000000 * 10) // run for 10 seconds
    {
        // Setup a sample profile
        const int noise_time = 10;
        PinballProfile::GenPinball(sim,
                                   4 * 1000000, // 4 seconds in
                                   stable_time,
                                   stable_time,
                                   noise_time, 0xd, 0xe);
        // Create another 6 seconds in
        PinballProfile::GenPinball(sim,
                                   6 * 1000000, // 6 seconds in
                                   stable_time,
                                   stable_time,
                                   noise_time, 42 & 0xf, 42 >> 4);

        // Create another 6.5 seconds in
        PinballProfile::GenPinball(sim,
                                   6.5 * 1000000, // 6.5 seconds in
                                   stable_time,
                                   stable_time,
                                   noise_time, 99 & 0xf, 99 >> 4);
    }

    ITimeProvider &Time() override
    {
        return time;
    }

    // A timer that expires when we should stop running
    ITimer &RunningTimer() override
    {
        return keeprunning;
    }

    // LED for visible status if
    IBooleanConsumer &LED() override
    {
        return led;
    }

    // Where the data is sent to
    IIntegerConsumer &Consumer() override
    {
        return consumer;
    }

    IBooleanProvider &Transmit() override
    {
        return sim.Lines().Transmit();
    }

    IBooleanProvider &Pin0() override
    {
        return sim.Lines().Data0();
    }

    IBooleanProvider &Pin1() override
    {
        return sim.Lines().Data1();
    }
    IBooleanProvider &Pin2() override
    {
        return sim.Lines().Data2();
    }
    IBooleanProvider &Pin3() override
    {
        return sim.Lines().Data3();
    }

private:
    IIntegerConsumer &consumer;
    Sim sim;
    WalkingTime time;
    TimeTimer keeprunning;
    MockBooleanConsumer led;
};

// We run the test once and then validate the recorded data.
// We might want to use TEST_F or TEST_P instead of TEST_E.
typedef std::tuple<ITimeProvider::TimeType, int> Record;
typedef std::vector<Record> Recording;
static Recording s_recording;

class RecordingTest : public ::testing::Test
{
protected:
    const ITimeProvider::TimeType one_second = 1000000;
    const int stable_time = TestBSP::stable_time;

    void SetUp() override
    {
        // Use a previous recording if it exists
        if (s_recording.size() > 0)
        {
            recording = s_recording;
            return;
        }
        recording.clear();

        // This is a wierd little circular dependency
        IBSP *bsp; // Need to do this in order to create the consumer and have access to the variable

        // Record the time and value that was provided
        MockIntegerConsumerLambda consumer([this, &bsp](IIntegerConsumer::value_type value)
                                           { recording.push_back(Record(std::make_tuple(bsp->Time().GetMicroseconds(), value))); });

        TestBSP testbsp(consumer);
        bsp = &testbsp;

        const uint32_t stable_time = TestBSP::stable_time;
        PinballApp::Run(*bsp, stable_time * 2 / 3); // The stable time window we give the machine is 66% of the actual stable time
        s_recording = recording;                    // cache this
    }
    Recording recording;
};

// Demonstrate some basic assertions.
TEST_F(RecordingTest, ExpectedValuesAtTimes)
{
    const Recording &records = recording;

    // The expected pattern should output values
    // 237, 42, and 99
    // at times
    // 4, 6, and 6.5 seconds.
    // The last value should be around second 10
    // There should be a value outputted at least every second.

    const int time_range = 100; // Look for the value within +- timerange
    auto expect_value = [&records](int value, ITimeProvider::TimeType time)
    {
        auto it = std::find_if(records.begin(), records.end(),
                               [&time](const Record &r)
                               {
                                   return std::get<0>(r) > time - time_range && std::get<0>(r) < time + time_range;
                               });
        EXPECT_NE(it, records.end());
        EXPECT_EQ(std::get<1>(*it), value);
    };

    // for (auto &value : records)
    // {
    //     std::cout << "Time: " << std::get<0>(value) << " Value: " << std::get<1>(value) << std::endl;
    // }

    expect_value(237, 4 * one_second + stable_time * 2);
    expect_value(42, 6 * one_second + stable_time * 2);
    expect_value(99, 6.5 * one_second + stable_time * 2);
}

TEST_F(RecordingTest, Expect3ValidValues)
{
    const Recording &records = recording;

    // Should be only three valid values
    int validcount = 0;
    for (auto &value : records)
    {
        if (std::get<1>(value) >= 0)
        {
            validcount++;
        }
    }

    EXPECT_EQ(validcount, 3);
}

TEST_F(RecordingTest, LastValueAroundSecond10)
{
    const Recording &records = recording;

    // The last value should be between time 10 and 11
    EXPECT_NEAR(std::get<0>(records.back()), 10 * one_second, 11 * one_second);
}

TEST_F(RecordingTest, ExpectSomeValueEverySecond)
{
    const Recording &records = recording;

    // There should be at least one value every second
    // (technically every second + the transmit time)
    const uint32_t max_value_gap = one_second + stable_time * 3; // 3 times stable time to give it a fudge factor
    uint32_t lasttime = 0;
    for (auto &value : records)
    {
        uint32_t diff_from_last = std::get<0>(value) - lasttime;
        EXPECT_LT(diff_from_last, max_value_gap);
        lasttime = std::get<0>(value);
    }
}