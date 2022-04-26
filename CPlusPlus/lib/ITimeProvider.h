#ifndef A63C4ED0_3C93_42E0_94CE_FB5B8965FB6C
#define A63C4ED0_3C93_42E0_94CE_FB5B8965FB6C

#include "lib/stdint.h"

class ITimeProvider {
    public:
    // Returns the number of microseconds since some arbitrary point in time.
    // Rolls over after 2^32-1 microseconds or ~4300 seconds or ~71.5 minutes
    virtual uint32_t GetMicroseconds() = 0;
};

#endif /* A63C4ED0_3C93_42E0_94CE_FB5B8965FB6C */
