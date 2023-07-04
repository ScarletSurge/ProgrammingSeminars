using System.Text;

namespace Practice.Domain;

public abstract class MihailGdeLaby:
    IEquatable<string>,
    IEquatable<int>,
    IEquatable<MihailGdeLaby>,
    IEquatable<object>
{
    
    // const, readonly
    // ref, out, in, params

    private const int IntValueDefault = 15;
    private const string StringValueDefault = "";
    private static readonly object SomeObject;

    static MihailGdeLaby()
    {
        // TODO: some logic for getting data to inject into SomeObject instance

        SomeObject = new object();
    }

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
        int @int = IntValueDefault,
        string @string = StringValueDefault)
    {
        IntValue = @int;
        StringValue = @string ?? throw new ArgumentNullException(nameof(@string));
        // SomeObject = new object();
    }

    public virtual string Foo()
    {
        return "Foo from base class";
    }

    public abstract void SomeMethod();
    
    // abstract virtual override

    public override string ToString()
    {
        // worst
        //return "[ StringValue: " + StringValue + ", IntValue: " + IntValue.ToString() + " ]";
        
        // avg
        //var builder = new StringBuilder("[ StringValue: ");
        //builder
        //    .Append(StringValue)
        //    .Append(", IntValue: ")
        //    .Append(IntValue)
        //    .Append(" ]");
        //return builder.ToString();
        
        //return new StringBuilder("[ StringValue: ")
        //    .Append(StringValue)
        //    .Append(", IntValue: ")
        //    .Append(IntValue)
        //    .Append(" ]")
        //    .ToString();

        return $"[ StringValue: {StringValue}, IntValue: {IntValue} ]";
    }

    public override int GetHashCode()
    {
        return StringValue.GetHashCode() * 23 + IntValue.GetHashCode();
    }

    public override bool Equals(
        object? obj)
    {
        Console.WriteLine("object.Equals called");
        
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
    
    // Explicit interface implementation

    bool IEquatable<object>.Equals(
        object? obj)
    {
        Console.WriteLine("IEquatable<object>.Equals called");
        
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
}

public sealed class MihailGdeKursach :
    MihailGdeLaby
{
    public MihailGdeKursach(
        string @string,
        int @int) : base(@int, @string)
    {
        
    }
    
    public override string Foo()
    {
        return "Foo from derived class";
    }

    public override void SomeMethod()
    {
        Console.WriteLine("Gde kursach");
    }
}

public sealed class MihailGdeDiplom :
    MihailGdeLaby
{
    public MihailGdeDiplom(
        string @string,
        int @int) : base(@int, @string)
    {
        
    }
    
    public override void SomeMethod()
    {
        Console.WriteLine("Gde diplom");
    }
}