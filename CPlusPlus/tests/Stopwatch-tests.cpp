#include <gtest/gtest.h>
#include "MockTimeProvider.h"
#include "lib/Stopwatch.h"

// Demonstrate some basic assertions.
TEST(Stopwatch, BasicInstantiation) {
    MockTimeProvider time(0);
    Stopwatch stopwatch(time);
}

TEST(Stopwatch, DeltaTimeWorks) {
    MockTimeProvider time(0);
    Stopwatch stopwatch(time);
    time.SetValue(100);
    ASSERT_EQ(stopwatch.ElapsedMicroseconds(), 100);
}

TEST(Stopwatch, MaxRange) {
    MockTimeProvider time(0);
    Stopwatch stopwatch(time);
    time.SetValue(0xFFFFFFFF);
    ASSERT_EQ(stopwatch.ElapsedMicroseconds(), 0xFFFFFFFF);
}

TEST(Stopwatch, Overflow) {
    // start near the end of time
    MockTimeProvider time(0xfffffff0);
    Stopwatch stopwatch(time);

    // stopwatch starts at 0
    ASSERT_EQ(stopwatch.ElapsedMicroseconds(), 0);

    // increment past 32bits
    time.SetValue(time.GetMicroseconds() + 0xffff);
    // We're less than we started and greater than 0
    ASSERT_LT(time.GetMicroseconds(), 0xfffffff0);
    ASSERT_GT(time.GetMicroseconds(), 0);

    // Diff works past overflow
    ASSERT_EQ(stopwatch.ElapsedMicroseconds(), 0xffff);
}