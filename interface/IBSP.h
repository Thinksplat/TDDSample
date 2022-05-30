#ifndef A5610071_B08E_49B8_B5AA_4C232DA48081
#define A5610071_B08E_49B8_B5AA_4C232DA48081

#include "lib-behaviour/BitsToNibbleFunction.h"
#include "interface/IBooleanProvider.h"

class ITimeProvider;
class IBooleanConsumer;
class IIntegerConsumer;
class ITimer;

class IBSP
{
public:
    virtual ITimeProvider &Time() = 0;

    // A timer that expires when we should stop running
    virtual ITimer &RunningTimer() = 0;

    // LED for visible status if
    virtual IBooleanConsumer &LED() = 0;

    // Where the data is sent to
    virtual IIntegerConsumer &Consumer() = 0;

    // The 5 data buss pins
    virtual IBooleanProvider &Transmit() = 0;
    virtual IBooleanProvider &Pin0() = 0;
    virtual IBooleanProvider &Pin1() = 0;
    virtual IBooleanProvider &Pin2() = 0;
    virtual IBooleanProvider &Pin3() = 0;
    std::function<int16_t()> Nibble() {
        return BitsToNibbleFunction::Create(Pin0(), Pin1(), Pin2(), Pin3());
    }
};

#endif /* A5610071_B08E_49B8_B5AA_4C232DA48081 */
