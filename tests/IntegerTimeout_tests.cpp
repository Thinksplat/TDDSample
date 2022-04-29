#include <gtest/gtest.h>
#include "lib/IntegerTimeout.h"
#include "MockBoolean.h"
#include "MockBooleanLambda.h"
#include "MockInteger.h"
#include "MockTimerLambda.h"

// Demonstrate some basic assertions.
TEST(IntegerTimeout, Instantiation)
{
    MockBoolean isReady;
    MockInteger value;
    MockTimerLambda timeout;

    IntegerTimeout itimeout(value, isReady, timeout);
}

TEST(IntegerTimeout, DoesTimeoutCorrectly)
{
    MockBoolean isReady; // won't be ready
    MockInteger value(42);
    MockTimerLambda timeout; // default timer expires immediately

    IntegerTimeout itimeout(value, isReady, timeout);

    auto returnedvalue = itimeout.GetInteger();
    ASSERT_EQ(returnedvalue, -2);
}

TEST(IntegerTimeout, IfReadyOnStartReturnsValue)
{
    MockBoolean isReady(true); // won't be ready
    MockInteger value(42);
    MockTimerLambda timeout; // default timer expires immediately

    IntegerTimeout itimeout(value, isReady, timeout);

    auto returnedvalue = itimeout.GetInteger();
    ASSERT_EQ(returnedvalue, 42);
}

TEST(IntegerTimeout, IfReadyLaterBeforeTimeoutReturnsValue)
{
    int count = 0;
    MockBooleanLambda isReady([&count](){return count >= 10;}); // ready after 10 iterations
    MockInteger value(42);
    MockTimerLambda timeout([&count](){return (count++) >= 20;}); // times out after 20 iterations

    IntegerTimeout itimeout(value, isReady, timeout);

    auto returnedvalue = itimeout.GetInteger();
    ASSERT_EQ(returnedvalue, 42);
    ASSERT_EQ(count,10); // We returned the value after several iterations
}


TEST(IntegerTimeout, IfReadyAfterTimeoutReturnsERROR)
{
    int count = 0;
    MockBooleanLambda isReady([&count](){return count >= 20;}); // ready after 20 iterations
    MockInteger value(42);
    MockTimerLambda timeout([&count](){return (++count) >= 10;}); // times out after 10 iterations

    IntegerTimeout itimeout(value, isReady, timeout);

    auto returnedvalue = itimeout.GetInteger();
    ASSERT_EQ(returnedvalue, -2);
    ASSERT_EQ(count,10); // We returned the value after several iterations
}