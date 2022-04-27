#include "bsp_main.h"
#include "lib/Stopwatch.h"
#include "lib-behaviour/OnOff.h"
#include "lib-behaviour/Wait.h"

void Blink(IIntegerConsumer &led, ITimeProvider &time, int count, uint32_t delay_microseconds)
{
    for (int i = 0; i < count; ++i)
    {
        Behaviour::OnOff(led, time, delay_microseconds);
    }
}

void SOS(IIntegerConsumer &led, ITimeProvider &time)
{
    const uint32_t shorttime = 100000;
    const uint32_t longtime = shorttime * 3;
    Blink(led, time, 3, shorttime);
    Behaviour::Wait(time, longtime);
    Blink(led, time, 3, longtime);
    Behaviour::Wait(time, longtime);
    Blink(led, time, 3, shorttime);
    Behaviour::Wait(time, longtime);
    Behaviour::Wait(time, longtime);
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