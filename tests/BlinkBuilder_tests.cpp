#include <gtest/gtest.h>
#include "lib-behaviour/BlinkBuilder.h"
#include "MockBooleanLambda.h"

// Demonstrate some basic assertions.
TEST(BlinkBuilder, Fluent) {
    MockBooleanLambdaConsumer on_off;

    BlinkBuilder builder(on_off);
}