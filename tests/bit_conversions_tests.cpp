#include <gtest/gtest.h>
#include "shared/bit_conversions.h"

// Demonstrate some basic assertions.
TEST(BitConversions, BitsToNibble) {
    auto value = BitConversions::BitsToInteger(true, true, true, true);
    ASSERT_EQ(value, 15);

    value = BitConversions::BitsToInteger(true, true, false, true);
    ASSERT_EQ(value, 11);
}

TEST(BitConversions, NibblesToInteger) {
    auto value = BitConversions::NibblesToWord(0, 0);
    ASSERT_EQ(value, 0);

    value = BitConversions::NibblesToWord(1, 1);
    ASSERT_EQ(value, 0x11);

    value = BitConversions::NibblesToWord(0, 1);
    ASSERT_EQ(value, 0x10);
}