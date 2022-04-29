#ifndef FCB38476_20D6_4FB4_A0E4_8803A2E087A4
#define FCB38476_20D6_4FB4_A0E4_8803A2E087A4

#include "lib/stdint.h"

class IIntegerProvider {
public:
    typedef int16_t value_type;
    virtual value_type GetInteger() = 0;
};

#endif /* FCB38476_20D6_4FB4_A0E4_8803A2E087A4 */
