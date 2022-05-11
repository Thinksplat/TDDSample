#ifndef BE9BF4DE_14F1_49FA_93AD_8ABE32F21AAC
#define BE9BF4DE_14F1_49FA_93AD_8ABE32F21AAC

#include "interface/IAudioProvider.h"
#include "math.h"

template <typename T>
class SinAudioProvider : public IAudioProvider_T<T> {
    public:
    SinAudioProvider(double frequency, double phase=0.0) : frequency(frequency), x(phase) {}
    
    bool Provide(T &buffer, uint32_t count) override {
        for (uint32_t i = 0; i < count; ++i) {
            double value = sin(x);
            x += 2 * M_PI / IAudioProviderBase::samplerate * frequency;
            // Keep x in the range 0 to 2*pi
            if(x > 2 * M_PI) {
                x -= 2 * M_PI;
            }
            int16_t sample = (int16_t)(value * 32767);
            buffer[i*2] = sample; // left channel
            buffer[i*2+1] = sample; // right channel
        }
        return true; // keep going
    }
    private:
    double frequency;
    double x;
};

#endif /* BE9BF4DE_14F1_49FA_93AD_8ABE32F21AAC */
