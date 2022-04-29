#include <gtest/gtest.h>
#include "lib-behaviour/OnOff.h"
#include "WalkingTime.h"
#include "MockIntegerConsumer.h"
#include "IntegerConsumerRecorder.h"
#include "lib/EqualTimeInterval.h"
#include "tests/MockTimerLambda.h"

// Demonstrate some basic assertions.
TEST(Behaviour, OnOff)
{
    WalkingTime time;
    IntegerConsumerRecorder led;
    EqualTimeInterval etw(time);
    auto waiter = etw.CreateWaiter(100);

    ASSERT_LT(time.GetTime(), 10);
    Behaviour::OnOff(led, waiter);
    // Time should be somewhere between 200 and 203
    ASSERT_GE(time.GetTime(), 200);
    ASSERT_LE(time.GetTime(), 203);

    // The pattern should have two on off pairs.
    ASSERT_EQ(led.Values().size(), 2);
}

TEST(Behavior, OnOffPattern)
{
    std::vector<std::string> pattern;

    MockTimerLambda timer([&pattern]()
                          { pattern.push_back("wait"); 
                                    return true; });

    MockIntegerConsumerLambda led([&pattern](int16_t value)
                                  { pattern.push_back(value ? "on" : "off"); });

    Behaviour::OnOff(led, timer);

    // Validate the expected pattern of starting with an on, waiting, off, then waiting
    ASSERT_EQ(pattern.size(),4);
    ASSERT_EQ(pattern[0],"on");
    ASSERT_EQ(pattern[1],"wait");
    ASSERT_EQ(pattern[2],"off");
    ASSERT_EQ(pattern[3],"wait");

}