#ifndef FFE976F7_54E2_4A83_AF64_5E42C6DEE97D
#define FFE976F7_54E2_4A83_AF64_5E42C6DEE97D

#include "lib/IIntegerProvider.h"
#include "lib/IBooleanProvider.h"

namespace Behaviour {
    // Returns the last valid value of the provider while isValid was true
    static IIntegerProvider::value_type LastValidValue(IBooleanProvider &isValid, IIntegerProvider &provider) {
        auto last_valid = -1;
        while (isValid.GetBool()) {
            auto this_value = provider.GetInteger();
            // "by definition", a valid value is greater than 0
            if (this_value >= 0) {
                last_valid = this_value;
            }
        }
        return last_valid;
    }
}

#endif /* FFE976F7_54E2_4A83_AF64_5E42C6DEE97D */
