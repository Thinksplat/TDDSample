#include "bsp_main.h"
#include "lib/Stopwatch.h"

void run_program()
{
    BSP bsp;

    ITimeProvider &time = bsp.Time();
    // IBooleanProvider &pin0 = bsp.Pin0();

    // Stopwatch stopwatch(time);
    // while (stopwatch.ElapsedMicroseconds() < 5 * 1000000)
    // {
    // }

    while(true) {
        bsp.LED().Consume(time.GetMicroseconds() / 1000000 % 2 == 0);
    }
}