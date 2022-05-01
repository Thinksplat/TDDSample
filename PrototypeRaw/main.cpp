#include <Arduino.h>

// Our ints that we work will will be signed 16 bit values
// to fit the full range of 0-255 that the bus requires,
// while allowing negative numbers for error values.
typedef int16_t inttype;
// Time is unsigned 32 bit 0 -> 2^32-1
typedef uint32_t timetype;

static const int pin0 = 0;
static const int pin1 = 1;
static const int pin2 = 2;
static const int pin3 = 3;
static const int transmitPin = 4;
static const timetype STABLE_TIME = 20 * 1000; // 20ms
static const timetype OneSecond = 1000000;
static const timetype TRANSMIT_WAIT_TIME = OneSecond;

// This is really valuable so we're going to reimplement it
class Timer
{
public:
    Timer(timetype timeout_us) : timeout_us(timeout_us)
    {
        Reset();
    }
    bool HasExpired()
    {
        return Elapsed() < timeout_us;
    }
    void Reset()
    {
        starttime = micros();
    }

protected:
    timetype Elapsed()
    {
        // works for overflow.  Inverted subtraction returns the correct
        // positive value.
        return micros() - starttime;
    }
    const timetype timeout_us;
    timetype starttime;
};

bool isTransmitting()
{
    return digitalRead(transmitPin) == HIGH;
}

// Returns 1 when it's high, -1 if timed out
inttype waitForTransmit(timetype timeout)
{
    Timer timer(timeout);
    while (!timer.HasExpired())
    {
        if (isTransmitting())
        {
            return 1;
        }
    }
    return -1;
}

inttype ReadNibble()
{
    return digitalRead(pin0) << 0 |
           digitalRead(pin1) << 1 |
           digitalRead(pin2) << 2 |
           digitalRead(pin3) << 3;
}

inttype ReadStableNibble()
{
    inttype value = -1;

    Timer timer(STABLE_TIME);
    while (isTransmitting())
    {
        auto newvalue = ReadNibble();
        if (newvalue != value)
        {
            value = newvalue;
            timer.Reset();
        }
        if (timer.HasExpired())
        {
            return value;
        }
    }
    return -1;
}

inttype ReadLastStableNibble()
{
    inttype lastvalue = -1;

    while (isTransmitting())
    {
        auto thisvalue = ReadStableNibble();
        if (lastvalue >= 0)
        {
            lastvalue = thisvalue;
        }
    }
    return lastvalue;
}

inttype readValue()
{
    if (waitForTransmit(TRANSMIT_WAIT_TIME) < 0)
    {
        return -2;
    }

    auto low_nibble = ReadStableNibble();
    auto high_nibble = ReadLastStableNibble();

    if (low_nibble < 0 || high_nibble < 0)
    {
        return -1;
    }

    return (high_nibble << 4) | low_nibble;
}

void setup()
{
    // Initialize the board
    // Setup all the pin outputs inputs stuff like that
    pinMode(pin0, INPUT);
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
    pinMode(pin3, INPUT);
    pinMode(transmitPin, INPUT);
}

void loop()
{
    auto value = readValue();
    Serial.println(value);
}