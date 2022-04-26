using FluentAssertions;
using lib;
using Xunit;

namespace tests;

public class BitsToNibbleTests
{
    [Fact]
    public void Instantiation()
    {
        MockBooleanProvider bit0 = new MockBooleanProvider(false);
        MockBooleanProvider bit1 = new MockBooleanProvider(false);
        MockBooleanProvider bit2 = new MockBooleanProvider(false);
        MockBooleanProvider bit3 = new MockBooleanProvider(false);
        BitsToNibble bton = new(bit0, bit1, bit2, bit3);
    }

     [Fact]
    public void Instantiation2()
    {
        MockBooleanProvider bit0 = new MockBooleanProvider(false);
        MockBooleanProvider bit1 = new MockBooleanProvider(false);
        MockBooleanProvider bit2 = new MockBooleanProvider(false);
        MockBooleanProvider bit3 = new MockBooleanProvider(false);
        BitsToNibble2 bton = new(bit0, bit1, bit2, bit3);
        bton.GetInteger().Should().Be(0);
    }

    static void TestPattern(bool bit0, bool bit1, bool bit2, bool bit3, int expected)
    {
        MockBooleanProvider b0 = new MockBooleanProvider(bit0);
        MockBooleanProvider b1 = new MockBooleanProvider(bit1);
        MockBooleanProvider b2 = new MockBooleanProvider(bit2);
        MockBooleanProvider b3 = new MockBooleanProvider(bit3);
        BitsToNibble bton = new(b0, b1, b2, b3);
        bton.GetInteger().Should().Be(expected);
    }

    [Fact]
    public void Zero()
    {
        TestPattern(false, false, false, false, 0);
    }

    [Fact]
    public void One()
    {
        TestPattern(true, false, false, false, 1);
    }

    [Fact]
    public void Two()
    {
        TestPattern(false, true, false, false, 2);
    }

}