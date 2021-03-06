#ifndef C5B35687_247F_418A_966A_7B1BC46C1D03
#define C5B35687_247F_418A_966A_7B1BC46C1D03

#include "lib/stdint.h"

// Push consumer for an integer value
class IIntegerConsumer {
    public:
    typedef int16_t value_type;
    virtual void Consume(int16_t value) = 0;
};

#endif /* C5B35687_247F_418A_966A_7B1BC46C1D03 */
