#ifndef C0EFC7C9_E77D_484E_9F5F_B7D351AF2D1B
#define C0EFC7C9_E77D_484E_9F5F_B7D351AF2D1B

#include "lib/IBooleanProvider.h"
#include "lib/ITimeProvider.h"
#include <vector>
#include <algorithm>
#include <memory>

class SimLines
{
public:
    SimLines(IBooleanProvider &data0, IBooleanProvider &data1, IBooleanProvider &data2, IBooleanProvider &data3, IBooleanProvider &transmit) : data0(data0), data1(data1), data2(data2), data3(data3), transmit(transmit) {}
    IBooleanProvider &Data0()
    {
        return data0;
    }
    IBooleanProvider &Data1()
    {
        return data1;
    }
    IBooleanProvider &Data2()
    {
        return data2;
    }
    IBooleanProvider &Data3()
    {
        return data3;
    }
    IBooleanProvider &Transmit()
    {
        return transmit;
    }

protected:
    IBooleanProvider &data0;
    IBooleanProvider &data1;
    IBooleanProvider &data2;
    IBooleanProvider &data3;
    IBooleanProvider &transmit;
};

class SimPoint
{
public:
    SimPoint(int pin, bool value, uint32_t time) : pin(pin), value(value), time(time) {}
    // overload the operator<
    bool operator<(const SimPoint &r) const
    {
        return time < r.time;
    }

    int pin;
    bool value;
    uint32_t time;
};

class SimProfile
{
public:
    void AddPoint(int pin, bool value, uint32_t time)
    {
        points.push_back(SimPoint(pin, value, time));
        std::sort(points.begin(), points.end());
    }
    bool GetPin(int pin, uint32_t time)
    {
        bool value = false;

        // iterate through points
        for (auto it = points.begin(); it != points.end(); it++)
        {
            const auto &p = *it;

            if (p.time > time)
            {
                break;
            }
            if (p.pin == pin)
            {
                value = p.value;
            }
        }

        return value;
    }

    void ResetFull()
    {
        points.clear();
    }

protected:
    std::vector<SimPoint> points;
};

class SimPin : public IBooleanProvider
{
public:
    SimPin(int pin, SimProfile &profile, ITimeProvider &time) : pin(pin), profile(profile), time(time) {}
    virtual bool GetBool() override
    {
        return profile.GetPin(pin, time.GetMicroseconds());
    }

protected:
    int pin;
    SimProfile &profile;
    ITimeProvider &time;
};

class Accum
{
public:
    Accum(SimProfile &profile, int pin) : profile(profile), pin(pin) {}
    Accum &Next(bool value, uint32_t holdtime)
    {
        profile.AddPoint(pin, value, curtime);
        curtime += holdtime;
        return *this;
    }

private:
    uint32_t curtime = 0;
    SimProfile &profile;
    int pin;
};

// Simulates the digital inputs and outputs given a profile
class Sim
{
public:
    enum PINS
    {
        DATA0 = 0,
        DATA1 = 1,
        DATA2 = 2,
        DATA3 = 3,
        TRANSMIT = 4
    };

    Sim(ITimeProvider &time)
        : pin0(DATA0, profile, time),
          pin1(DATA1, profile, time),
          pin2(DATA2, profile, time),
          pin3(DATA3, profile, time),
          pin4(TRANSMIT, profile, time),
          lines(pin0, pin1, pin2, pin3, pin4), time(time)
    {
    }
    virtual ~Sim()
    {
    }

    SimLines &Lines()
    {
        return lines;
    }

    ITimeProvider &Time()
    {
        return time;
    }

    void AddPoint(PINS pin, bool value, uint32_t time)
    {
        profile.AddPoint(pin, value, time);
    }

    SimProfile &Profile()
    {
        return profile;
    }

    Accum Accumulate(int pin)
    {
        return Accum(profile, pin);
    }

protected:
    SimProfile profile;
    SimPin pin0, pin1, pin2, pin3, pin4;
    SimLines lines;
    ITimeProvider &time;
};

#endif /* C0EFC7C9_E77D_484E_9F5F_B7D351AF2D1B */
