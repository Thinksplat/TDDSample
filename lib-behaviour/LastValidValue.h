#ifndef FFE976F7_54E2_4A83_AF64_5E42C6DEE97D
#define FFE976F7_54E2_4A83_AF64_5E42C6DEE97D

#include "interface/IIntegerProvider.h"
#include "interface/IBooleanProvider.h"

namespace Behaviour {
    // Returns the last valid value of the provider 
    /// @param isValid Keep reading while isValid continues to provide true
    /// @param value The value we are monitoring
    /// @return The last valid value of the provider

    template <typename T>
    static T LastValidValue(const std::function<bool()> &isValid, const std::function<T()> &value) {
        // Start out invalid in the case we immediately drop out of the while loop
        T last_valid = -1;

        while (isValid()) {
            T this_value = value();
            // "by definition", a valid value is greater than 0
            if (this_value >= 0) {
                last_valid = this_value;
            }
        }
        
        return last_valid;
    }
}

#endif /* FFE976F7_54E2_4A83_AF64_5E42C6DEE97D */
