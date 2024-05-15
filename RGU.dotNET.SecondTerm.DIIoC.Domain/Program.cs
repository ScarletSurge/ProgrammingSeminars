// See https://aka.ms/new-console-template for more information
// Artifactory (JFrog, nuget.org)
// packet (Maven, Ruby Gem, NuGet)

// Autofac
// Castle.Windsor (по диагонали)
// Ninject (для истории)
// Unity (по диагонали)
// IServiceRegistrator

using DryIoc;

var cntnr = new Container();
cntnr.Register<A>();
cntnr.Register<C>();
cntnr.RegisterMapping<ISomeInterface, C>();

// Register
// RegisterMany
// RegisterInstance
// RegisterMapping
// RegisterDelegate
// Resolve
// ResolveMany

Console.WriteLine("Hello, World!");
Console.WriteLine(ReferenceEquals(cntnr.Resolve<ISomeInterface>(), cntnr.Resolve<ISomeInterface>()));

sealed class A
{
    private B _obj;

    public A(
        B? obj)
    {
        _obj = obj ?? throw new ArgumentNullException(nameof(obj));
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

sealed class B: ISomeInterface
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

sealed class C: ISomeInterface
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