#include <gtest/gtest.h>
#include "MockIntegerLambda.h"
#include "MockBooleanLambda.h"
#include "MockTimerLambda.h"
#include "lib/StableInteger.h"

// Demonstrate some basic assertions.
TEST(StableInteger, Instantiation)
{
    MockIntegerLambda mockInt([]()
                              { return 0; });
    MockTimerLambda mockTimer([]()
                              { return true; });
    MockBooleanLambda mockBoolean([]()
                                  { return true; });
    StableInteger stable(mockInt, mockBoolean, mockTimer);
}

// No need to test the behaviour because it's pass-through behaviour