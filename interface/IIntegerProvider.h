#ifndef FCB38476_20D6_4FB4_A0E4_8803A2E087A4
#define FCB38476_20D6_4FB4_A0E4_8803A2E087A4

#include <functional>
#include "lib/stdint.h"

// Pull provider for an integer value
class IIntegerProvider
{
public:
    typedef int16_t value_type;
    virtual value_type GetInteger() = 0;
    // conversion to std::function<value_type()>
    operator std::function<value_type()>()
    {
        return GetFunction();
    }
    std::function<value_type()> GetFunction()
    {
        return std::function<value_type()>(std::bind(&IIntegerProvider::GetInteger, this));
    }
};

#endif /* FCB38476_20D6_4FB4_A0E4_8803A2E087A4 */
