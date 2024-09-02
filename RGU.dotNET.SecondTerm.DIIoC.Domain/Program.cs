// See https://aka.ms/new-console-template for more information
// Artifactory (JFrog, nuget.org)
// packet (Maven, Ruby Gem, NuGet)

// Autofac
// Castle.Windsor (по диагонали)
// Ninject (для истории)
// Unity (по диагонали)
// IServiceRegistrator

using DryIoc;

var container = new Container();
//var a = default(A);
//container.RegisterInstance(a = new A(new B()));
container.Register<B>();
container.Register<ISomeInterface3, C>();
container.Register<ISomeInterface1, A>(Reuse.Singleton);
container.RegisterMapping<ISomeInterface2, ISomeInterface1>();

//

var a1 = container.Resolve<ISomeInterface1>();
var a2 = container.Resolve<ISomeInterface2>();
var a3 = container.Resolve<ISomeInterface3>();
Console.WriteLine(ReferenceEquals(a1, a2));
a1.Foo();
a2.Foo();
a3.Foo();
var x = 10;

class B
{
    
}

class C: ISomeInterface3
{
    public void Foo()
    {
        Console.WriteLine("C.Foo() called");
    }
}

public interface ISomeInterface1
{
    void Foo();
}

public interface ISomeInterface2
{
    void Foo();
}

public interface ISomeInterface3
{
    void Foo();
}

class A: ISomeInterface1, ISomeInterface2, ISomeInterface3
{
    private readonly B _value;

    void ISomeInterface1.Foo()
    {
        Console.WriteLine("A.Foo() for interface1 called");
    }

    void ISomeInterface2.Foo()
    {
        Console.WriteLine("A.Foo() for interface2 called");
    }

    void ISomeInterface3.Foo()
    {
        Console.WriteLine("A.Foo() for interface3 called");
    }
    
    public A(B value)
    {
        _value = value;
    }
}

//var b = new B();
//// TODO: use b
//
//var cntnr = new Container();
//cntnr.RegisterMany<A>();
//cntnr.Register<I1, D>();
//cntnr.Register<B>(Reuse.Singleton);
////cntnr.RegisterInstance(b);
//cntnr.Register<C>(Reuse.Transient);
////cntnr.RegisterMapping<ISomeInterface, C>();
//cntnr.RegisterMapping<ISomeInterface, B>();

//var resolved = cntnr.Resolve<ISomeInterface>();
//Console.WriteLine(ReferenceEquals(resolved, cntnr.Resolve<B>()));
//Console.WriteLine(ReferenceEquals(resolved, b));

// Register
// RegisterMany
// RegisterInstance
// RegisterMapping
// RegisterDelegate
// Resolve
// ResolveMany

//Console.WriteLine("Hello, World!");
//Console.WriteLine(ReferenceEquals(cntnr.Resolve<ISomeInterface>(), cntnr.Resolve<ISomeInterface>()));