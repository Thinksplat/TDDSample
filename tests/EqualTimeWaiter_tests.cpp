#include <gtest/gtest.h>
#include "lib/EqualTimeWaiter.h"
#include "WalkingTime.h"

// Demonstrate some basic assertions.
TEST(EqualTimeWaiter, Instantiation)
{
    WalkingTime time;
    EqualTimeWaiter waiter(time, 100);
}

TEST(EqualTimeWaiter, Wait)
{
    WalkingTime time;
    EqualTimeWaiter waiter(time, 100);
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 100);
    ASSERT_LE(time.GetTime(), 103);

    waiter.Wait();
    ASSERT_GE(time.GetTime(), 200);
    ASSERT_LE(time.GetTime(), 203);

     waiter.Wait();
    ASSERT_GE(time.GetTime(), 300);
    ASSERT_LE(time.GetTime(), 303);

     waiter.Wait();
    ASSERT_GE(time.GetTime(), 400);
    ASSERT_LE(time.GetTime(), 403);
}

TEST(EqualTimeWaiter, WorksWithTimePassingInbetween)
{
    WalkingTime time;

    EqualTimeWaiter waiter(time, 100);
    time.SetTime(50);
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 100);
    ASSERT_LE(time.GetTime(), 103);
}

TEST(EqualTimeWaiter, OverflowReturnsRightAwayToCatchUp)
{
    WalkingTime time;

    EqualTimeWaiter waiter(time, 100);
    // We pass the first one
    time.SetTime(150);
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 150);
    ASSERT_LE(time.GetTime(), 153);
    
    // Wait again and it should have caught up.
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 200);
    ASSERT_LE(time.GetTime(), 203);
}