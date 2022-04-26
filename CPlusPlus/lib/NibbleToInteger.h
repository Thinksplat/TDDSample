#ifndef E6A14C88_2DD2_482F_93FA_869F1B594AE9
#define E6A14C88_2DD2_482F_93FA_869F1B594AE9

#include "lib/IIntegerProvider.h"
#include "lib/IBooleanProvider.h"

class NibbleToInteger : IIntegerProvider
{
public:
    NibbleToInteger(IBooleanProvider &bit0, IBooleanProvider &bit1, IBooleanProvider &bit2, IBooleanProvider &bit3) : bit0(bit0), bit1(bit1), bit2(bit2), bit3(bit3)
    {
    }
    int16_t GetInteger() override
    {
        return Convert(
            bit0.GetBool(),
            bit1.GetBool(),
            bit2.GetBool(),
            bit3.GetBool());
    }
    
    static int16_t Convert(bool bit0, bool bit1, bool bit2, bool bit3)
    {
        return (bit0 << 0) | 
                (bit1 << 1) | 
                (bit2 << 2) | 
                (bit3 << 3);
    }

private:
    IBooleanProvider &bit0;
    IBooleanProvider &bit1;
    IBooleanProvider &bit2;
    IBooleanProvider &bit3;
};

#endif /* E6A14C88_2DD2_482F_93FA_869F1B594AE9 */
