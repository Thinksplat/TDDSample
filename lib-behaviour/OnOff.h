#ifndef D6560AD8_CADB_40B0_8B37_0E2F0B74B126
#define D6560AD8_CADB_40B0_8B37_0E2F0B74B126

#include "interface/IBooleanConsumer.h"
#include "interface/IWork.h"

namespace Behaviour
{
    static void OnOff(IBooleanConsumer &output, IWork &waiter)
    {
        // ON
        output.Consume(1);
        waiter.Work();

        // Off
        output.Consume(0);
        waiter.Work();
    }

} // namespace Behaviour

#endif /* D6560AD8_CADB_40B0_8B37_0E2F0B74B126 */
