#ifndef B8751227_E850_4FDC_8820_01E664E85DB6
#define B8751227_E850_4FDC_8820_01E664E85DB6

#include "interface/IBooleanProvider.h"
#include "interface/IBooleanConsumer.h"

class MockBoolean : public IBooleanProvider
{
public:
    MockBoolean(bool value=0) : value(value) {}
    bool GetBool() override { return value; }
    void SetValue(bool value) { this->value = value; }
private:
    bool value;
};

class MockBooleanConsumer : public IBooleanConsumer {
    public:
    void Consume(bool value) override {
        this->value = value;
    }
    private:
    bool value;
};

#endif /* B8751227_E850_4FDC_8820_01E664E85DB6 */
