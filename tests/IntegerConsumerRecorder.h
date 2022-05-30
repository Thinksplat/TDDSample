#ifndef F68871D7_58C1_4A18_BF48_B9079CBCD0B2
#define F68871D7_58C1_4A18_BF48_B9079CBCD0B2

#include "interface/IIntegerConsumer.h"
#include <vector>

class IntegerConsumerRecorder : public IIntegerConsumer, public IBooleanConsumer
{
public:
    void Consume(bool value) override {
        values.push_back(value ? 1 : 0);
    }
    void Consume(int16_t value) override
    {
        values.push_back(value);
    }
    const std::vector<int16_t> &Values() const
    {
        return values;
    }
    // reset
    void Reset()
    {
        values.clear();
    }

private:
    std::vector<int16_t> values;
};

#endif /* F68871D7_58C1_4A18_BF48_B9079CBCD0B2 */
