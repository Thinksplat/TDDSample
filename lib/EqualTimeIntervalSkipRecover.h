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
    class SkipRecoverWaiter : public IWork
    {
    public:
        SkipRecoverWaiter(const EqualTimeInterval::TimerWaiter &waiter)
            : waiter(waiter)
        {
        }
        void Work()
        {
            // The skipping process
            while (waiter.HasExpired())
            {
                waiter.Advance();
            }
            waiter.Wait();
        }

    private:
        EqualTimeInterval::TimerWaiter waiter;
    };

    SkipRecoverWaiter CreateWaiter(uint32_t interval_microseconds)
    {
        return SkipRecoverWaiter(eqi.CreateWaiter(interval_microseconds));
    }

    // Wait microseconds from the previous wait point
    void Wait(uint32_t interval_microseconds)
    {
        CreateWaiter(interval_microseconds).Work();
    }

private:
    EqualTimeInterval eqi;
};

#endif /* D73E5041_8188_4427_A096_FC8AC228C66E */
