#ifndef DA128173_42BF_483A_A5E0_F41AA962A50E
#define DA128173_42BF_483A_A5E0_F41AA962A50E

#include <stdint.h>

namespace BitConversions
{
    inline int16_t BitsToInteger(bool bit0, bool bit1, bool bit2, bool bit3)
    {
        return (bit0 << 0) |
               (bit1 << 1) |
               (bit2 << 2) |
               (bit3 << 3);
    }

    inline int16_t NibblesToWord(int16_t lowbits, int16_t highbits)
    {
        return (highbits << 4) | lowbits;
    }
}

#endif /* DA128173_42BF_483A_A5E0_F41AA962A50E */
