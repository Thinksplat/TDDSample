#ifndef E21D3C25_B801_4579_B115_5C89FA7A13F9
#define E21D3C25_B801_4579_B115_5C89FA7A13F9

#include "lib/ITimeProvider.h"
#include "ITimeWaiter.h"

class EqualTimeWaiter : public ITimeWaiter
{
public:
    EqualTimeWaiter(ITimeProvider &time, uint32_t delay_microseconds)
        : time(time), delay_microseconds(delay_microseconds)
    {
        last_microseconds = time.GetMicroseconds();
    }

    void Sequence(EqualTimeWaiter &next) {
        next.last_microseconds = this->last_microseconds;
    }

    void Wait()
    {
        // we use these calculations to deal with overflow properly
        while (time.GetMicroseconds() - last_microseconds < delay_microseconds)
        {
        }
        last_microseconds += delay_microseconds;
    }

private:
    ITimeProvider &time;
    uint32_t delay_microseconds;
    uint32_t last_microseconds;
};

#endif /* E21D3C25_B801_4579_B115_5C89FA7A13F9 */
