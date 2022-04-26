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
        return (bit0.GetBool() ? 1 : 0) + (bit1.GetBool() ? 2 : 0) + (bit2.GetBool() ? 4 : 0) + (bit3.GetBool() ? 8 : 0);
    }

private:
    IBooleanProvider &bit0;
    IBooleanProvider &bit1;
    IBooleanProvider &bit2;
    IBooleanProvider &bit3;
};

#endif /* E6A14C88_2DD2_482F_93FA_869F1B594AE9 */
