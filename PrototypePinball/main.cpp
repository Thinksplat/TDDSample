#include "bsp_main.h"
#include "lib/Pinball.h"
#include "lib/TimeTimer.h"
#include "lib/App.h"

void run_program()
{
    BSP system_bsp;
    IBSP &bsp = system_bsp;

    // Create a stable timer
    const int stable_time = 100;
    TimeTimer stable_timer(bsp.Time(), stable_time);

    // Create the pinball and wire it up to the BSP
    Pinball pinball(bsp.Enable(), bsp.Pin0(), bsp.Pin1(), bsp.Pin2(), bsp.Pin3(), stable_timer);

    // Create the application and run it
    App app(pinball, bsp.Consumer(), bsp.RunningTimer());
    
    app.Run();
}