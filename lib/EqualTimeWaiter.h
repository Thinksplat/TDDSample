#ifndef E21D3C25_B801_4579_B115_5C89FA7A13F9
#define E21D3C25_B801_4579_B115_5C89FA7A13F9

#include "lib/ITimeProvider.h"
#include "ITimeWaiter.h"

class EqualTimeWaiter
{
public:
    class DelayWaiter : public ITimeWaiter
    {
    public:
        void Wait()
        {
            // we use these calculations to deal with overflow properly
            while (time.GetMicroseconds() - last_microseconds < delay_microseconds)
            {
            }
            last_microseconds += delay_microseconds;
        }

        DelayWaiter(ITimeProvider &time, uint32_t &last_microseconds, uint32_t delay_microseconds) : time(time), last_microseconds(last_microseconds), delay_microseconds(delay_microseconds) {}

    protected:
        ITimeProvider &time;
        uint32_t &last_microseconds;
        uint32_t delay_microseconds;
    };

    EqualTimeWaiter(ITimeProvider &time)
        : time(time)
    {
        last_microseconds = time.GetMicroseconds();
    }

    DelayWaiter Create(uint32_t delay_microseconds)
    {
        return DelayWaiter(time, last_microseconds, delay_microseconds);
    }

private:
    ITimeProvider &time;
    uint32_t last_microseconds;
};

#endif /* E21D3C25_B801_4579_B115_5C89FA7A13F9 */
