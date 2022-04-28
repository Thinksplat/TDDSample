#ifndef E21D3C25_B801_4579_B115_5C89FA7A13F9
#define E21D3C25_B801_4579_B115_5C89FA7A13F9

#include "lib/ITimeProvider.h"
#include "ITimeWaiter.h"

// On overframe will immediately return to attempt to catch up
class EqualTimeInterval
{
public:
    class TimerWaiter : public ITimeWaiter
    {
    public:
        void Wait()
        {
            // we use these calculations to deal with overflow properly
            while (!HasExpired())
            {
                // Spin
            }
            Advance();
        }

        inline bool HasExpired()
        {
            return time.GetMicroseconds() - last_microseconds >= delay_microseconds;
        }

        inline void Advance()
        {
            last_microseconds += delay_microseconds;
        }

        TimerWaiter(ITimeProvider &time, uint32_t &last_microseconds, uint32_t delay_microseconds) : time(time), last_microseconds(last_microseconds), delay_microseconds(delay_microseconds) {}

    protected:
        ITimeProvider &time;
        uint32_t &last_microseconds;
        uint32_t delay_microseconds;
    };

    EqualTimeInterval(ITimeProvider &time)
        : time(time)
    {
        last_microseconds = time.GetMicroseconds();
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
