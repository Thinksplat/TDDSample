#ifndef C1618207_A198_4257_92EA_BEE9F994DD12
#define C1618207_A198_4257_92EA_BEE9F994DD12

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "lib/BitsToNibble.h"
#include "lib/StableInteger.h"
#include "interface/ITimer.h"
#include "lib-behaviour/LastValidValue.h"
#include "lib-behaviour/BitsToNibbleFunction.h"
#include "lib/WorkUntilTrue.h"
#include "shared/bit_conversions.h"

class Pinball : public IIntegerProvider
{
public:
    Pinball(const std::function<bool()> &enable,
            const std::function<bool()> &bit0,
            const std::function<bool()> &bit1,
            const std::function<bool()> &bit2,
            const std::function<bool()> &bit3,
            ITimer &stable_timer) : Pinball(enable, BitsToNibbleFunction::Create(bit0, bit1, bit2, bit3), stable_timer)
    {
    }

    Pinball(const std::function<bool()> &enable, const std::function<int16_t()> &nibble, ITimer &stable_timer)
        : stable_nibble(nibble, enable, stable_timer),
          is_transmitting(enable),
          enable(enable)
    {
    }

    IIntegerProvider::value_type GetInteger()
    {
        // This is the meat of our project.

        // Wait for the enable line to go high
        is_transmitting.Work();

        // Read the first stable nibble
        low_nibble = stable_nibble.GetInteger();

        // Read the last stable nibble
        high_nibble = Behaviour::LastValidValue(enable, stable_nibble.GetFunction());

        // if low or high is invalid the entire thing is invalid
        if (low_nibble < 0 || high_nibble < 0)
        {
            return -1;
        }

        // Combine the nibbles into a single value
        return BitConversions::NibblesToWord(low_nibble, high_nibble);
    }

    // Expose the nibble to the outside world for testing
    IIntegerProvider::value_type LastLowNibble()
    {
        return low_nibble;
    }

    IIntegerProvider::value_type LastHighNibble()
    {
        return high_nibble;
    }

private:
    StableInteger stable_nibble;
    WorkUntilTrue is_transmitting;
    std::function<bool()> enable;

    IIntegerProvider::value_type low_nibble;
    IIntegerProvider::value_type high_nibble;
};

#endif /* C1618207_A198_4257_92EA_BEE9F994DD12 */
