#ifndef EAB9DD45_001E_4BD3_B906_C91E1E43CB61
#define EAB9DD45_001E_4BD3_B906_C91E1E43CB61

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "interface/ITimer.h"

class IntegerTimeout : public IIntegerProvider {
    public:
    IntegerTimeout(IIntegerProvider &value, IBooleanProvider &isReady, ITimer &timeout) : value(value), isReady(isReady), timeout(timeout) {}
    IIntegerProvider::value_type GetInteger() override {
        // Start with a clean timer
        timeout.Reset();

        while(notReady()) {
            if(timeout.HasExpired()) {
                return -2;
            }
        }
        return value.GetInteger();
    }
    private:
    inline bool notReady() {
        return isReady.GetBool() == false;
    }

    IIntegerProvider &value;
    IBooleanProvider &isReady;
    ITimer &timeout;
};

#endif /* EAB9DD45_001E_4BD3_B906_C91E1E43CB61 */
