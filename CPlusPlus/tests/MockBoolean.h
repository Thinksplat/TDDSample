#ifndef B8751227_E850_4FDC_8820_01E664E85DB6
#define B8751227_E850_4FDC_8820_01E664E85DB6

#include "lib/IBooleanProvider.h"

class MockBoolean : IBooleanProvider
{
public:
    MockBoolean(bool value) : value(value) {}
    bool GetBool() override { return value; }
    void SetValue(bool value) { this->value = value; }
private:
    bool value;
};

#endif /* B8751227_E850_4FDC_8820_01E664E85DB6 */
