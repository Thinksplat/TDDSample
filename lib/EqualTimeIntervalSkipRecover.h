#ifndef D73E5041_8188_4427_A096_FC8AC228C66E
#define D73E5041_8188_4427_A096_FC8AC228C66E

#include "EqualTimeInterval.h"

class EqualTimeIntervalSkipRecover
{
public:
    EqualTimeIntervalSkipRecover(ITimeProvider &time)
        : eqi(time)
    {
    }
    class SkipRecoverWaiter : public ITimeWaiter
    {
    public:
        SkipRecoverWaiter(const EqualTimeInterval::TimerWaiter &waiter)
            : waiter(waiter)
        {
        }
        void Wait() {
            // The skipping process
            while(waiter.HasExpired()) {
                waiter.Advance();
            }
            waiter.Wait();
        }

    private:
        EqualTimeInterval::TimerWaiter waiter;
    };
    SkipRecoverWaiter CreateWaiter(uint32_t delay_microseconds)
    {
        return SkipRecoverWaiter(eqi.CreateWaiter(delay_microseconds));
    }

private:
    EqualTimeInterval eqi;
};

#endif /* D73E5041_8188_4427_A096_FC8AC228C66E */
