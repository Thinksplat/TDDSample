#ifndef C966AB86_7E5D_483D_BB6D_F9686FE07A05
#define C966AB86_7E5D_483D_BB6D_F9686FE07A05

#include "interface/IBooleanConsumer.h"
#include "interface/IBooleanProvider.h"
//#include "lib-behaviour/Blink.h"
#include <memory>

class BlinkBuilder {
    public:
    BlinkBuilder(IBooleanConsumer &on_off) : on_off(on_off) {}

    void Run() {
        on_off.On();
    }
    
    private:
    IBooleanConsumer &on_off;
};

#endif /* C966AB86_7E5D_483D_BB6D_F9686FE07A05 */
