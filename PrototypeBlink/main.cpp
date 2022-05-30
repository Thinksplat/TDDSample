#include "bsp_main.h"
#include "lib-behaviour/BlinkBuilder.h"
#include "lib/EqualTimeInterval.h"
//#include "lib-behaviour/Blink.h"
//#include "lib/EqualTimeInterval.h"

void run_program()
{
    BSP bsp;
    auto &until = bsp.RunningTimer();

    EqualTimeInterval equaltime(bsp.Time());
    auto one_second = equaltime.CreateWaiterSeconds(0.5);

    auto blinker = BlinkBuilder().OnOff(bsp.LED()).Until(until).Wait(one_second);
    blinker.Run();

}