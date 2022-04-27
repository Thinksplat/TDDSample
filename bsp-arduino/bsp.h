#ifndef C83C0921_98FB_431B_890C_4FFD9A81CD47
#define C83C0921_98FB_431B_890C_4FFD9A81CD47

#include "lib/stdint.h"
#include "lib/IBSP.h"
#include "lib/IBooleanProvider.h"
#include "lib/ITimeProvider.h"
#include "lib/IIntegerConsumer.h"
#include <Arduino.h>

class ArduinoTime : public ITimeProvider
{
public:
    ArduinoTime()
    {
    }

    uint32_t GetMicroseconds() override
    {
        return micros();
    }
};

class TrueBooleanProvider : public IBooleanProvider
{
    public:
    bool GetBool() override
    {
        return true;
    }
};

class ArduinoPin : public IBooleanProvider
{
public:
    ArduinoPin(int pin) : pin(pin)
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

class BSP : IBSP
{
public:
    BSP() : pin0(5), led(LED_BUILTIN)
    {
    }

    ITimeProvider &Time()
    {
        return time;
    }

    IIntegerConsumer &LED()
    {
        return led;
    }

    IBooleanProvider &Pin0()
    {
        return pin0;
    }

    IBooleanProvider &KeepRunning() {
        return keep_running;
    }

private:
    TrueBooleanProvider keep_running;
    ArduinoTime time;
    ArduinoPin pin0;
    ArduinoWritePin led;
};

#endif /* C83C0921_98FB_431B_890C_4FFD9A81CD47 */
