#ifndef E4C754FD_DE68_4A94_946C_47B3D09CAF35
#define E4C754FD_DE68_4A94_946C_47B3D09CAF35

#include "lib/IIntegerProvider.h"

class NibblesToInteger : public IIntegerProvider
{
public:
    NibblesToInteger(IIntegerProvider &lowbits, IIntegerProvider &highbits) : lowbits(lowbits), highbits(highbits)
    {
    }

    int16_t GetInteger() override
    {
        return Convert(
            lowbits.GetInteger(),
            highbits.GetInteger());
    }

    static int16_t Convert(int16_t lowbits, int16_t highbits) {
        return (highbits << 4) | lowbits;
    }

private:
    IIntegerProvider &lowbits;
    IIntegerProvider &highbits;
};

#endif /* E4C754FD_DE68_4A94_946C_47B3D09CAF35 */
