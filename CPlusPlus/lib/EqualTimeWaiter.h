#ifndef E21D3C25_B801_4579_B115_5C89FA7A13F9
#define E21D3C25_B801_4579_B115_5C89FA7A13F9

#include "ITimeWaiter.h"
#include "Stopwatch.h"

class EqualTimeWaiter : public ITimeWaiter
{
public:
    EqualTimeWaiter(ITimeProvider &time, uint32_t delay_microseconds)
        : stopwatch(time), delay_microseconds(delay_microseconds)
    {
        last_microseconds = time.GetMicroseconds();
    }

    void Wait()
    {
        // we use these calculations to deal with overflow properly
        while (stopwatch.ElapsedMicroseconds() - last_microseconds < delay_microseconds)
        {
        }
        last_microseconds += delay_microseconds;
    }

private:
    Stopwatch stopwatch;
    uint32_t delay_microseconds;
    uint32_t last_microseconds;
};

#endif /* E21D3C25_B801_4579_B115_5C89FA7A13F9 */
