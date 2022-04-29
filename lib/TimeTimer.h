#ifndef E7FBD4F9_E87D_4319_8227_573A2290AD49
#define E7FBD4F9_E87D_4319_8227_573A2290AD49

#include "interface/ITimer.h"
#include "interface/ITimeProvider.h"
#include "lib/Stopwatch.h"

class TimeTimer : public ITimer
{
    public:
    TimeTimer(ITimeProvider &timeProvider, ITimeProvider::TimeType timeout) : stopwatch(timeProvider), timeout(timeout) {}
    bool HasExpired() override {
        return stopwatch.ElapsedMicroseconds() >= timeout;
    }
    void Reset() override {
        stopwatch.Reset();
    }
    private:
    Stopwatch stopwatch;
    ITimeProvider::TimeType timeout;
};

#endif /* E7FBD4F9_E87D_4319_8227_573A2290AD49 */
