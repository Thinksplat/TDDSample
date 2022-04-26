using FluentAssertions;
using Xunit;

namespace tests;

public class UnitTest1
{
    [Fact]
    public void Test1()
    {
        1.Should().Be(1);
    }
}