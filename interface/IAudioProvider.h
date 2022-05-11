#ifndef BD3115D2_0733_4317_B312_3FA843AF7C79
#define BD3115D2_0733_4317_B312_3FA843AF7C79

#include "lib/stdint.h"

class IAudioProviderBase
{
public:
    static const uint32_t samplerate = 44100;
    static const uint8_t channels = 2;
};

// Basic audio provider without any external playhead designator.
// Classes themselves keep track of their own playhead
template <typename T>
class IAudioProvider_T : public IAudioProviderBase
{
    public:
    // returns false when the provider is done
    virtual bool Provide(T &buffer, uint32_t count) = 0;
};

#endif /* BD3115D2_0733_4317_B312_3FA843AF7C79 */
