#ifndef BEEF5770_1869_43C3_80A6_2E0FABBD9EAF
#define BEEF5770_1869_43C3_80A6_2E0FABBD9EAF

#include "IIntegerProvider.h"
#include "IIntegerConsumer.h"

class App {
    public:
    App(IIntegerProvider &provider, IIntegerConsumer &consumer) : provider(provider), consumer(consumer) {}
    protected:
    IIntegerProvider &provider;
    IIntegerConsumer &consumer;
}

#endif /* BEEF5770_1869_43C3_80A6_2E0FABBD9EAF */
