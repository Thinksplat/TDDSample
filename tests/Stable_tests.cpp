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

TEST(Stable, InValidIsValidIsFalseOnEntry)
{
    MockIntegerLambda mockInt([]()
                              { return 17; });
    MockTimerLambda mockTimer([]()
                              { return true; });
    MockBooleanLambda isValid([]()
                              { return false; });

    auto value = Behaviour::Stable(mockInt, isValid, mockTimer);
    EXPECT_EQ(-1, value);
}

TEST(Stable, IfTheValueEverProvidesNegativeReturnNegativeImmediately)
{
    int count = 10;
    int readcount = 0;
    // Decrement count every time we read a value and keep
    // track.
    const int error_value = -15;
    MockIntegerLambda mockInt([&readcount, &count]()
                              { 
                                  readcount++;
                                  count--;
                                  return count < 0 ? error_value : count; });
    // Timer never expires
    MockTimerLambda mockTimer([]()
                              { return false; });
    MockBooleanLambda isValid([]()
                              { return true; });

    auto value = Behaviour::Stable(mockInt, isValid, mockTimer);
    // Must have returned an error
    EXPECT_LT(value, 0);
    // Must return the error value from the internal read
    EXPECT_EQ(value, error_value);
    EXPECT_GT(readcount, 5); // probably equal to 10 or 11, but we don't care about the implementation here
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