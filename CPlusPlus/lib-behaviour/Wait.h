#ifndef AD015665_ECA7_40E1_B6F8_811EEE168E63
#define AD015665_ECA7_40E1_B6F8_811EEE168E63

#include "lib/ITimeProvider.h"
#include "lib/Stopwatch.h"

namespace Behaviour
{
    void Wait(ITimeProvider &time, uint32_t delay_microseconds)
    {
        Stopwatch stopwatch(time);
        while (stopwatch.ElapsedMicroseconds() < delay_microseconds)
        {
        }
    }
} // namespace Behaviour

#endif /* AD015665_ECA7_40E1_B6F8_811EEE168E63 */
