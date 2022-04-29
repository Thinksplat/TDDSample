#ifndef C8112EE8_BA4D_4599_B14E_357AFBF3E193
#define C8112EE8_BA4D_4599_B14E_357AFBF3E193

#include "interface/ITimeProvider.h"

class MockTimeProvider : public ITimeProvider
{
public:
    MockTimeProvider(uint32_t startTime) : startTime(startTime) {}
    uint32_t GetMicroseconds() override { return startTime; }
    void SetValue(uint32_t startTime) { this->startTime = startTime; }
private:
    uint32_t startTime;
};

#endif /* C8112EE8_BA4D_4599_B14E_357AFBF3E193 */
