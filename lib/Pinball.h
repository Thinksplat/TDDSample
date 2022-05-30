#ifndef C1618207_A198_4257_92EA_BEE9F994DD12
#define C1618207_A198_4257_92EA_BEE9F994DD12

#include "lib/BitsToNibble.h"
#include "lib-behaviour/Stable.h"
#include "interface/ITimer.h"
#include "lib-behaviour/LastValidValue.h"
#include "lib-behaviour/BitsToNibbleFunction.h"
#include "shared/bit_conversions.h"

class Pinball : public IIntegerProvider
{
public:
    typedef std::tuple<int16_t, int16_t, int16_t> value_low_high;
    // The full functional implementation of the pinball reader.
    static inline std::function<value_low_high()> Create(const std::function<bool()> &enable, const std::function<int16_t()> &nibble, ITimer &stable_timer)
    {
        // Spin on the enable line to wait for the data to be sending
        auto wait_for_read = [enable]()
        {
            while (!enable())
            {
                // spin
            }
        };

        std::function<int16_t()> stable_nibble = [nibble, enable, &stable_timer]()
        { return Behaviour::Stable(nibble, enable, stable_timer); };

        return [wait_for_read, stable_nibble, enable]() -> value_low_high
        {
            // Wait for the enable line to go high
            wait_for_read();

            // Read the first stable nibble
            auto low_nibble = stable_nibble();

            // Read the last stable nibble
            auto high_nibble = Behaviour::LastValidValue(enable, stable_nibble);

            // if low or high is invalid the entire thing is invalid
            if (low_nibble < 0 || high_nibble < 0)
            {
                return std::make_tuple(-1, low_nibble, high_nibble);
            }

            // Combine the nibbles into a single value
            return std::make_tuple(BitConversions::NibblesToWord(low_nibble, high_nibble), low_nibble, high_nibble);
        };
    }

    Pinball(const std::function<bool()> &enable,
            const std::function<bool()> &bit0,
            const std::function<bool()> &bit1,
            const std::function<bool()> &bit2,
            const std::function<bool()> &bit3,
            ITimer &stable_timer) : Pinball(enable, BitsToNibbleFunction::Create(bit0, bit1, bit2, bit3), stable_timer)
    {
    }

    Pinball(const std::function<bool()> &enable, const std::function<int16_t()> &nibble, ITimer &stable_timer)
        : convert(Create(enable, nibble, stable_timer))
    {
    }

    int16_t GetInteger()
    {
        last_value = convert();
        return std::get<0>(last_value);
    }

    // Expose the nibble to the outside world for testing
    int16_t LastLowNibble()
    {
        return std::get<1>(last_value);
    }

    int16_t LastHighNibble()
    {
        return std::get<2>(last_value);
    }

private:
    value_low_high last_value;
    std::function<value_low_high()> convert;
};

#endif /* C1618207_A198_4257_92EA_BEE9F994DD12 */
