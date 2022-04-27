#ifndef CA004DDE_5C51_4169_AB6F_C38523D0B2BD
#define CA004DDE_5C51_4169_AB6F_C38523D0B2BD

#include "bsp.h"

extern void run_program();

extern "C" {
    void setup();
    void loop();
}
void setup()
{

}

void loop()
{
    run_program();
}

#endif /* CA004DDE_5C51_4169_AB6F_C38523D0B2BD */
