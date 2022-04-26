#ifndef DA128173_42BF_483A_A5E0_F41AA962A50E
#define DA128173_42BF_483A_A5E0_F41AA962A50E

#include <stdint.h>

namespace BitConversions
{
    inline int16_t NibbleToInteger(bool bit0, bool bit1, bool bit2, bool bit3)
    {
        return (bit0 << 0) |
               (bit1 << 1) |
               (bit2 << 2) |
               (bit3 << 3);
    }
}

#endif /* DA128173_42BF_483A_A5E0_F41AA962A50E */
