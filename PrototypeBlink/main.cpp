#include "bsp_main.h"
#include "lib-behaviour/Blink.h"
#include "lib/EqualTimeInterval.h"
#
//#include "lib-behaviour/Blink.h"
//#include "lib/EqualTimeInterval.h"

void run_program()
{
    BSP bsp;
    auto &until = bsp.RunningTimer();

    EqualTimeInterval equaltime(bsp.Time());
    auto on_time = equaltime.CreateWaiterSeconds(1);
    auto off_time = equaltime.CreateWaiterSeconds(1);
    auto &led = bsp.LED();

    auto on = led.OnFunction();
    auto off = led.OffFunction();
    auto shortwait = [&equaltime]() { equaltime.CreateWaiterSeconds(0.1).Wait(); };

    auto on_off = [on,off,shortwait]()
    {
       on();
       shortwait();
       off();
       shortwait();
    };

    // A little fun here, define the on function to quickly blink the LED
    auto on_function = [on_off,on]()
    {
        on_off();
        on_off();
        on();
    };

    Behaviour::Blink(on_function, off, on_time, off_time, until);
}