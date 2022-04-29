#ifndef A5610071_B08E_49B8_B5AA_4C232DA48081
#define A5610071_B08E_49B8_B5AA_4C232DA48081

class ITimeProvider;
class IBooleanProvider;
class IIntegerConsumer;
class ITimer;

class IBSP
{
public:
    virtual ITimeProvider &Time() = 0;

    // A timer that expires when we should stop running
    virtual ITimer &RunningTimer() = 0;

    // LED for visible status if
    virtual IIntegerConsumer &LED() = 0;

    // Where the data is sent to
    virtual IIntegerConsumer &Consumer() = 0;

    // The 5 data buss pins
    virtual IBooleanProvider &Enable() = 0;
    virtual IBooleanProvider &Pin0() = 0;
    virtual IBooleanProvider &Pin1() = 0;
    virtual IBooleanProvider &Pin2() = 0;
    virtual IBooleanProvider &Pin3() = 0;
};

#endif /* A5610071_B08E_49B8_B5AA_4C232DA48081 */
