namespace RGU.dotNET.SecondTerm.ICloneableDemo;

public class CloneableDemo:
    IEquatable<CloneableDemo>,
    ICloneable
{

    private enum SomeType
    {
        Value1,
        Value2
    }
    
    private readonly int _value;
    private readonly SomeType _someTypeValue;

    public CloneableDemo()
    {
        _value = new Random().Next(1, 100);
        _someTypeValue = SomeType.Value1;
    }
    
    private CloneableDemo(
        int value,
        SomeType someTypeValue)
    {
        _value = value;
        _someTypeValue = someTypeValue;
    }
    
    #region System.Object overrides

    public override int GetHashCode()
    {
        return HashCode.Combine(_value, _someTypeValue);
    }

    public override bool Equals(
        object? obj)
    {
        if (obj is null)
        {
            return false;
        }

        if (obj is CloneableDemo ruslan)
        {
            return Equals(ruslan);
        }

        return false;
    }
    
    #endregion
    
    #region System.IEquatable<out CloneableDemo> implementation

    public bool Equals(
        CloneableDemo? obj)
    {
        if (obj is null)
        {
            return false;
        }

        return _value.Equals(obj._value)
               && _someTypeValue.Equals(obj._someTypeValue);
    }
    
    #endregion
    
    #region System.ICloneable implementation
    
    // public object Clone()
    object ICloneable.Clone()
    {
        return (new CloneableDemo(_value, _someTypeValue) as object);
    }
    
    #endregion

}