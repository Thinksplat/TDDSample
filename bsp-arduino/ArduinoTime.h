#ifndef A0D24B8A_35A3_4810_A813_4EAB563D2605
#define A0D24B8A_35A3_4810_A813_4EAB563D2605

#include "interface/ITimeProvider.h"
#include <Arduino.h>

class ArduinoTime : public ITimeProvider
{
public:
    uint32_t GetMicroseconds() override
    {
        return micros();
    }
};

#endif /* A0D24B8A_35A3_4810_A813_4EAB563D2605 */
