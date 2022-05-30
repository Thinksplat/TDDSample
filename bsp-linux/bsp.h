#ifndef A9CF6D59_0CED_454A_8B64_A9D9CDD92F45
#define A9CF6D59_0CED_454A_8B64_A9D9CDD92F45

#include "interface/ITimeProvider.h"
#include "interface/IBSP.h"
#include "interface/IIntegerConsumer.h"
#include "lib/TimeTimer.h"
#include "tests/MockTimeLambda.h"
#include "tests/MockBooleanLambda.h"
#include "tests/Sim.h"
#include "tests/PinballProfile.h"
// include files for gettimeofday
#include <sys/time.h>
#include <iostream>

class LinuxLED : public IBooleanConsumer
{
public:
    void Consume(bool value) override
    {
        if (prev != value)
        {
            prev = value;
            std::cout << "LED: " << value << std::endl;
        }
    }

private:
    bool prev = 0;
};

class LinuxTime : public ITimeProvider
{
public:
    uint32_t GetMicroseconds() override
    {
        return LinuxNumberOfMicroseconds() - starttime;
    }

private:
    uint32_t starttime = LinuxNumberOfMicroseconds();
    static uint32_t LinuxNumberOfMicroseconds()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec * 1000000 + tv.tv_usec;
    }
};

class StdoutConsumer : public IIntegerConsumer
{
public:
    void Consume(int16_t value) override
    {
        std::cout << "Consumer: " << value << std::endl;
    }
};

class BSP : public IBSP
{
public:
    BSP() : pin0([this]()
                 { return this->Time().GetMicroseconds() / 1000000 % 2 == 0; }),
            keeprunning(Time(), 1000000 * 10),
            sim(timemock)
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

    ITimeProvider &Time() override
    {
        return timemock;
    }

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

    IBooleanConsumer &LED() override
    {
        return led;
    }

    ITimer &RunningTimer() override
    {
        return keeprunning;
    }

private:
    LinuxTime timemock;
    MockBooleanLambda pin0;

    TimeTimer keeprunning;
    LinuxLED led;
    Sim sim;
    StdoutConsumer consumer;
};

#endif /* A9CF6D59_0CED_454A_8B64_A9D9CDD92F45 */
