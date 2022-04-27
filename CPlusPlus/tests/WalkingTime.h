#ifndef D40B24E8_1934_45AF_BCB7_E807FFCF7114
#define D40B24E8_1934_45AF_BCB7_E807FFCF7114

class WalkingTime : public ITimeProvider
{
public:
    uint32_t GetMicroseconds() override
    {
        return time++;
    }
    uint32_t GetTime()
    {
        return time;
    }
    void Reset() {
        time = 0;
    }
protected:
    uint32_t time = 0;
};

#endif /* D40B24E8_1934_45AF_BCB7_E807FFCF7114 */
