#include <gtest/gtest.h>
#include "lib-behaviour/Wait.h"
#include "WalkingTime.h"

// Demonstrate some basic assertions.
TEST(Behaviour, Wait) {
    WalkingTime time;
    
    time.Reset();
    ASSERT_EQ(time.GetTime(), 0);
    Behaviour::Wait(time, 100);
    // Time should be somewhere between 100 and 103
    ASSERT_GE(time.GetTime(), 100);
    ASSERT_LE(time.GetTime(), 103);
    
}