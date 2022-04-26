#include <gtest/gtest.h>
#include "lib/IBooleanProvider.h"
#include "lib/IIntegerProvider.h"

class MockBoolean : IBooleanProvider
{
public:
    MockBoolean(bool value) : value(value) {}
    bool GetBool() override { return value; }
    void SetValue(bool value) { this->value = value; }
private:
    bool value;
};

class MockInteger : IIntegerProvider {
public:
    MockInteger(int16_t value) : value(value) {}
    int16_t GetInteger() override { return value; }
    void SetValue(int16_t value) { this->value = value; }
private:
    int16_t value;
};

// Demonstrate some basic assertions.
TEST(Interface, MockBooleanBasicInherientance)
{
    MockBoolean mock(true);
    auto value = mock.GetBool();
    ASSERT_TRUE(value);

    mock.SetValue(false);
    value = mock.GetBool();
    ASSERT_FALSE(value);
}

// Demonstrate some basic assertions.
TEST(Interface, MockIntegerBasicInherientance)
{
    MockInteger mock(1);
    auto value = mock.GetInteger();
    ASSERT_EQ(value, 1);

    mock.SetValue(2);
    value = mock.GetInteger();
    ASSERT_EQ(value, 2);
}