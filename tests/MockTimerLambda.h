#ifndef F7711BC3_2A87_4660_8819_DE50ABE752CD
#define F7711BC3_2A87_4660_8819_DE50ABE752CD

#include "interface/ITimer.h"
#include <functional>

class MockTimerLambda : public ITimer {
    public:
    MockTimerLambda(std::function<bool()> lambda, std::function<void()> reset = [](){}) : expired_lambda(lambda), reset(reset) {}
     bool HasExpired() override {
            return expired_lambda();
     }
     void Reset() override {
         reset();
     }

    private:
    std::function<bool()> expired_lambda;
    std::function<void()> reset;
};


#endif /* F7711BC3_2A87_4660_8819_DE50ABE752CD */
