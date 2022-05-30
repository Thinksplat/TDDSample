#include <gtest/gtest.h>
#include "lib-behaviour/BlinkBuilder.h"
#include "MockBooleanLambda.h"
#include <string>
#include <vector>

class NothingWork : public IWork {
public:
    virtual void Work() {}
};  

// Demonstrate some basic assertions.
TEST(BlinkBuilder, Fluent) {
    std::vector<std::string> record;
    MockBooleanLambdaConsumer on_off([&record](bool value) {
        record.push_back(value ? "on" : "off");
    });

    MockBooleanLambda until([]() { return true; });
    NothingWork wait;

    // Missing end value
    EXPECT_THROW(BlinkBuilder(on_off).Run(), std::runtime_error);
    EXPECT_THROW(BlinkBuilder(on_off).Until(until).Run(), std::runtime_error);
    EXPECT_THROW(BlinkBuilder(on_off).Until(until).OnWait(wait).Run(), std::runtime_error);
    // All complete
    EXPECT_NO_THROW(BlinkBuilder(on_off).Until(until).OnWait(wait).OffWait(wait).Run());
    // Also complete with a single wait
    EXPECT_NO_THROW(BlinkBuilder(on_off).Until(until).Wait(wait).Run());
}