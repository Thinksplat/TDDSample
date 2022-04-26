#ifndef EBEE678B_AF26_44F0_A0E2_E953FB4C238C
#define EBEE678B_AF26_44F0_A0E2_E953FB4C238C

#include <functional>
#include "lib/ITimeProvider.h"

class MockTimeLambda : public ITimeProvider
{
    public:
    // constructor takes a lambda
    MockTimeLambda(std::function<uint32_t()> lambda) : lambda(lambda) {}
    uint32_t GetMicroseconds() override { return lambda(); }
    private:
    std::function<uint32_t()> lambda;
};


#endif /* EBEE678B_AF26_44F0_A0E2_E953FB4C238C */
