#include <gtest/gtest.h>
#include "MockIntegerLambda.h"
#include "MockBooleanLambda.h"
#include "MockBoolean.h"
#include "MockTimerLambda.h"
#include "tests/WalkingTime.h"
#include "lib/Pinball.h"
#include "lib/TimeTimer.h"
#include "tests/Sim.h"
#include "tests/PinballProfile.h"

static const int stable_time = 200;

TEST(Pinball, Instantiation)
{
    MockBoolean pin0, pin1, pin2, pin3;
    MockBoolean enable;
    MockTimerLambda timer([]()
                          { return true; });

    Pinball pinball(enable, pin0, pin1, pin2, pin3, timer);
}

TEST(Pinball, DoesThisThingWork)
{
    WalkingTime time;
    Sim sim(time);

    TimeTimer timer(time, stable_time);

    Pinball pinball(sim.Lines().Transmit(),
                    sim.Lines().Data0(),
                    sim.Lines().Data1(),
                    sim.Lines().Data2(),
                    sim.Lines().Data3(),
                    timer);

    // Setup a profile with an enable line that holds true for at least twice the stable time,
    // should give 0 as a value
    const int little_bit = 15;
    sim.Accumulate(Sim::PINS::TRANSMIT)
        .Next(false, 10)
        .Next(true, stable_time + little_bit) // low bit
        .Next(true, stable_time + little_bit) // high bit
        .Next(false, 10);                     // end transmit

    // See if pinball gives us 0
    auto value = pinball.GetInteger();
    EXPECT_EQ(0, value);
}

static void GenericTest(std::function<void(Pinball &, Sim &sim)> test_function)
{
    WalkingTime time;
    Sim sim(time);

    TimeTimer timer(time, stable_time);

    Pinball pinball(sim.Lines().Transmit(),
                    sim.Lines().Data0(),
                    sim.Lines().Data1(),
                    sim.Lines().Data2(),
                    sim.Lines().Data3(),
                    timer);

    test_function(pinball, sim);
}

TEST(Pinball, ShortTransmit)
{
    GenericTest([](Pinball &pinball, Sim &sim)
                {
                    // Setup a profile with an enable line that holds true for at least twice the stable time,
                    // should give 0 as a value
                    const int little_bit = 15;
                    sim.Accumulate(Sim::PINS::TRANSMIT)
                        .Next(false, 10)
                        .Next(true, stable_time + little_bit) // low bit
                        //.Next(true, stable_time + little_bit) // high bit
                        .Next(false, 10); // end transmit

                    // See if pinball gives us 0
                    auto value = pinball.GetInteger();
                    EXPECT_EQ(-1, value);
                    // The low value is valid
                    EXPECT_EQ(0, pinball.LastLowNibble());
                    // The high value should be invalid becase we ended early
                    EXPECT_EQ(-1, pinball.LastHighNibble()); });
}

TEST(Pinball, GoodProfile)
{
    GenericTest([](Pinball &pinball, Sim &sim)
                {
                    const int noise_time = 10;
                    const int little_bit = 30;
                    PinballProfile::GenPinball(sim,
                    10,
                    stable_time+little_bit,
                    stable_time+little_bit,
                    noise_time,0xd,0xe);

                    auto value = pinball.GetInteger();
                    EXPECT_EQ(0xed, value); });
}

TEST(Pinball, ShortFirst)
{
    GenericTest([](Pinball &pinball, Sim &sim)
                {
                    const int noise_time = 10;
                    const int little_bit = 30;
                    PinballProfile::GenPinball(sim,
                                               10,
                                               stable_time / 2 + little_bit,
                                               stable_time + little_bit,
                                               noise_time, 0xd, 0xe);

                    auto value = pinball.GetInteger();
                    EXPECT_EQ(-1, value);
                    // the low value is missed, but the high value will show as the low value
                    EXPECT_EQ(0xe, pinball.LastLowNibble());
                    EXPECT_EQ(-1, pinball.LastHighNibble());
                });
}

TEST(Pinball, ShortSecond)
{
    GenericTest([](Pinball &pinball, Sim &sim)
                {
                    const int noise_time = 10;
                    const int little_bit = 30;
                    PinballProfile::GenPinball(sim,
                                               10,
                                               stable_time + little_bit,
                                               stable_time/2 + little_bit,
                                               noise_time, 0xd, 0xe);

                    auto value = pinball.GetInteger();
                    EXPECT_EQ(-1, value);
                    // the low value is missed, but the high value will show as the low value
                    EXPECT_EQ(0xd, pinball.LastLowNibble());
                    EXPECT_EQ(-1, pinball.LastHighNibble());
                });
}

TEST(Pinball, AnotherValue)
{
    GenericTest([](Pinball &pinball, Sim &sim)
                {
                    const int noise_time = 10;
                    const int little_bit = 30;
                    PinballProfile::GenPinball(sim,
                                               10,
                                               stable_time + little_bit,
                                               stable_time + little_bit,
                                               noise_time, 0xa, 0xb);

                    auto value = pinball.GetInteger();
                    EXPECT_EQ(0xba, value);
                    // the low value is missed, but the high value will show as the low value
                    EXPECT_EQ(0xa, pinball.LastLowNibble());
                    EXPECT_EQ(0xb, pinball.LastHighNibble());
                });
}