namespace lib;

public class BitsToNibble2 : IIntegerProvider
{
    readonly IBooleanProvider bit0;
    readonly IBooleanProvider bit1;
    readonly IBooleanProvider bit2;
    readonly IBooleanProvider bit3;
    
    public BitsToNibble2(IBooleanProvider bit0, IBooleanProvider bit1, IBooleanProvider bit2, IBooleanProvider bit3)
    {
        this.bit0 = bit0;
        this.bit1 = bit1;
        this.bit2 = bit2;
        this.bit3 = bit3;
    }
    public int GetInteger()
    {
        return Convert(bit0.GetBoolean(), bit1.GetBoolean(), bit2.GetBoolean(), bit3.GetBoolean());
    }

    static int Convert(bool bit0, bool bit1, bool bit2, bool bit3)
    {
        return (bit0 ? 1 : 0) + (bit1 ? 2 : 0) + (bit2 ? 4 : 0) + (bit3 ? 8 : 0);
    }


}
