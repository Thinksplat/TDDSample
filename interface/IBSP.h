#ifndef A5610071_B08E_49B8_B5AA_4C232DA48081
#define A5610071_B08E_49B8_B5AA_4C232DA48081

class ITimeProvider;
class IBooleanProvider;
class IIntegerConsumer;

class IBSP
{
    ITimeProvider &Time();
    // A provider to tell the program to keep running or stop.
    IBooleanProvider &KeepRunning();

    // LED for visible status if
    IIntegerConsumer &LED();

    // The 5 data buss pins
    IBooleanProvider &Enable();
    IBooleanProvider &Pin0();
    IBooleanProvider &Pin1();
    IBooleanProvider &Pin2();
    IBooleanProvider &Pin3();
};

#endif /* A5610071_B08E_49B8_B5AA_4C232DA48081 */
