namespace shared;
public class BitConversions
{
    public static int BitsToNibble(bool bit0, bool bit1, bool bit2, bool bit3)
    {
        return (bit0 ? 1 : 0) + (bit1 ? 2 : 0) + (bit2 ? 4 : 0) + (bit3 ? 8 : 0);
    }
}
