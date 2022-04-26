namespace lib;

public class BitsToNibble4 : IIntegerProvider
{
    readonly IBooleanProvider bit0;
    readonly IBooleanProvider bit1;
    readonly IBooleanProvider bit2;
    readonly IBooleanProvider bit3;
    
    public BitsToNibble4(IBooleanProvider bit0, IBooleanProvider bit1, IBooleanProvider bit2, IBooleanProvider bit3)
    {
        this.bit0 = bit0;
        this.bit1 = bit1;
        this.bit2 = bit2;
        this.bit3 = bit3;
    }
    public int GetInteger()
    {
        return shared.BitConversions.BitsToNibble(bit0.GetBoolean(), bit1.GetBoolean(), bit2.GetBoolean(), bit3.GetBoolean());
    }
}
