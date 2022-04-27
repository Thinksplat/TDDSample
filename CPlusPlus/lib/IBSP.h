#ifndef A5610071_B08E_49B8_B5AA_4C232DA48081
#define A5610071_B08E_49B8_B5AA_4C232DA48081

class ITimeProvider;
class IBooleanProvider;
class IIntegerConsumer;

class IBSP
{
    ITimeProvider &Time();
    IIntegerConsumer &LED();
    IBooleanProvider &Pin0();
};

#endif /* A5610071_B08E_49B8_B5AA_4C232DA48081 */
