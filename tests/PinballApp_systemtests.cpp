#include <gtest/gtest.h>
#include "tests/PinballProfile.h"
#include "tests/Sim.h"
#include "lib/PinballApp.h"
#include "tests/WalkingTime.h"
#include "tests/MockIntegerConsumer.h"
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
    time(10), // increment time by 10 microseconds each step
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

    ITimeProvider &Time()
    {
        return time;
    }

    // A timer that expires when we should stop running
    ITimer &RunningTimer()
    {
        return keeprunning;
    }

    // LED for visible status if
    IIntegerConsumer &LED()
    {
        return led;
    }

    // Where the data is sent to
    IIntegerConsumer &Consumer()
    {
        return consumer;
    }

    IBooleanProvider &Transmit()
    {
        return sim.Lines().Transmit();
    }

    IBooleanProvider &Pin0()
    {
        return sim.Lines().Data0();
    }

    IBooleanProvider &Pin1()
    {
        return sim.Lines().Data1();
    }
    IBooleanProvider &Pin2()
    {
        return sim.Lines().Data2();
    }
    IBooleanProvider &Pin3()
    {
        return sim.Lines().Data3();
    }

private:
    IIntegerConsumer &consumer;
    Sim sim;
    WalkingTime time;
    TimeTimer keeprunning;
    MockIntegerConsumer led;
};

// Demonstrate some basic assertions.
TEST(PinballApp, SetupAndRun)
{
    typedef std::tuple<ITimeProvider::TimeType, int> Record;
    std::vector<Record> records;
    const ITimeProvider::TimeType one_second = 1000000;

    // This is a wierd little circular dependency
    IBSP *bsp; // Need to do this in order to create the consumer and have access to the variable

    // Record the time and value that was provided
    MockIntegerConsumerLambda consumer([&records,&bsp](IIntegerConsumer::value_type value)
    {
        records.push_back(Record(std::make_tuple(bsp->Time().GetMicroseconds(), value)));
    });

    TestBSP testbsp(consumer);
    bsp = &testbsp;

    const uint32_t stable_time = TestBSP::stable_time;
    PinballApp::Run(*bsp, stable_time * 2 / 3); // The stable time window we give the machine is 66% of the actual stable time

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
                                   return std::get<0>(r) > time-time_range && std::get<0>(r) < time+time_range;
                               });
        EXPECT_NE(it, records.end());
        EXPECT_EQ(std::get<1>(*it), value);
    };

    for(auto &value: records)
    {
        std::cout << "Time: " << std::get<0>(value) << " Value: " << std::get<1>(value) << std::endl;
    }

    expect_value(237, 4 * one_second + stable_time*2);
    expect_value(42, 6 * one_second + stable_time*2);
    expect_value(99, 6.5 * one_second + stable_time*2);

    // Should be only three valid values
    int validcount = 0;
    for(auto &value: records)
    {
        if(std::get<1>(value) >= 0)
        {
            validcount++;
        }
    }

    EXPECT_EQ(validcount, 3);

    // The last value should be between time 10 and 11
    EXPECT_NEAR(std::get<0>(records.back()), 10 * one_second, 11 * one_second);

    // There should be at least one value every second
    // (technically every second + the transmit time)
    const uint32_t max_value_gap = one_second + stable_time * 3; // 3 times stable time to give it a fudge factor
    uint32_t lasttime = 0;
    for(auto &value: records)
    {
        uint32_t diff_from_last = std::get<0>(value) - lasttime;
        EXPECT_LT(diff_from_last, max_value_gap);
        lasttime = std::get<0>(value);
    }

}