#ifndef DDFD5FCE_CCD0_4004_9E8E_D200DDC27617
#define DDFD5FCE_CCD0_4004_9E8E_D200DDC27617

#include "interface/IIntegerConsumer.h"
#include <functional>

class MockIntegerConsumerLambda : public IIntegerConsumer
{
public:
    MockIntegerConsumerLambda(std::function<void(IIntegerConsumer::value_type)> lambda) : lambda(lambda) {}
    void Consume(IIntegerConsumer::value_type value) override { lambda(value); }

private:
    std::function<void(IIntegerConsumer::value_type)> lambda;
};

#endif /* DDFD5FCE_CCD0_4004_9E8E_D200DDC27617 */
