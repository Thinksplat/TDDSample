#ifndef DD28A152_FF93_4910_B1EE_0C4D6915D5D8
#define DD28A152_FF93_4910_B1EE_0C4D6915D5D8

#include "interface/IAudioProvider.h"

class Assignmenter
{
public:
    int16_t value = 0;
    void operator=(int16_t value)
    {
        this->value = value;
    }
};

class BoundTester
{
public:
    BoundTester(int32_t lower, int32_t upper)
    {
        this->lower = lower;
        this->upper = upper;
        min = std::numeric_limits<int32_t>::max();
        max = std::numeric_limits<int32_t>::min();
    }
    Assignmenter assign;
    Assignmenter &operator[](int32_t index)
    {
        if (index < lower || index >= upper)
        {
            throw std::out_of_range("index out of range");
        }
        min = std::min(min, index);
        max = std::max(max, index);
        return assign;
    }
    int32_t Min()
    {
        return min;
    }
    int32_t Max()
    {
        return max;
    }

private:
    int32_t lower;
    int32_t upper;

    int32_t min, max;
};

static void AudioTestBound(IAudioProvider_T<BoundTester> &audio)
{
    BoundTester tester(0, 8192);

    audio.Provide(tester, 4096);

    ASSERT_EQ(tester.Min(), 0);
    ASSERT_EQ(tester.Max(), 8191);
}

#endif /* DD28A152_FF93_4910_B1EE_0C4D6915D5D8 */
