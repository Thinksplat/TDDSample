#include <gtest/gtest.h>
#include "lib-behaviour/OnOff.h"
#include "WalkingTime.h"
#include "MockIntegerConsumer.h"
#include "MockIntegerConsumerLambda.h"
#include "IntegerConsumerRecorder.h"
#include "lib/EqualTimeInterval.h"
#include "tests/MockTimerLambda.h"

TEST(Behaviour, OnOffPattern)
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