#ifndef A9CF6D59_0CED_454A_8B64_A9D9CDD92F45
#define A9CF6D59_0CED_454A_8B64_A9D9CDD92F45

#include "lib/ITimeProvider.h"
#include "tests/MockTimeLambda.h"
#include "tests/MockBooleanLambda.h"
// include files for gettimeofday
#include <sys/time.h>

class BSP {
    public:
        BSP() : 
            timemock(LinuxNumberOfMicroseconds),
            pin0([this]() { 
                return this->Time().GetMicroseconds() / 1000000 % 2 == 0; 
                })
            {}

        ITimeProvider &Time() {
            return timemock;
        }

        IBooleanProvider &Pin0() {
            return pin0;
        }

    private:
        static uint32_t LinuxNumberOfMicroseconds() {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return tv.tv_sec * 1000000 + tv.tv_usec;
        }

        MockTimeLambda timemock;
        MockBooleanLambda pin0;
};

#endif /* A9CF6D59_0CED_454A_8B64_A9D9CDD92F45 */
