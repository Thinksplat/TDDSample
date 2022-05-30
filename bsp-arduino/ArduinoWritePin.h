#ifndef CBBFF31D_8C43_4472_9AED_77993103900F
#define CBBFF31D_8C43_4472_9AED_77993103900F

#include "interface/IBooleanConsumer.h"
#include <Arduino.h>

class ArduinoWritePin : public IBooleanConsumer
{
public:
    ArduinoWritePin(int pin) : pin(pin)
    {
        pinMode(pin, OUTPUT);
    }

    void Consume(bool value) override
    {
        digitalWrite(pin, value ? HIGH : LOW);
    }

private:
    int pin;
};

#endif /* CBBFF31D_8C43_4472_9AED_77993103900F */
