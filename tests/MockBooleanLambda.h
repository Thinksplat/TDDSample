#ifndef DA77C53E_D1A9_45C0_840C_8A4FC0A17BBE
#define DA77C53E_D1A9_45C0_840C_8A4FC0A17BBE

#include <functional>
#include "interface/IBooleanProvider.h"

class MockBooleanLambda : public IBooleanProvider
{
    public:
    // constructor takes a lambda
    MockBooleanLambda(std::function<bool()> lambda) : lambda(lambda) {}
    bool GetBool() override { return lambda(); }
    private:
    std::function<bool()> lambda;
};

#endif /* DA77C53E_D1A9_45C0_840C_8A4FC0A17BBE */
