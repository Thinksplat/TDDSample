#ifndef BF04202A_3954_46A7_8763_D6A6230754B9
#define BF04202A_3954_46A7_8763_D6A6230754B9

#include "interface/ITimeProvider.h"

class Stopwatch
{
public:
    Stopwatch(ITimeProvider &timeProvider) : timeProvider(timeProvider)
    {
        Reset();
    }
    
    void Reset()
    {
        startTime = timeProvider.GetMicroseconds();
    }

    uint32_t ElapsedMicroseconds()
    {
        // This properly handles rollover when the provider goes over
        // 2^32-1 microseconds.
        return timeProvider.GetMicroseconds() - startTime;
    }

private:
    ITimeProvider &timeProvider;
    uint32_t startTime;
};

#endif /* BF04202A_3954_46A7_8763_D6A6230754B9 */
