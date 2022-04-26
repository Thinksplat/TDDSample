#ifndef AB5BB5FE_275E_496C_ACAA_D2815B17C4B3
#define AB5BB5FE_275E_496C_ACAA_D2815B17C4B3

#include "lib/IIntegerProvider.h"

class MockInteger : public IIntegerProvider {
public:
    MockInteger(int16_t value) : value(value) {}
    int16_t GetInteger() override { return value; }
    void SetValue(int16_t value) { this->value = value; }
private:
    int16_t value;
};

#endif /* AB5BB5FE_275E_496C_ACAA_D2815B17C4B3 */
