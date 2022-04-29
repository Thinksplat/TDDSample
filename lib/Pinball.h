#ifndef C1618207_A198_4257_92EA_BEE9F994DD12
#define C1618207_A198_4257_92EA_BEE9F994DD12

#include "lib/IIntegerProvider.h"
#include "lib/IBooleanProvider.h"
#include "lib/BitsToNibble.h"
#include "lib/StableInteger.h"
#include "lib/ITimer.h"
#include "lib-behaviour/LastValidValue.h"

class Pinball : public IIntegerProvider
{
public:
    Pinball(IBooleanProvider &enable, IBooleanProvider &pin0, IBooleanProvider &pin1, IBooleanProvider &pin2, IBooleanProvider &pin3,
        ITimer &stable_timer)
        : nibble(pin0,pin1,pin2,pin3), stable_nibble(nibble, enable, stable_timer), enable(enable)
    {
    }

    IIntegerProvider::value_type GetInteger()
    {
        // This is the meat of our project.
        
        // Wait for the enable line to go high
        while(enable.GetBool() == false) {
            // spin
        }

        // Read the first stable nibble
        low_nibble = stable_nibble.GetInteger();

        // Read the last stable nibble
        high_nibble = Behaviour::LastValidValue(enable, stable_nibble);

        // if one is invalid the entire thing is invalid
        if(low_nibble < 0 || high_nibble < 0) {
            return -1;
        }

        // Combine the nibbles into a single value
        return (high_nibble << 4) | low_nibble;
    }

    // Expose the nibble to the outside world for testing
    IIntegerProvider::value_type LastLowNibble() {
        return low_nibble;
    }

    IIntegerProvider::value_type LastHighNibble() {
        return high_nibble;
    }

private:
    BitsToNibble nibble;
    StableInteger stable_nibble;
    IBooleanProvider &enable;

    IIntegerProvider::value_type low_nibble;
    IIntegerProvider::value_type high_nibble;
};

#endif /* C1618207_A198_4257_92EA_BEE9F994DD12 */
