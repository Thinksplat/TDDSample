#ifndef CDFB6AFA_714F_48C7_841D_106B86C9F2BB
#define CDFB6AFA_714F_48C7_841D_106B86C9F2BB

#include "interface/IBooleanProvider.h"
#include <Arduino.h>

class ArduinoPinReader : public IBooleanProvider
{
public:
    ArduinoPinReader(int pin) : pin(pin)
    {
        pinMode(pin, INPUT);
    }

    bool GetBool() override
    {
        return digitalRead(pin) == HIGH;
    }

private:
    int pin;
};

#endif /* CDFB6AFA_714F_48C7_841D_106B86C9F2BB */
