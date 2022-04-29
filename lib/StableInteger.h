#ifndef FD4C823B_A69B_45D7_8FFF_6663B514E768
#define FD4C823B_A69B_45D7_8FFF_6663B514E768

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"
#include "interface/ITimer.h"
#include "lib-behaviour/Stable.h"

class StableInteger : public IIntegerProvider
{
public:
    StableInteger(IIntegerProvider &provider, IBooleanProvider &isValid, ITimer &timer) 
        : provider(provider), isValid(isValid), timer(timer)
    {
    }
    int16_t GetInteger()
    {
       return Behaviour::Stable(provider, isValid, timer);
    }

private:
    IIntegerProvider &provider;
    IBooleanProvider &isValid;
    ITimer &timer;
};

#endif /* FD4C823B_A69B_45D7_8FFF_6663B514E768 */
