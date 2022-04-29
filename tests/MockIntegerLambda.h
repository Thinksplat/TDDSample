#ifndef FB6EFA69_7858_43C6_A633_206114D4A6B2
#define FB6EFA69_7858_43C6_A633_206114D4A6B2

#include <functional>
#include "interface/IIntegerProvider.h"

class MockIntegerLambda : public IIntegerProvider
{
    public:
    // constructor takes a lambda
    MockIntegerLambda(std::function<int16_t()> lambda) : lambda(lambda) {}
    int16_t GetInteger() override { return lambda(); }
    private:
    std::function<int16_t()> lambda;
};


#endif /* FB6EFA69_7858_43C6_A633_206114D4A6B2 */
