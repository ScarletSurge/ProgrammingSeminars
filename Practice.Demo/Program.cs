using DryIoc;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

using Practice.DI.Core;
using Practice.Services.IEnumerableExpander.Core;
using Container = DryIoc.Container;

namespace Practice.Demo
{

    // public delegate void MyDelegateType(int value1, string value2);
    //
    // class EventHolder
    // {
    //
    //     public event MyDelegateType SomeEvent;
    //     
    //     // event:
    //     private MyDelegateType _SomeEvent;
    //
    //     protected void SubscribeToSomeEvent(MyDelegateType toSubscribe)
    //     {
    //         _SomeEvent += toSubscribe;
    //     }
    //     
    //     protected void UnubscribeToSomeEvent(MyDelegateType toUnsubscribe)
    //     {
    //         _SomeEvent -= toUnsubscribe;
    //     }
    //
    //     void foo()
    //     {
    //         SomeEvent(4, "4");
    //     }
    //
    // }

    class ASettings
    {
        public int Setting1 { get; set; }

        public string Setting2 { get; set; }
    }
    
    class Program
    {
        private static readonly DryIoc.Container Container;

        static Program()
        {
            Container = new Container();
        }

        interface ISomeInterface
        {
            string InterfaceMethod();
        }

        class A : ISomeInterface
        {
            private ASettings _aSettings;
            
            public A(ASettings aSettings)
            {
                _aSettings = aSettings ?? throw new ArgumentNullException(nameof(aSettings));
            }
            
            public string InterfaceMethod()
            {
                return $"{nameof(ISomeInterface)} implementation from {nameof(A)} Parameters = [{_aSettings.Setting1}, {_aSettings.Setting2}]";
            }
        }

        class B : ISomeInterface
        {
            public string InterfaceMethod()
            {
                return $"{nameof(ISomeInterface)} implementation from {nameof(B)}";
            }
        }

