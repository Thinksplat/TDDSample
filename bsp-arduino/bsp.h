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
#include <Arduino.h>


class ForeverTimer : public ITimer {
public:
    bool HasExpired() override {
        return false;
    }
    void Reset() {

    }
};

class SerialConsumer: public IIntegerConsumer {
    public:
        void Consume(int16_t value) override {
            Serial.println(value);
        }
};

class BSP : public IBSP
{
public:
    BSP() : pin0(5), pin1(6), pin2(7), pin3(8), enable(9), led(LED_BUILTIN)
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

    ITimer &RunningTimer() {
        return keep_running;
    }

    IIntegerConsumer &Consumer() {
        return consumer;
    }

private:
    ForeverTimer keep_running;
    ArduinoTime time;
    ArduinoPinReader pin0, pin1, pin2, pin3;
    ArduinoPinReader enable;
    ArduinoWritePin led;
    SerialConsumer consumer;
};

#endif /* C83C0921_98FB_431B_890C_4FFD9A81CD47 */
