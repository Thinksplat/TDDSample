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
    TestBSP(IIntegerConsumer &consumer) 
    : consumer(consumer), sim(time), 
    time(10), // increment time by 10 microseconds each step
    keeprunning(Time(), 1000000 * 10) // run for 10 seconds
    {
        // Setup a sample profile
        const int noise_time = 10;
        const int stable_time = 20 * 1000; // 20ms
        PinballProfile::GenPinball(sim,
                                   4 * 1000000, // 2 seconds in
                                   stable_time * 3 / 2,
                                   stable_time * 3 / 2,
                                   noise_time, 0xd, 0xe);
        // Create another 6 seconds in
        PinballProfile::GenPinball(sim,
                                   6 * 1000000, // 2 seconds in
                                   stable_time * 3 / 2,
                                   stable_time * 3 / 2,
                                   noise_time, 42 & 0xf, 42 >> 4);

        // Create another 6.5 seconds in
        PinballProfile::GenPinball(sim,
                                   6.5 * 1000000, // 2 seconds in
                                   stable_time * 3 / 2,
                                   stable_time * 3 / 2,
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

    // This is a wierd little circular dependency
    IBSP *bsp; // Need to do this in order to create the consumer and have access to the variable

    // Record the time and value that was provided
    MockIntegerConsumerLambda consumer([&records,&bsp](IIntegerConsumer::value_type value)
    {
        records.push_back(Record(std::make_tuple(bsp->Time().GetMicroseconds(), value)));
    });

    TestBSP testbsp(consumer);
    bsp = &testbsp;

    PinballApp::Run(*bsp,20*1000);

    foreach(auto &value: records)
    {
        std::cout << "Time: " << std::get<0>(value) << " Value: " << std::get<1>(value) << std::endl;
    }
}