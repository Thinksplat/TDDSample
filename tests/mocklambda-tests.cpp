#include <gtest/gtest.h>
#include <functional>
#include "interface/IIntegerProvider.h"
#include "MockIntegerLambda.h"
#include "MockBooleanLambda.h"
#include "MockTimeLambda.h"

// Demonstrate some basic assertions.
TEST(MockLambda, BasicFunctionality) {
    MockIntegerLambda mock([]() { return 5; });

    IIntegerProvider &provider = mock;
    auto value = provider.GetInteger();

    ASSERT_EQ(value, 5);
}

TEST(MockLambda, BooleanFunctionality) {
    MockBooleanLambda mock([]() { return true; });

    IBooleanProvider &provider = mock;
    auto value = provider.GetBool();

    ASSERT_TRUE(value);
}

TEST(MockLambda, TimeFunctionality) {
    MockTimeLambda mock([]() { return 47; });

    ITimeProvider &provider = mock;
    auto value = provider.GetMicroseconds();

    ASSERT_EQ(value, 47);
}

// Demonstrate some basic assertions.
TEST(MockLambda, ExternalBinding) {
    int ret = 314;
    MockIntegerLambda mock([&ret]()
                           { return ret; });

    IIntegerProvider &provider = mock;

    auto value = provider.GetInteger();
    ASSERT_EQ(value, ret);

    ret = 512;
    value = provider.GetInteger();
    ASSERT_EQ(value, ret);

}