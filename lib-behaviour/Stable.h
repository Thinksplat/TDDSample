#ifndef CDE357EC_2341_497D_89EA_594BDEF60D24
#define CDE357EC_2341_497D_89EA_594BDEF60D24

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "interface/ITimer.h"

namespace Behaviour
{
    static IIntegerProvider::value_type Stable(IIntegerProvider &provider, IBooleanProvider &isValid, ITimer &timer)
    {
        timer.Reset();
        IIntegerProvider::value_type lastvalue = provider.GetInteger();
        // Do this while we're allowed to
        while (isValid.GetBool())
        {
            IIntegerProvider::value_type thisvalue = provider.GetInteger();
            // If the value has changed, reset the timer
            if (thisvalue != lastvalue)
            {
                lastvalue = thisvalue;
                timer.Reset();
            }
            // If the timer has expired, return the last value
            if (timer.HasExpired())
            {
                return lastvalue;
            }
        }
        // If we've exited the loop, the value is invalid
        return -1;
    }
}

#endif /* CDE357EC_2341_497D_89EA_594BDEF60D24 */
