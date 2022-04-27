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
        next_elapsed_microseconds = delay_microseconds;
    }
    void Wait() {
        while (stopwatch.ElapsedMicroseconds() < next_elapsed_microseconds) {
        }
        next_elapsed_microseconds += delay_microseconds;
    }
    private:
    Stopwatch stopwatch;
    uint32_t delay_microseconds;
    uint32_t next_elapsed_microseconds;
};

#endif /* E21D3C25_B801_4579_B115_5C89FA7A13F9 */
