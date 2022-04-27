#ifndef C83C0921_98FB_431B_890C_4FFD9A81CD47
#define C83C0921_98FB_431B_890C_4FFD9A81CD47

#include "lib/stdint.h"
#include "lib/IBooleanProvider.h"
#include "lib/ITimeProvider.h"

class ArduinoTime : public ITimeProvider
{
public:
    ArduinoTime() 
    {}

    uint32_t GetMicroseconds() override
    {
        return 0;
    }
};

class ArduinoPin : public IBooleanProvider
{
public:
    ArduinoPin(int pin) : pin(pin)
    {
    }

    bool GetBool() override
    {
        return false;
    }

private:
    int pin;
};

class BSP
{
public:
    BSP() : pin0(5)
    {
    }

    ITimeProvider &Time()
    {
        return time;
    }

    IBooleanProvider &Pin0()
    {
        return pin0;
    }

private:
    ArduinoTime time;
    ArduinoPin pin0;
};

#endif /* C83C0921_98FB_431B_890C_4FFD9A81CD47 */
