#ifndef F7711BC3_2A87_4660_8819_DE50ABE752CD
#define F7711BC3_2A87_4660_8819_DE50ABE752CD

#include "lib/ITimer.h"
#include <functional>

class MockTimerLambda : public ITimer {
    public:
    MockTimerLambda(std::function<bool()> lambda) : expired_lambda(lambda) {}
     bool HasExpired() override {
            return expired_lambda();
     }
     void Reset() override {

     }
    private:
    std::function<bool()> expired_lambda;
};


#endif /* F7711BC3_2A87_4660_8819_DE50ABE752CD */