        static void Main(string[] args)
        {
            var configuration = new ConfigurationBuilder()
                .SetBasePath(Environment.CurrentDirectory)
                .AddJsonFile("appsettings.json", false)
                .AddJsonFile("appsettings.Development.json", true)
                .Build() as IConfiguration;

            Container.Register<ISomeInterface, A>(Reuse.Singleton);
            Container.RegisterInstance(new ASettings
            {
                Setting1 = int.Parse(configuration["ASettings:Settings1"]),
                Setting2 = configuration["ASettings:Settings2"]
            });

            foreach (var moduleSettings in configuration.GetSection("Modules").Get<ModuleSettings[]>())
            {
                if (!moduleSettings.Used)
                {
                    continue;
                }

                var assemblyName = new AssemblyName(moduleSettings.Assembly);
                var assembly = Assembly.Load(assemblyName);

                var targetType = assembly
                    .GetTypes()
                    .SingleOrDefault(type => type.GetInterfaces().Contains(typeof(IPracticeServiceRegistrator)));

                if (targetType is null)
                {
                    // TODO: logs & exception
                    continue;
                }
                
                ((IPracticeServiceRegistrator)Activator.CreateInstance(targetType))
                    .Register(Container, configuration);
            }

            Console.WriteLine(Container.Resolve<ISomeInterface>().InterfaceMethod());

            var a1 = Container.Resolve<ISomeInterface>();
            var a2 = Container.Resolve<ISomeInterface>();
            
            Console.WriteLine(ReferenceEquals(a1, a2));

            var transform = Container.Resolve<IEnumerableExpander<int>>();
            var expand = transform.Expand(new[] { 1, 2, 3 }, EqualityComparer<int>.Default);
            foreach (var subset in expand)
            {
                Console.Write("{ ");
                foreach (var i in subset)
                {
                    Console.Write($"{i} ");
                }
                Console.WriteLine("}");
            }
            
            // var eh = new EventHolder();
            // eh.SomeEvent += (value1, value2) =>
            // {
            //     Console.WriteLine($"{value1} {value2}");
            // };
            //
            // eh.SomeEvent -= (value1, value2) =>
            // {
            //
            // };

            //eh.SomeEvent(4, "4");

            //Action<string[]> m = Main;
            //Console.WriteLine("Hello World!");

            // var a = new Class1();
            // var value = a.A;
            // a.A = 10;

            // A b = new B();
            // A c = new C();
            //
            // Console.WriteLine($"b: {b.Bar()}{Environment.NewLine}c: {c.Bar()}");
            //
            // b.Foo();
            // c.Foo();
            //
            // var b1 = new B1();

            // in, ref, out, params
            // const, readonly
            // object, object methods

            // var s1 = "abcd";
            // var s2 = "abcd";
            //
            // var sb = new StringBuilder();
            // sb.Append("123")
            //     .AppendFormat("{0} abc {1}", new object(), 35)
            //     .AppendLine("abc")
            //     // ...
            //     ;
            // var s = sb.ToString();
            //
            // Console.Write("Input an string: ");
            // var s3 = Console.ReadLine();
            // s3 = string.Intern(s3);
            //
            // Console.WriteLine("{1}{0}{2}{0}{3}", Environment.NewLine,
            //     s1.Equals(s2),
            //     s2.Equals(s3),
            //     s3.Equals(s1)
            //     // ReferenceEquals(s1, s2),
            //     // ReferenceEquals(s2, s3),
            //     // ReferenceEquals(s3, s1)
            //     );

            // var service = new B();
            // int @int = 0;
            //
            // object o = null;
            //
            // int int1;
            // service.ByNothing(o);
            // Console.WriteLine($"After ByNothing(): o = {o}");
            // service.ByRef(ref o);
            // Console.WriteLine($"After ByRef(): o = {o}");
            // service.ByOut(out o);
            // Console.WriteLine($"After ByOut(): o = {o}");

            // is, as
            // params
            // const, readonly
            // this, base, new
            // ICloneable, IEquatable<T>, IComparable, IComparable<T>,
            // IComparer<T>, IEqualityComparer<T>, IDisposable,
            // IEnumerator, IEnumerator<T>, IEnumerable, IEnumerable<T>
            // generics + operator overloading + constraints

            // int[] arr = new int[20];
            //
            // ParamsDemo(1, 1.1, new object(), new B(), new B1(), new CancellationToken(), StringSplitOptions.RemoveEmptyEntries);
            // //ParamsDemo(arr);

            // var cr = new ConstAndReadonly(new object());
            // cr = new ConstAndReadonly(new object());
            //
            // var list = new List<int> { 1, 2, 3, 4, 5 };
            // var oddValuesFromList = list.Where(v => v % 2 == 1)
            //     ;//.ToList();
            //
            // oddValuesFromList.ToArray();
            //
            // Enumerable.Where(list, IsOdd);
            //
            // bool IsOdd(int value)
            // {
            //     return value % 2 == 1;
            // }

            // var derived = new Derived(5);
            // derived.Foo();
            //
            // ISomeInterface i1 = new SomeInterfaceImplementation();
            // i1.SomeAction();
            // i1 = new SomeOtherInterfaceImplementation();
            // i1.SomeAction();
            // deployment time behavior

            // var logContext = new LogContext(Path.Combine(Environment.CurrentDirectory, "log.txt"));
            // logContext.Log("message 1");
            // logContext.Log("message 2");
            // logContext.Log("message 3");
            // logContext.Dispose();

            // var logContext1 = default(LogContext);
            // try
            // {
            //     logContext1 = new LogContext(Path.Combine(Environment.CurrentDirectory, "log.txt"));
            //
            //     logContext1.Log("message 1");
            //     logContext1.Log("message 2");
            //     logContext1.Log("message 3");
            // }
            // finally
            // {
            //     if (logContext1 != null)
            //     {
            //         logContext1.Dispose();
            //     }
            //     
            //     logContext1?.Dispose();
            // }

            // var eq1 = new EquatableImplementation();
            // var eq2 = new EquatableImplementation();
            // var eq3 = default(EquatableImplementation);
            //
            // var eq1ObjRef = eq1 as object;
            //
            // var equalityComparisonResult = eq2.Equals(eq3);

            // var randomSource = new Random();
            // var values = new SomeClass<TImpl>[100];
            // for (var i = 0; i < values.Length; i++)
            // {
            //     values[i] = new SomeClass<TImpl>(randomSource.Next(10),
            //         randomSource.Next(10).ToString(), new TImpl(i));
            // }
            //
            // var selectedValues1 = values.Distinct(new SomeClassEqualityComparer<TImpl>())
            //     .ToArray();
            // var selectedValues2 = values.Distinct(new SomeOtherClassEqualityComparer<TImpl>())
            //     .ToArray();
            //
            // selectedValues2.ToList().Sort(new SomeClassComparer<TImpl>());
            //
            // Console.WriteLine("Selected values with SomeClassEqualityComparer:");
            // foreach (var selectedValue1 in selectedValues1)
            // {
            //     Console.WriteLine($"\t{selectedValue1}");
            // }
            //
            // Console.WriteLine($"{Environment.NewLine}Selected values with SomeOtherClassEqualityComparer:");
            // foreach (var selectedValue2 in selectedValues2)
            // {
            //     Console.WriteLine($"\t{selectedValue2}");
            // }

            // IEnumerable;
            // IEnumerable<int>;
            // IEnumerator;
            // IEnumerator<int>;
            // // IAsyncEnumerator<int>;
            // // IAsyncEnumerable<int>;
            //
            //
            // object o = new object();
            //
            // int a = 10;
            // var aCopied = a;
            // object aBoxed = (object)a;
            // int aUnboxed = (int)aBoxed;
            //
            // var ints = new List<int>(10000);
            //
            // ints.GetEnumerator();
            // var intsGenericIterator = ((IEnumerable)ints).GetEnumerator();
            // //intsGenericIterator.
            //
            // foreach (var @int in new B())
            // {
            //     
            // }

            // var obj = default(object);
            //
            // if (obj != null) // if (obj is object)
            // {
            //     // TODO: work with obj
            // }
            //
            // obj?.Equals(new object());

            // var matrix = new EnumerableMatrix(new double[3, 4]
            // {
            //     { 1, 2, 3, 4 },
            //     { 5, 6, -1.1, 8 },
            //     { 9, -10, 11, -12.3 }
            // });
            //
            // var otherMatrix = new EnumerableMatrix(new double[3, 4]
            // {
            //     { 1, 2, 3, 4 },
            //     { 5, 6, -1.1, 8 },
            //     { 9, -10, 11, -12.3 }
            // });
            //
            // Console.WriteLine($"{matrix} + {otherMatrix} == {matrix += otherMatrix}");
            // Console.Write($"{Environment.NewLine}{matrix}{Environment.NewLine}");
            //
            // // delegate, event, lambda
            // // StreamReader/StreamWriter, FileInfo/DirectoryInfo, System.IO
            // // DateTime/TimeSpan
            // // List<T>, Dictionary<T>, etc.
            // // Heaps (binary/binomial)
            // // try/catch/finally
            // // reflection, IoC, SL/DI, implementation (DryIoC), constructor/setter injection
            //
            // try
            // {
            //     var parsedInt = int.Parse("123.");
            // }
            // catch (FormatException ex) when (ex.StackTrace.Length > 3)
            // {
            //     Console.Write("Invalid format 1!");
            //     //throw;
            // }
            // catch (FormatException ex) when (ex.StackTrace.Length > 3)
            // {
            //     Console.Write("Invalid format 2!");
            //     //throw;
            // }
            // finally
            // {
            //     
            // }
            //
            // var currentDateTime = DateTime.Now;
            // Thread.Sleep(1000);
            // var currentDateTime2 = DateTime.Now;
            // Console.WriteLine($"{Environment.NewLine}{currentDateTime2 - currentDateTime}");
            //
            // string foo1(int param)
            // {
            //     return "1";
            // }
            //
            // string foo2(int param)
            // {
            //     return "2";
            // }
            //
            // Func<int, string> fooMethods = foo1;
            // fooMethods += foo2;
            // fooMethods += foo1;
            //
            // // fooMethods += (i1, i2) =>
            // // {
            // //     return "1".ToString();
            // // };
            //
            // fooMethods -= foo1;
            // fooMethods -= foo1;
            // fooMethods -= foo2;
            //
            // foreach (var fooMethod in fooMethods.GetInvocationList())
            // {
            //     fooMethod.DynamicInvoke(5);
            // }
            //
            // var s = fooMethods?.Invoke(5) ?? "<null>";
            // Console.WriteLine(s);
            //
            // // if (fooDelegate != null)
            // // {
            // //     var s = fooMethods(5);
            // // }
            //
            // var collection = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            //
            // bool IsOdd(int value)
            // {
            //     return value % 2 == 1;
            // }
            //
            // foreach (var oddItem in collection.Where(IsOdd))
            // {
            //     Console.Write($"{oddItem} ");
            // }
            //
            // // Predicate<int> p;
            // // EventHandler
            // // Action<int, int, Action<int>>, Func<int>, //Comparison<int>, Predicate<int>, EventHandler
            //
            // int[] arr = new int[] { 1, 2, 3, 4, 5 };
            //
            // List<int> lst = new List<int>() { 1, 2, 3, 4, 5 };
            // LinkedList<int> llst = new LinkedList<int>();
            // Dictionary<int, string> dict = new Dictionary<int, string>();

            var typeOfClass = typeof(Class<int>);
            Console.WriteLine(typeOfClass.Namespace);
            Console.WriteLine(typeOfClass.IsClass);
            Console.WriteLine(typeOfClass.IsEnum);
            Console.WriteLine(typeOfClass.IsAbstract);
            Console.WriteLine(typeOfClass.IsInterface);
            Console.WriteLine(typeOfClass.IsNested);
            Console.WriteLine(typeOfClass.IsSealed);
            Console.WriteLine(typeOfClass.IsPublic);
            Console.WriteLine(typeOfClass.IsGenericType);

            var bf = BindingFlags.Default | BindingFlags.Instance | BindingFlags.CreateInstance;
            Console.WriteLine(bf.HasFlag(BindingFlags.FlattenHierarchy));
            Console.WriteLine(bf.HasFlag(BindingFlags.Default));
            
            //i18n

            Console.WriteLine(typeof(Class<int>).Constructors());

            var obj = Activator.CreateInstance(typeof(Class<int>), 5);
            
            Console.WriteLine(obj);
            
            // SortedList<int, int> i = new SortedList<int, int>();
            // var nonGenericSortedList = new SortedList()
            
            Container.Dispose();
        }

        public interface IInterface
        {
            void Foo();

            int Prop { get; set; }

            event Action Event;
        }

        // class Decorator
        // {
        public class Class<T> : IInterface
        {

            public Class(int value)
            {
                Prop = value;
            }

            public void Foo()
            {
                Console.Write($"Foo() from {typeof(Class<T>).Name} called");
            }

            public int Prop { get; set; }

            public event Action Event;

            public override string ToString()
            {
                return $"{nameof(Class<T>)}: {Prop}";
            }
        }
    //}

    // static void ParamsDemo(params object[] list)
        // {
        //     for (var i = 0; i < list.Length; i++)
        //     {
        //         var encoding = list[i] as A;
        //         if (encoding is null)
        //         {
        //             Console.WriteLine("<null>");
        //             continue;
        //         }
        //
        //         Console.WriteLine(encoding);
        //     }
        // }
        
    }
    
}