#include <gtest/gtest.h>
#include "lib/NibblesToInteger.h"
#include "MockInteger.h"

// Demonstrate some basic assertions.
TEST(NibblessToInteger, InjectsToIntegerProviders)
{
    MockInteger lowbits(0);
    MockInteger highbits(0);

    NibblesToInteger ntoi(lowbits, highbits);
}

TEST(NibblesToInteger, IsAIntegerProvider)
{
    MockInteger lowbits(0);
    MockInteger highbits(0);

    NibblesToInteger ntoi(lowbits, highbits);

    // Make sure we can get a reference to the interface
    IIntegerProvider &intprovider = ntoi;

    auto value = intprovider.GetInteger();
    ASSERT_EQ(value, 0);
}

static void TestPattern(int16_t lowbits, int16_t highbits, int16_t expected)
{
    MockInteger low(lowbits);
    MockInteger high(highbits);

    NibblesToInteger ntoi(low, high);

    // Make sure we can get to it through the interface
    IIntegerProvider &intprovider = ntoi;
    auto value = intprovider.GetInteger();
    ASSERT_EQ(value, expected);

    value = NibblesToInteger::Convert(lowbits, highbits);
    ASSERT_EQ(value, expected);
}

TEST(NibblesToInteger, Zero)
{
    TestPattern(0, 0, 0);
}

TEST(NibblesToInteger, One)
{
    TestPattern(0x1, 0, 1);
}

TEST(NibblesToInteger, Sixteen)
{
    TestPattern(0, 0x1, 16);
}

TEST(NibblesToInteger, FullRange) {
    for(int16_t i=0;i<255;++i) {
        int16_t low = i & 0xF;
        int16_t high = (i >> 4) & 0xF;
        TestPattern(low, high, i);
    }
}