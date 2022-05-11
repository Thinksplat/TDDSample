#include <gtest/gtest.h>
#include <limits>
#include "lib/SinAudioProvider.h"
#include "AudioTestBound.h"

class ZeroCrossingCounter
{
public:
    template <class T>
    static ZeroCrossingCounter Create(const T &samples)
    {
        ZeroCrossingCounter counter;
        for (size_t i = 0; i < samples.size(); i += IAudioProviderBase::channels)
        {
            counter.Sample(samples[i]);
        }
        return counter;
    }
    void Sample(int32_t value)
    {
        if (previous < 0 && value >= 0)
        {
            count++;
        }
        else if (previous >= 0 && value < 0)
        {
            count++;
        }
        previous = value;
    }
    int32_t Count()
    {
        return count;
    }

private:
    int32_t previous = 0;
    uint32_t count = 0;
};

// Demonstrate some basic assertions.
TEST(SinAudioProvider, BasicAssertions)
{
    SinAudioProvider<int16_t *> sap(440.0);

    std::vector<int16_t> buffer(4096 * IAudioProvider_T<int16_t>::channels);
    int16_t *buf = &buffer[0];
    sap.Provide(buf, 4096);
}

// Check the bounds
TEST(SinAudioProvider, Bounds)
{
    SinAudioProvider<BoundTester> sap(440.0, 0.0);
    AudioTestBound(sap);
}

// See that we get about 440 zero crossings in the first second
TEST(SinAudioProvider, ZeroCrossings)
{
    double frequency = 440.0;
    SinAudioProvider<int16_t *> sap(frequency, 0.1);

    std::vector<int16_t> samples(IAudioProviderBase::samplerate * IAudioProviderBase::channels);
    int16_t *ptr = &samples[0];
    sap.Provide(ptr, samples.size() / IAudioProviderBase::channels);

    auto counter = ZeroCrossingCounter::Create(samples);

    // Since it crosses up and down, we expect to see twice as many
    // as the frequency.
    int32_t expected_crossings = (int32_t)(frequency * 2);
    const int32_t tolerance = 2;
    ASSERT_GE(counter.Count(), expected_crossings - tolerance);
    ASSERT_LE(counter.Count(), expected_crossings + tolerance);
}