#ifndef C83C0921_98FB_431B_890C_4FFD9A81CD47
#define C83C0921_98FB_431B_890C_4FFD9A81CD47

#include "lib/stdint.h"
#include "interface/IBSP.h"
#include "interface/IBooleanProvider.h"
#include "interface/ITimeProvider.h"
#include "interface/IIntegerConsumer.h"
#include "interface/ITimer.h"
#include "ArduinoWritePin.h"
#include "ArduinoPinReader.h"
#include "ArduinoTime.h"
#include "ArduinoSerialConsumer.h"
#include <Arduino.h>

// For some reason, for some platforms LED_BUILTIN isn't defined
// in Arduino.h
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

class ForeverTimer : public ITimer
{
public:
    bool HasExpired() override
    {
        return false;
    }
    void Reset()
    {
    }
};

class BSP : public IBSP
{
public:
    BSP() : pin0(PINBALL_PIN0), pin1(PINBALL_PIN1), pin2(PINBALL_PIN2), pin3(PINBALL_PIN3), enable(PINBALL_TRANSMIT_PIN), led(LED_BUILTIN)
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

    IBooleanProvider &Pin0() override
    {
        return pin0;
    }

    IBooleanProvider &Pin1() override
    {
        return pin1;
    }

    IBooleanProvider &Pin2() override
    {
        return pin2;
    }

    IBooleanProvider &Pin3() override
    {
        return pin3;
    }

    IBooleanProvider &Transmit() override
    {
        return enable;
    }

    ITimer &RunningTimer()
    {
        return keep_running;
    }

    IIntegerConsumer &Consumer()
    {
        return consumer;
    }

private:
    const static int PINBALL_PIN0 = 5;
    const static int PINBALL_PIN1 = 6;
    const static int PINBALL_PIN2 = 7;
    const static int PINBALL_PIN3 = 8;
    const static int PINBALL_TRANSMIT_PIN = 9;

    ForeverTimer keep_running;
    ArduinoTime time;
    ArduinoPinReader pin0, pin1, pin2, pin3;
    ArduinoPinReader enable;
    ArduinoWritePin led;
    ArduinoSerialConsumer consumer;
};

#endif /* C83C0921_98FB_431B_890C_4FFD9A81CD47 */
