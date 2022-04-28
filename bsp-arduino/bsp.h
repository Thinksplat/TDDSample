#ifndef C83C0921_98FB_431B_890C_4FFD9A81CD47
#define C83C0921_98FB_431B_890C_4FFD9A81CD47

#include "lib/stdint.h"
#include "lib/IBSP.h"
#include "lib/IBooleanProvider.h"
#include "lib/ITimeProvider.h"
#include "lib/IIntegerConsumer.h"
#include "ArduinoWritePin.h"
#include "ArduinoPinReader.h"
#include "ArduinoTime.h"
#include <Arduino.h>

class TrueBooleanProvider : public IBooleanProvider
{
    public:
    bool GetBool() override
    {
        return true;
    }
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
    ArduinoPinReader pin0;
    ArduinoWritePin led;
};

#endif /* C83C0921_98FB_431B_890C_4FFD9A81CD47 */
