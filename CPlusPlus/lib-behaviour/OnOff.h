#ifndef D6560AD8_CADB_40B0_8B37_0E2F0B74B126
#define D6560AD8_CADB_40B0_8B37_0E2F0B74B126

#include "lib/IIntegerConsumer.h"
#include "lib/ITimeProvider.h"
#include "lib-behaviour/Wait.h"

namespace Behaviour
{
    static void OnOff(IIntegerConsumer &led, ITimeProvider &time, uint32_t delay_microseconds)
    {
        // ON
        led.Consume(1);
        Wait(time, delay_microseconds);

        // Off
        led.Consume(0);
        Wait(time, delay_microseconds);
    }

} // namespace Behaviour

#endif /* D6560AD8_CADB_40B0_8B37_0E2F0B74B126 */
