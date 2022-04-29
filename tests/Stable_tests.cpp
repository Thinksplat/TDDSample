#include <gtest/gtest.h>
#include "MockIntegerLambda.h"
#include "MockBooleanLambda.h"
#include "MockTimerLambda.h"
#include "lib-behaviour/Stable.h"

TEST(Stable, ImmediateInvalid)
{
    MockIntegerLambda mockInt([]()
                              { return 0; });
    MockTimerLambda mockTimer([]()
                              { return true; });
    MockBooleanLambda isValid([]()
                                  { return false; });

    auto value = Behaviour::Stable(mockInt, isValid, mockTimer);
    EXPECT_EQ(-1, value);
}

TEST(Stable, ValidWhenTimerExpires)
{
    MockIntegerLambda mockInt([]()
                              { return 17; });
    MockTimerLambda mockTimer([]()
                              { return true; });
    MockBooleanLambda isValid([]()
                                  { return true; });

    auto value = Behaviour::Stable(mockInt, isValid, mockTimer);
    EXPECT_EQ(17, value);
}

TEST(Stable, ChangeWithATimerExpireReturnsChangedValue)
{
    int count = 0;
    MockIntegerLambda mockInt([&count]()
                              { return count < 10 ? 11 : 22; });
    MockTimerLambda mockTimer([&count]()
                              { return (count++) > 20; }); // Expires at time 20 which should set the value to 22
    MockBooleanLambda isValid([]()
                                  { return true; });

    auto value = Behaviour::Stable(mockInt, isValid, mockTimer);
    EXPECT_EQ(22, value);
}