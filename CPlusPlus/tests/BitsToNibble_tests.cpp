#include <gtest/gtest.h>
#include "MockBoolean.h"
#include "lib/BitsToNibble.h"

static void TestPattern(bool bit0, bool bit1, bool bit2, bool bit3, int16_t expected)
{
    // Testing using the IIntegerProvider interface
    MockBoolean mockBit0(bit0);
    MockBoolean mockBit1(bit1);
    MockBoolean mockBit2(bit2);
    MockBoolean mockBit3(bit3);
    BitsToNibble nibbleToInteger(mockBit0, mockBit1, mockBit2, mockBit3);

    // Make sure we can get to it through the interface
    IIntegerProvider &intprovider = nibbleToInteger;
    auto value = intprovider.GetInteger();
    ASSERT_EQ(value, expected);

    // Test the pure static function too.
    value = BitsToNibble::Convert(bit0,bit1,bit2,bit3);
    ASSERT_EQ(value, expected);
}

// Demonstrate some basic assertions.
TEST(BitsToNibble, Instantiation)
{
    MockBoolean bit0(false);
    MockBoolean bit1(false);
    MockBoolean bit2(false);
    MockBoolean bit3(false);

    BitsToNibble ntoi(bit0, bit1, bit2, bit3);
}

TEST(BitsToNibble, Zero)
{
    TestPattern(false, false, false, false, 0);
}

TEST(BitsToNibble, One)
{
    TestPattern(true, false, false, false, 1);
}

TEST(BitsToNibble, AllPatterns)
{
    TestPattern(false, false, false, false, 0);
    TestPattern(true, false, false, false, 1);
    TestPattern(false, true, false, false, 2);
    TestPattern(true, true, false, false, 3);
    TestPattern(false, false, true, false, 4);
    TestPattern(true, false, true, false, 5);
    TestPattern(false, true, true, false, 6);
    TestPattern(true, true, true, false, 7);
    TestPattern(false, false, false, true, 8);
    TestPattern(true, false, false, true, 9);
    TestPattern(false, true, false, true, 10);
    TestPattern(true, true, false, true, 11);
    TestPattern(false, false, true, true, 12);
    TestPattern(true, false, true, true, 13);
    TestPattern(false, true, true, true, 14);
    TestPattern(true, true, true, true, 15);
}