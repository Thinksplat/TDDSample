#ifndef CDE357EC_2341_497D_89EA_594BDEF60D24
#define CDE357EC_2341_497D_89EA_594BDEF60D24

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "interface/ITimer.h"

namespace Behaviour
{
    /// @brief Returns the last valid value of the provider
    /// @param isValid Keep reading while isValid continues to provide true
    /// @param value The value we are monitoring
    /// @return The last valid value of the provider
    static IIntegerProvider::value_type Stable(IIntegerProvider &value, IBooleanProvider &isValid, ITimer &timer)
    {
        // Reset the timer so we're starting clean
        timer.Reset();

        IIntegerProvider::value_type lastvalue = value.GetInteger();
        // Do this while we're allowed to
        while (isValid.GetBool())
        {
            IIntegerProvider::value_type thisvalue = value.GetInteger();
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
        // If we've exited the loop, the value is invalid.
        // (valid values exit early inside the loop)
        return -1;
    }
}

#endif /* CDE357EC_2341_497D_89EA_594BDEF60D24 */
