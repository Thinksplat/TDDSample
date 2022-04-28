#ifndef CBBFF31D_8C43_4472_9AED_77993103900F
#define CBBFF31D_8C43_4472_9AED_77993103900F

#include "lib/IIntegerConsumer.h"
#include <Arduino.h>

class ArduinoWritePin : public IIntegerConsumer
{
public:
    ArduinoWritePin(int pin) : pin(pin)
    {
        pinMode(pin, OUTPUT);
    }

    void Consume(int16_t value) override
    {
        digitalWrite(pin, value != 0 ? HIGH : LOW);
    }

private:
    int pin;
};

#endif /* CBBFF31D_8C43_4472_9AED_77993103900F */
