#include "bsp_main.h"
#include "lib/Pinball.h"
#include "lib/TimeTimer.h"
#include "lib/IntegerTimeout.h"
#include "lib/App.h"

void run_program()
{
    BSP system_bsp;
    IBSP &bsp = system_bsp;

    // Create a stable timer
    const int stable_time = 20 * 1000; // 20ms
    TimeTimer stable_timer(bsp.Time(), stable_time);

    // Create the pinball and wire it up to the BSP
    Pinball pinball(bsp.Transmit(), bsp.Pin0(), bsp.Pin1(), bsp.Pin2(), bsp.Pin3(), stable_timer);

    // Wrap a Timeout around the pinball so that it is able to provide a read timeout
    // to indicate to the host that the bus reader is running but didn't receive data.
    TimeTimer timeout_timer(bsp.Time(), 1 * 1000000); // 1 second
    IntegerTimeout read_timeout(pinball, bsp.Transmit(), timeout_timer);

    // Create the application and run it
    App app(read_timeout, bsp.Consumer(), bsp.RunningTimer());
    
    app.Run();
}