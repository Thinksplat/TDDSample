#ifndef AFA126F5_41C7_4478_93CC_4E66DFC3D695
#define AFA126F5_41C7_4478_93CC_4E66DFC3D695

#include "lib/IIntegerConsumer.h"

class MockIntegerConsumer : public IIntegerConsumer
{
public:
    int32_t Value() const
    {
        return value;
    }
    void Consume(int32_t value) override
    {
        this->value = value;
    }

protected:
    int32_t value = 0;
};

#endif /* AFA126F5_41C7_4478_93CC_4E66DFC3D695 */
