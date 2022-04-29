#ifndef CDEF15BB_47C5_4333_B5B5_C93189284355
#define CDEF15BB_47C5_4333_B5B5_C93189284355

#include "interface/IWaiter.h"
#include "interface/IBooleanProvider.h"

class BoolTrueWaiter : IWaiter
{
public:
    BoolTrueWaiter(IBooleanProvider &provider) : provider(provider) {}
    virtual void Wait()
    {
        while (provider.GetBool() == false)
        {
            // spin
        }
    }

private:
    IBooleanProvider &provider;
};

#endif /* CDEF15BB_47C5_4333_B5B5_C93189284355 */
