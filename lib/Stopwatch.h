#ifndef C7A5E506_5861_4277_B46F_6172A941A349
#define C7A5E506_5861_4277_B46F_6172A941A349

#include <functional>

class Stopwatch
{
public:
    Stopwatch(const std::function<uint32_t()> &timeProvider) : timeProvider(timeProvider)
    {
        Reset();
    }
    
    void Reset()
    {
        startTime = timeProvider();
    }

    uint32_t ElapsedMicroseconds()
    {
        // This properly handles rollover when the provider goes over
        // 2^32-1 microseconds.
        return timeProvider() - startTime;
    }

private:
    std::function<uint32_t()> timeProvider;
    uint32_t startTime;
};

#endif /* C7A5E506_5861_4277_B46F_6172A941A349 */
