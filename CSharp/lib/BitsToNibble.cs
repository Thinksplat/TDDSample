namespace lib;

public class BitsToNibble : IIntegerProvider
{
    readonly IBooleanProvider bit0;
    readonly IBooleanProvider bit1;
    readonly IBooleanProvider bit2;
    readonly IBooleanProvider bit3;
    
    public BitsToNibble(IBooleanProvider bit0, IBooleanProvider bit1, IBooleanProvider bit2, IBooleanProvider bit3)
    {
        this.bit0 = bit0;
        this.bit1 = bit1;
        this.bit2 = bit2;
        this.bit3 = bit3;
    }
    public int GetInteger()
    {
        return (bit0.GetBoolean() ? 1 : 0) + (bit1.GetBoolean() ? 2 : 0) + (bit2.GetBoolean() ? 4 : 0) + (bit3.GetBoolean() ? 8 : 0);
    }
}
