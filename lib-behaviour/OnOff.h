#ifndef D6560AD8_CADB_40B0_8B37_0E2F0B74B126
#define D6560AD8_CADB_40B0_8B37_0E2F0B74B126

#include "interface/IIntegerConsumer.h"
#include "interface/IWaiter.h"

namespace Behaviour
{
    static void OnOff(IIntegerConsumer &output, IWaiter &waiter)
    {
        // ON
        output.Consume(1);
        waiter.Wait();

        // Off
        output.Consume(0);
        waiter.Wait();
    }

} // namespace Behaviour

#endif /* D6560AD8_CADB_40B0_8B37_0E2F0B74B126 */
