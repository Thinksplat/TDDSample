#include "bsp_main.h"
#include "lib/Stopwatch.h"
#include "lib-behaviour/OnOff.h"
#include "lib-behaviour/Wait.h"
#include "lib-behaviour/Blink.h"
#include "lib/EqualTimeInterval.h"

void SOS(IIntegerConsumer &led, ITimeProvider &time)
{
    const uint32_t shorttime = 100000;
    const uint32_t longtime = shorttime * 3;

    EqualTimeInterval etw(time);
    auto shortwait = etw.CreateWaiter(shorttime);
    auto longwait = etw.CreateWaiter(longtime);

    // S
    Behaviour::Blink(led, shortwait, 3);
    longwait.Wait();

    // O
    Behaviour::Blink(led, longwait, 3);
    longwait.Wait();

    // S
    Behaviour::Blink(led, shortwait, 3);
    longwait.Wait();
}

void run_program()
{
    BSP bsp;

    while (bsp.KeepRunning().GetBool())
    {
        SOS(bsp.LED(), bsp.Time());
        Behaviour::Wait(bsp.Time(), 1000000);
    }
}