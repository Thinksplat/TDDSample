#include "bsp_main.h"
#include "lib/PinballApp.h"

void run_program()
{
    BSP system_bsp;
    IBSP &bsp = system_bsp;

    // Create a stable timer
    const int stable_time = 20 * 1000; // 20ms

    PinballApp::Run(bsp, stable_time);
}