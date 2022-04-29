#ifndef FB185EEF_26A2_4C49_BF99_EDBC19BBBB11
#define FB185EEF_26A2_4C49_BF99_EDBC19BBBB11

#include "interface/ITimeProvider.h"
#include "lib/Stopwatch.h"

namespace Behaviour
{
    static void Wait(ITimeProvider &time, uint32_t delay_microseconds)
    {
        Stopwatch stopwatch(time);
        while (stopwatch.ElapsedMicroseconds() < delay_microseconds)
        {
        }
    }
} // namespace Behaviour


#endif /* FB185EEF_26A2_4C49_BF99_EDBC19BBBB11 */
