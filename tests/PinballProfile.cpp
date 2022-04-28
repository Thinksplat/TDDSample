#include "Sim.h"

class PinballProfile
{
    static void SetData(Sim &sim, int data, uint32_t time)
    {
        sim.AddPoint(Sim::PINS::DATA0, data & 0x1, time);
        sim.AddPoint(Sim::PINS::DATA1, data & 0x2, time);
        sim.AddPoint(Sim::PINS::DATA2, data & 0x4, time);
        sim.AddPoint(Sim::PINS::DATA3, data & 0x8, time);
    }

public:
    static void GenPinball(Sim &sim, uint32_t before, uint32_t time1on, uint32_t time2on, int noisetime, int nibble0, int nibble1)
    {
        sim.AddPoint(Sim::TRANSMIT, true, before);
        sim.AddPoint(Sim::TRANSMIT, false, before + time1on + time2on);

        // Half the noise time (noise straddles the transitions)
        auto noisetimed2 = noisetime / 2;

        // Clean data
        SetData(sim, nibble0, before + noisetimed2 + 1);
        SetData(sim, nibble1, before + time1on + noisetimed2 + 1);
        SetData(sim, 0, before + time1on + time2on + noisetimed2 + 1);

        // Add noise
        for (int i = 0; i < noisetime; ++i)
        {
            // random int between 0 and 15
            int noise = rand() % 16;
            SetData(sim, noise, before - noisetimed2 + i);
            noise = rand() % 16;
            SetData(sim, noise, before + time1on - noisetimed2 + i);
            noise = rand() % 16;
            SetData(sim, noise, before + time1on + time2on - noisetimed2 + i);
        }
    }
};
