#ifndef C366AC13_245C_4678_BC51_A8CD2EC14545
#define C366AC13_245C_4678_BC51_A8CD2EC14545

#include <functional>
#include "interface/IBooleanConsumer.h"
#include "interface/IBooleanProvider.h"
#include "interface/IWork.h"
#include "lib-behaviour/OnOff.h"

namespace Behaviour
{
    inline static void Blink(const std::function<void()> &turn_on,
                             const std::function<void()> &turn_off,
                             const std::function<void()> &on_wait,
                             const std::function<void()> &off_wait,
                             const std::function<bool()> &done)
    {
        while (!done())
        {
            turn_on();
            on_wait();
            turn_off();
            off_wait();
        }
    }
    inline static void Blink(IBooleanConsumer &output, IWork &waiter, int count)
    {
        Blink(output.OnFunction(), output.OffFunction(), waiter, waiter, [&count]() -> bool
              {
           count -= 1;
           return count < 0; });
    }
    inline static void Blink(IBooleanConsumer &output,
                             const std::function<void()> &on_wait,
                             const std::function<void()> &off_wait,
                             const std::function<bool()> &done)
    {
        Blink(output.OnFunction(), output.OffFunction(), on_wait, off_wait, done);
    }

}

#endif /* C366AC13_245C_4678_BC51_A8CD2EC14545 */
