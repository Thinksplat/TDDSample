#ifndef AF9B907F_63A5_4B26_92DA_C99A2D2773B7
#define AF9B907F_63A5_4B26_92DA_C99A2D2773B7

#include <functional>
#include "shared/bit_conversions.h"

class BitsToNibbleFunction
{
public:
    static inline std::function<int16_t()> Create(
        const std::function<bool()> &bit0, 
        const std::function<bool()> &bit1, 
        const std::function<bool()> &bit2, 
        const std::function<bool()> &bit3)
    {
        return [bit0,bit1,bit2,bit3]() {
            return BitConversions::BitsToInteger(bit0(), bit1(), bit2(), bit3());
        };
    }

};

#endif /* AF9B907F_63A5_4B26_92DA_C99A2D2773B7 */
