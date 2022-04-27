#include <gtest/gtest.h>
#include "lib/EqualTimeIntervalSkipRecover.h"
#include "WalkingTime.h"

// Demonstrate some basic assertions.
TEST(EqualTimeIntervalSkipRecover, Instantiation)
{
    WalkingTime time;
    EqualTimeIntervalSkipRecover etw(time);
}

TEST(EqualTimeIntervalSkipRecover, Wait)
{
    WalkingTime time;
    EqualTimeIntervalSkipRecover etw(time);
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

TEST(EqualTimeIntervalSkipRecover, WorksWithTimePassingInbetween)
{
    WalkingTime time;

    EqualTimeIntervalSkipRecover etw(time);
    auto waiter = etw.CreateWaiter(100);
    time.SetTime(50);
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 100);
    ASSERT_LE(time.GetTime(), 103);
}

TEST(EqualTimeIntervalSkipRecover, OverframeWillSkipToCatchUp)
{
    WalkingTime time;

    EqualTimeIntervalSkipRecover etw(time);
    auto waiter = etw.CreateWaiter(100);

    // Hit the first one
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 100);
    ASSERT_LE(time.GetTime(), 103);

    // We pass the second one
    time.SetTime(250);
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 300);
    ASSERT_LE(time.GetTime(), 303);

    // Hit the fourth one
    waiter.Wait();
    ASSERT_GE(time.GetTime(), 400);
    ASSERT_LE(time.GetTime(), 403);
}