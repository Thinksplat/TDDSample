#ifndef E6A14C88_2DD2_482F_93FA_869F1B594AE9
#define E6A14C88_2DD2_482F_93FA_869F1B594AE9

#include <functional>
#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "shared/bit_conversions.h"
#include "lib-behaviour/BitsToNibbleFunction.h"

class BitsToNibble : public IIntegerProvider
{
public:
    BitsToNibble(const std::function<bool()> &bit0, 
    const std::function<bool()> &bit1, 
    const std::function<bool()> &bit2, 
    const std::function<bool()> &bit3)
    {
        convert = BitsToNibbleFunction::Create(bit0, bit1, bit2, bit3);
    }
    
    int16_t GetInteger() override
    {
       return convert();
    }

private:
    std::function<IIntegerProvider::value_type()> convert;
};

#endif /* E6A14C88_2DD2_482F_93FA_869F1B594AE9 */
