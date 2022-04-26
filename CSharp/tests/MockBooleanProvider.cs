using lib;

namespace tests;

class MockBooleanProvider : IBooleanProvider
{
    private bool Value;

    public MockBooleanProvider(bool value)
    {
        Value = value;
    }
    void SetValue(bool value) => Value = value;
    public bool GetBoolean() => Value;
}
