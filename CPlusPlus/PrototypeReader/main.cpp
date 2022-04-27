#include "bsp_main.h"
#include "lib/Stopwatch.h"

void OnOff(IIntegerConsumer &led, ITimeProvider &time, uint32_t delay_microseconds)
{
    // ON
    Stopwatch stopwatch(time);
    while (stopwatch.ElapsedMicroseconds() < delay_microseconds)
    {
        led.Consume(1);
    }

    // Off
    stopwatch.Reset();
    while (stopwatch.ElapsedMicroseconds() < delay_microseconds)
    {
        led.Consume(0);
    }
}

void Blink(IIntegerConsumer &led, ITimeProvider &time, int count, uint32_t delay_microseconds)
{
    for (int i = 0; i < count; ++i)
    {
        OnOff(led, time, delay_microseconds);
    }
}

void Wait(ITimeProvider &time, uint32_t microseconds)
{
    Stopwatch stopwatch(time);
    while (stopwatch.ElapsedMicroseconds() < microseconds)
    {
    }
}

void SOS(IIntegerConsumer &led, ITimeProvider &time)
{
    const uint32_t shorttime = 100000;
    const uint32_t longtime = shorttime * 3;
    Blink(led, time, 3, shorttime);
    Wait(time, longtime);
    Blink(led, time, 3, longtime);
    Wait(time, longtime);
    Blink(led, time, 3, shorttime);
    Wait(time, longtime);
    Wait(time, longtime);
}

void run_program()
{
    BSP bsp;

    // ITimeProvider &time = bsp.Time();
    // IBooleanProvider &pin0 = bsp.Pin0();

    // Stopwatch stopwatch(time);
    // while (stopwatch.ElapsedMicroseconds() < 5 * 1000000)
    // {
    // }

    while (true)
    {
        SOS(bsp.LED(), bsp.Time());
    }
}