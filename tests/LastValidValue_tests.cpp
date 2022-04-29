#include <gtest/gtest.h>
#include "MockIntegerLambda.h"
#include "MockBooleanLambda.h"
#include "MockTimerLambda.h"
#include "lib-behaviour/LastValidValue.h"

TEST(LastValidValue, ImmediateInvalid)
{
    MockIntegerLambda mockInt([]()
                              { return 0; });
    MockBooleanLambda isValid([]()
                              { return false; });

    auto value = Behaviour::LastValidValue(isValid, mockInt);
    EXPECT_EQ(-1, value);
}

TEST(LastValidValue, OneValid)
{
    int count = 0;
    MockIntegerLambda mockInt([]()
                              { return 0; });
    MockBooleanLambda isValid([&count]()
                              { return (count++) < 10; });

    auto value = Behaviour::LastValidValue(isValid, mockInt);
    EXPECT_EQ(0, value);
}

TEST(LastValidValue, LastValid)
{
    int count = 0;
    MockIntegerLambda mockInt([&count]()
                              { return count; });
    MockBooleanLambda isValid([&count]()
                              { return (count++) < 10; });

    auto value = Behaviour::LastValidValue(isValid, mockInt);
    EXPECT_EQ(10, value);
}

TEST(LastValidValue, InvalidStuffAtEndIgnored)
{
    int count = 0;
    MockIntegerLambda mockInt([&count]()
                              { return count <= 5 ? count : -1; });
    MockBooleanLambda isValid([&count]()
                              { return (count++) < 10; });

    auto value = Behaviour::LastValidValue(isValid, mockInt);
    EXPECT_EQ(5, value);
}
