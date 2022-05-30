#ifndef DEACFCB3_F9EA_4C00_B325_CE616E6BC45F
#define DEACFCB3_F9EA_4C00_B325_CE616E6BC45F

#include <functional>

// Interface to generically Wait for something to happen
class IWork
{
public:
    void Wait()
    {
        Work();
    }
    void Run() {
        Work();
    }
    virtual void Work() = 0;
    // conversion to std::functional<void()>
    operator std::function<void()>() {
        return std::function<void()>(std::bind(&IWork::Work, this));
    }
};

#endif /* DEACFCB3_F9EA_4C00_B325_CE616E6BC45F */
