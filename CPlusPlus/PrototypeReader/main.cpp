#include <iostream>
#include "bsp.h"



int main(int argc, char *argv[]) {
    BSP bsp;

    ITimeProvider &time = bsp.Time();
    IBooleanProvider &pin0 = bsp.Pin0();

    while(true) {
        std::cout << "Pin0: " << pin0.GetBool() << " Time: " << time.GetMicroseconds() << std::endl;
    }

    return 0;
}