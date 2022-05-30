#ifndef CDEF15BB_47C5_4333_B5B5_C93189284355
#define CDEF15BB_47C5_4333_B5B5_C93189284355

#include "interface/IWork.h"
#include "interface/IBooleanProvider.h"

class WorkUntilTrue : IWork
{
public:
    WorkUntilTrue(IBooleanProvider &provider) : provider(provider) {}
    virtual void Work()
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
