#include <gtest/gtest.h>
#include "MockBoolean.h"
#include "MockInteger.h"

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