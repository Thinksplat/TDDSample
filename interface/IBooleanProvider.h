#ifndef DD3762F1_47EC_412F_A437_72747731A949
#define DD3762F1_47EC_412F_A437_72747731A949

#include <functional>

// Pull Provider for a boolean value
class IBooleanProvider
{
    public:
    virtual ~IBooleanProvider(){}
    virtual bool GetBool() = 0;
    // conversion to std::function<bool()>
    operator std::function<bool()>() {
        return GetFunction();
    }
    std::function<bool()> GetFunction() {
        return std::function<bool()>(std::bind(&IBooleanProvider::GetBool, this));
    }
};

#endif /* DD3762F1_47EC_412F_A437_72747731A949 */
