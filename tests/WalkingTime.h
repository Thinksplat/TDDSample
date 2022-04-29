#ifndef D40B24E8_1934_45AF_BCB7_E807FFCF7114
#define D40B24E8_1934_45AF_BCB7_E807FFCF7114

#include "interface/ITimeProvider.h"

class WalkingTime : public ITimeProvider
{
public:
    uint32_t GetMicroseconds() override
    {
        return time++;
    }
    void SetTime(uint32_t t)
    {
        time = t;
    }
    uint32_t GetTime()
    {
        return time;
    }
    void Reset()
    {
        time = 0;
    }

protected:
    uint32_t time = 0;
};

#endif /* D40B24E8_1934_45AF_BCB7_E807FFCF7114 */
