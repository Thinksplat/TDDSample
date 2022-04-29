#ifndef C1618207_A198_4257_92EA_BEE9F994DD12
#define C1618207_A198_4257_92EA_BEE9F994DD12

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "lib/BitsToNibble.h"
#include "lib/StableInteger.h"
#include "interface/ITimer.h"
#include "lib-behaviour/LastValidValue.h"
#include "lib/BoolTrueWaiter.h"

class Pinball : public IIntegerProvider
{
public:
    Pinball(IBooleanProvider &enable, IBooleanProvider &pin0, IBooleanProvider &pin1, IBooleanProvider &pin2, IBooleanProvider &pin3,
        ITimer &stable_timer)
        : nibble(pin0,pin1,pin2,pin3), 
        stable_nibble(nibble, enable, stable_timer), 
        is_transmitting(enable),
        enable(enable)
    {
    }

    IIntegerProvider::value_type GetInteger()
    {
        // This is the meat of our project.
        
        // Wait for the enable line to go high
        is_transmitting.Wait();

        // Read the first stable nibble
        low_nibble = stable_nibble.GetInteger();

        // Read the last stable nibble
        high_nibble = Behaviour::LastValidValue(enable, stable_nibble);

        // if low or high is invalid the entire thing is invalid
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
    BoolTrueWaiter is_transmitting;
    IBooleanProvider &enable;

    IIntegerProvider::value_type low_nibble;
    IIntegerProvider::value_type high_nibble;
};

#endif /* C1618207_A198_4257_92EA_BEE9F994DD12 */
