#ifndef BEEF5770_1869_43C3_80A6_2E0FABBD9EAF
#define BEEF5770_1869_43C3_80A6_2E0FABBD9EAF

#include "interface/IIntegerProvider.h"
#include "interface/IIntegerConsumer.h"
#include "interface/ITimer.h"

class App {
    public:
    App(IIntegerProvider &provider, IIntegerConsumer &consumer, ITimer &run_timer) : provider(provider), consumer(consumer), run_timer(run_timer) {}
    void Run() {
        while(!run_timer.HasExpired()) {
            consumer.Consume(provider.GetInteger());
        }
    }
    protected:
    IIntegerProvider &provider;
    IIntegerConsumer &consumer;
    ITimer &run_timer;
};

#endif /* BEEF5770_1869_43C3_80A6_2E0FABBD9EAF */
