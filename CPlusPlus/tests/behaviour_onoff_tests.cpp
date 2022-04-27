#include <gtest/gtest.h>
#include "lib-behaviour/OnOff.h"
#include "WalkingTime.h"
#include "MockIntegerConsumer.h"
#include "IntegerConsumerRecorder.h"

// Demonstrate some basic assertions.
TEST(Behaviour, OnOff) {
    WalkingTime time;
    IntegerConsumerRecorder led;
    
    time.Reset();
    ASSERT_EQ(time.GetTime(), 0);
    Behaviour::OnOff(led, time, 100);
    // Time should be somewhere between 200 and 203
    ASSERT_GE(time.GetTime(), 200);
    ASSERT_LE(time.GetTime(), 203);
    
    // The pattern should have two on off pairs.
    ASSERT_EQ(led.Values().size(), 2);
}