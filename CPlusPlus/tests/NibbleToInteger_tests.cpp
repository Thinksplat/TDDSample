#include <gtest/gtest.h>
#include "MockBoolean.h"
#include "lib/NibbleToInteger.h"

// Demonstrate some basic assertions.
TEST(NibbleToInteger, Instantiation) {
    MockBoolean bit0(false);
    MockBoolean bit1(false);
    MockBoolean bit2(false);
    MockBoolean bit3(false);
    
    NibbleToInteger ntoi(bit0, bit1, bit2, bit3);
}