#ifndef E21D3C25_B801_4579_B115_5C89FA7A13F9
#define E21D3C25_B801_4579_B115_5C89FA7A13F9

#include "interface/ITimeProvider.h"
#include "interface/ITimer.h"

// On overframe will immediately return to attempt to catch up
class EqualTimeInterval
{
public:
    class TimerWaiter : public ITimer
    {
    public:
        void Work() override
        {
            // we use these calculations to deal with overflow properly
            while (NotReady())
            {
                // Spin
            }
            Advance();
        }

        inline bool NotReady()
        {
            return !HasExpired();
        }

        inline bool HasExpired() override
        {
            return time.GetMicroseconds() - last_microseconds >= interval_microseconds;
        }

        inline void Advance()
        {
            last_microseconds += interval_microseconds;
        }
        void Reset() override
        {
            // do nothing
        }

        TimerWaiter(ITimeProvider &time, uint32_t &last_microseconds, uint32_t interval_microseconds) : time(time), last_microseconds(last_microseconds), interval_microseconds(interval_microseconds) {}

    protected:
        ITimeProvider &time;
        uint32_t &last_microseconds;
        uint32_t interval_microseconds;
    };

    EqualTimeInterval(ITimeProvider &time)
        : time(time)
    {
        last_microseconds = time.GetMicroseconds();
    }

    TimerWaiter CreateWaiterSeconds(double seconds)
    {
        return TimerWaiter(time, last_microseconds, (uint32_t)(1000000.0 / seconds));
    }

    TimerWaiter CreateWaiter(uint32_t delay_microseconds)
    {
        return TimerWaiter(time, last_microseconds, delay_microseconds);
    }

    void Wait(uint32_t delay_microseconds)
    {
        CreateWaiter(delay_microseconds).Wait();
    }

private:
    ITimeProvider &time;
    uint32_t last_microseconds;
};

#endif /* E21D3C25_B801_4579_B115_5C89FA7A13F9 */
