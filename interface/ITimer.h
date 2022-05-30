#ifndef DA6A6755_21A6_4743_8988_1F46A84425CA
#define DA6A6755_21A6_4743_8988_1F46A84425CA

#include "interface/IWork.h"

class ITimer : public IWork
{
public:
    void Wait()
    {
        Work();
    }
    void Work() override
    {
        while (!HasExpired())
        {
            // Do nothing
        }
    }
    virtual bool HasExpired() = 0;
    virtual void Reset() = 0;
};

#endif /* DA6A6755_21A6_4743_8988_1F46A84425CA */
