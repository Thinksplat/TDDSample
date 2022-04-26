#include <gtest/gtest.h>
#include "lib/IBooleanProvider.h"

class MockBoolean : IBooleanProvider
{
public:
    MockBoolean(bool value) : value(value) {}
    bool GetBool() { return value; }
private:
    bool value;
};

// Demonstrate some basic assertions.
TEST(Interface, BasicInherientance)
{
    MockBoolean mock(true);
    auto value = mock.GetBool();
    ASSERT_TRUE(value);
}