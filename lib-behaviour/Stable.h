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
    static IIntegerProvider::value_type Stable(const std::function<int16_t()> &value, const std::function<bool()> &isValid, ITimer &timer)
    {
        // We don't reset the timer on entry because the
        // logic below will fall through to reset the value
        // after the first read (because lastvalue is -1)

        IIntegerProvider::value_type lastvalue = -1;
        // Do this while we're allowed to
        while (isValid())
        {
            IIntegerProvider::value_type thisvalue = value();
            if(thisvalue < 0) {
                return thisvalue;
            }
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
