#include <gtest/gtest.h>
#include "lib/EqualTimeInterval.h"
#include "WalkingTime.h"

// Demonstrate some basic assertions.
TEST(EqualTimeInterval, Instantiation)
{
    WalkingTime time;
    EqualTimeInterval etw(time);
}

TEST(EqualTimeInterval, Wait)
{
    WalkingTime time;
    EqualTimeInterval etw(time);
    auto waiter = etw.CreateWaiter(100);
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

TEST(EqualTimeInterval, WorksWithTimePassingInbetween)
{
    WalkingTime time;

    EqualTimeInterval etw(time);
    auto waiter = etw.CreateWaiter(100);
    time.SetTime(50);
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 100);
    ASSERT_LE(time.GetTime(), 103);
}

TEST(EqualTimeInterval, OverflowReturnsRightAwayToCatchUp)
{
    WalkingTime time;

    EqualTimeInterval etw(time);
    auto waiter = etw.CreateWaiter(100);

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