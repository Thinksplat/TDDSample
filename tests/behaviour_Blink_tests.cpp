#include <gtest/gtest.h>
#include "lib-behaviour/Blink.h"
#include "WalkingTime.h"
#include "MockIntegerConsumer.h"
#include "IntegerConsumerRecorder.h"
#include "lib/EqualTimeWaiter.h"

// Demonstrate some basic assertions.
TEST(Behaviour, Blink) {
    WalkingTime time;
    IntegerConsumerRecorder led;
    EqualTimeWaiter etw(time);
    
    auto waiter = etw.Create(100);

    ASSERT_LT(time.GetTime(), 10);

    Behaviour::Blink(led, waiter, 3);
    // Should have turned on off 6 times
    ASSERT_EQ(led.Values().size(), 6);
    // Time between 600 and 603
    ASSERT_GE(time.GetTime(), 600);
    ASSERT_LE(time.GetTime(), 603);
}