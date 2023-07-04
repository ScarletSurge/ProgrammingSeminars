namespace Practice.Domain;

public class MihailGdeLaby:
    IEquatable<string>,
    IEquatable<int>,
    IEquatable<MihailGdeLaby>
{

    public int IntValue
    {
        get;

        // init;
    }

    public string StringValue
    {
        get;
    }

    public MihailGdeLaby(
        int @int = 0,
        string @string = "")
    {
        IntValue = @int;
        StringValue = @string ?? throw new ArgumentNullException(nameof(@string));
    }

    public void Foo()
    {
        
    }
    
    // abstract virtual override

    public override bool Equals(
        object? obj)
    {
        if (obj == null)
        {
            return false;
        }

        if (obj is MihailGdeLaby mgl)
        {
            return Equals(mgl);
        }
        if (obj is string @string)
        {
            return Equals(@string);
        }

        if (obj is int @int)
        {
            return Equals(@int);
        }

        return false;
    }
    
    public bool Equals(
        string @string)
    {
        return StringValue.Equals(@string);
    }

    public bool Equals(
        int @int)
    {
        return IntValue.Equals(@int);
    }

    public bool Equals(
        MihailGdeLaby mgl)
    {
        if (mgl == null)
        {
            return false;
        }
        
        return IntValue == mgl.IntValue
               && StringValue.Equals(mgl.StringValue);
    }
    
}

public class MihailGdeKursach :
    MihailGdeLaby
{
    
}