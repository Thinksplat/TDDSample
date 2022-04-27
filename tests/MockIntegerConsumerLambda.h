#ifndef DDFD5FCE_CCD0_4004_9E8E_D200DDC27617
#define DDFD5FCE_CCD0_4004_9E8E_D200DDC27617

#include "lib/IIntegerConsumer.h"

class MockIntegerConsumerLambda : public IIntegerConsumer
{
public:
    MockIntegerConsumerLambda(std::function<void(int32_t)> lambda) : lambda(lambda) {}
    void Consume(int32_t value) override { lambda(value); }
};

#endif /* DDFD5FCE_CCD0_4004_9E8E_D200DDC27617 */
