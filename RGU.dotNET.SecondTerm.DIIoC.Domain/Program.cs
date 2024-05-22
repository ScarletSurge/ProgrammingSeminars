// See https://aka.ms/new-console-template for more information
// Artifactory (JFrog, nuget.org)
// packet (Maven, Ruby Gem, NuGet)

// Autofac
// Castle.Windsor (по диагонали)
// Ninject (для истории)
// Unity (по диагонали)
// IServiceRegistrator

using DryIoc;

var b = new B();
// TODO: use b

var cntnr = new Container();
cntnr.RegisterMany<A>();
cntnr.Register<I1, D>();
cntnr.Register<B>(Reuse.Singleton);
//cntnr.RegisterInstance(b);
cntnr.Register<C>(Reuse.Transient);
//cntnr.RegisterMapping<ISomeInterface, C>();
cntnr.RegisterMapping<ISomeInterface, B>();

var resolved = cntnr.Resolve<ISomeInterface>();
Console.WriteLine(ReferenceEquals(resolved, cntnr.Resolve<B>()));
Console.WriteLine(ReferenceEquals(resolved, b));

// Register
// RegisterMany
// RegisterInstance
// RegisterMapping
// RegisterDelegate
// Resolve
// ResolveMany

//Console.WriteLine("Hello, World!");
//Console.WriteLine(ReferenceEquals(cntnr.Resolve<ISomeInterface>(), cntnr.Resolve<ISomeInterface>()));

public interface I1
{
    void Foo();
}

public interface I2
{
    void Foo();
}

public sealed class D:
    I1
{
    public void Foo()
    {
        
    }
}

public sealed class A:
    I1,
    I2
{
    private B _obj;

    public A(
        B? obj)
    {
        _obj = obj ?? throw new ArgumentNullException(nameof(obj));
    }

    void I1.Foo()
    {
        
    }

    void I2.Foo()
    {
        
    }
    
    public override string ToString()
    {
        return "A instance";
    }
}

interface ISomeInterface
{
    void Foo();
}

public sealed class B:
    ISomeInterface
{
    public override string ToString()
    {
        return "B instance";
    }

    public void Foo()
    {
        Console.WriteLine("Foo from B");
    }
}

public sealed class C:
    ISomeInterface
{
    public override string ToString()
    {
        return "B instance";
    }

    public void Foo()
    {
        Console.WriteLine("Foo from C");
    }
}