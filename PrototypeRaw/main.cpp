#include <Arduino.h>

static const int pin0 = 0;
static const int pin1 = 1;
static const int pin2 = 2;
static const int pin3 = 3;
static const int transmitPin = 4;
static const uint32_t STABLE_TIME = 20 * 1000; // 20ms
static const uint32_t OneSecond = 1000000;
static const uint32_t TRANSMIT_WAIT_TIME = OneSecond;

// This is really valuable so we're going to reimplement it
class Timer
{
public:
    Timer(uint32_t timeout_us) : timeout_us(timeout_us)
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
    uint32_t Elapsed()
    {
        // works for overflow.  Inverted subtraction returns the correct
        // positive value.
        return micros() - starttime;
    }
    const uint32_t timeout_us;
    uint32_t starttime;
};

bool isTransmitting()
{
    return digitalRead(transmitPin) == HIGH;
}

// Returns 1 when it's high, -1 if timed out
int16_t waitForTransmit(uint32_t timeout)
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

int16_t ReadNibble()
{
    return digitalRead(pin0) << 0 |
           digitalRead(pin1) << 1 |
           digitalRead(pin2) << 2 |
           digitalRead(pin3) << 3;
}

int16_t ReadStableNibble()
{
    int16_t value = -1;

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

int16_t ReadLastStableNibble()
{
    int16_t lastvalue = -1;

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

int16_t
readValue()
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
}

void loop()
{
    // Initialize the board
    // Setup all the pin outputs inputs stuff like that
    pinMode(pin0, INPUT);
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
    pinMode(pin3, INPUT);
    pinMode(transmitPin, INPUT);

    while (true)
    {
        auto value = readValue();
        Serial.println(value);
    }
}