#ifndef C366AC13_245C_4678_BC51_A8CD2EC14545
#define C366AC13_245C_4678_BC51_A8CD2EC14545

#include "interface/IIntegerConsumer.h"
#include "interface/IWaiter.h"
#include "lib-behaviour/OnOff.h"

namespace Behaviour
{
    static void Blink(IIntegerConsumer &led, IWaiter &waiter, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            Behaviour::OnOff(led, waiter);
        }
    }
}

#endif /* C366AC13_245C_4678_BC51_A8CD2EC14545 */
