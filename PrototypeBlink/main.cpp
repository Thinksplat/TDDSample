#include "bsp_main.h"
//#include "lib-behaviour/Blink.h"
//#include "lib/EqualTimeInterval.h"

void run_program()
{
    BSP bsp;

    while (!bsp.RunningTimer().HasExpired())
    {
       // SOS(bsp.LED(), bsp.Time());
    }
}