#ifndef C366AC13_245C_4678_BC51_A8CD2EC14545
#define C366AC13_245C_4678_BC51_A8CD2EC14545

#include "interface/IBooleanConsumer.h"
#include "interface/IBooleanProvider.h"
#include "interface/IWork.h"
#include "lib-behaviour/OnOff.h"

namespace Behaviour
{
    inline static void Blink(IBooleanConsumer &output, IWork &waiter, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            Behaviour::OnOff(output, waiter);
        }
    }
    inline static void Blink(IBooleanConsumer &output, IWork &on_wait, IWork &off_wait, IBooleanProvider &done) {
        while(!done.GetBool()) {
            output.On();
            on_wait.Wait();
            output.Off();
            off_wait.Wait();
        }
    }
}

#endif /* C366AC13_245C_4678_BC51_A8CD2EC14545 */
