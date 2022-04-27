#include "bsp_main.h"
#include "lib/Stopwatch.h"

void Blink(IIntegerConsumer &led, ITimeProvider &time, int count, uint32_t delay_microseconds)
{
    for (int i = 0; i < count; ++i)
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
        Blink(bsp.LED(), bsp.Time(), 5, 1000000);
    }
}