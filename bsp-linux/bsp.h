#ifndef A9CF6D59_0CED_454A_8B64_A9D9CDD92F45
#define A9CF6D59_0CED_454A_8B64_A9D9CDD92F45

#include "interface/ITimeProvider.h"
#include "interface/IBSP.h"
#include "interface/IIntegerConsumer.h"
#include "tests/MockTimeLambda.h"
#include "tests/MockBooleanLambda.h"
#include "tests/Sim.h"
// include files for gettimeofday
#include <sys/time.h>
#include <iostream>

class LinuxLED : public IIntegerConsumer
{
public:
    void Consume(int16_t value) override
    {
        if (prev != value)
        {
            prev = value;
            std::cout << "LED: " << value << std::endl;
        }
    }

private:
    int16_t prev = 0;
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

class BSP : IBSP
{
public:
    BSP() : pin0([this]()
                 { return this->Time().GetMicroseconds() / 1000000 % 2 == 0; }),
            keeprunning([this]()
                        { return this->Time().GetMicroseconds() < 1000000 * 10; }),
            sim(timemock)
    {
    }

    ITimeProvider &Time()
    {
        return timemock;
    }

    IBooleanProvider &Pin0()
    {
        return pin0;
    }

    IIntegerConsumer &LED()
    {
        return led;
    }

    IBooleanProvider &KeepRunning()
    {
        return keeprunning;
    }

private:
    LinuxTime timemock;
    MockBooleanLambda pin0;
    MockBooleanLambda keeprunning;
    LinuxLED led;
    Sim sim;
};

#endif /* A9CF6D59_0CED_454A_8B64_A9D9CDD92F45 */
