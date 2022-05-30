#ifndef DA77C53E_D1A9_45C0_840C_8A4FC0A17BBE
#define DA77C53E_D1A9_45C0_840C_8A4FC0A17BBE

#include <functional>
#include "interface/IBooleanProvider.h"
#include "interface/IBooleanConsumer.h"

class MockBooleanLambda : public IBooleanProvider
{
    public:
    // constructor takes a lambda
    MockBooleanLambda(std::function<bool()> lambda=&True) : lambda(lambda) {}
    bool GetBool() override { return lambda(); }
    private:
    std::function<bool()> lambda;
    static bool True() {
        return true;
    }
};

class MockBooleanLambdaConsumer : public IBooleanConsumer
{
    public:
    // constructor takes a lambda
    MockBooleanLambdaConsumer(std::function<void(bool)> lambda=&Eat) : lambda(lambda) {}
    void Consume(bool value) override { lambda(value); }
    private:
    std::function<void(bool)> lambda;
    static void Eat(bool) {
    }
};

#endif /* DA77C53E_D1A9_45C0_840C_8A4FC0A17BBE */
