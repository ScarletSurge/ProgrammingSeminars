// See https://aka.ms/new-console-template for more information

using Practice.Domain;

namespace Practice.Launcher.App
{
    class Program
    {
        
        private static IEnumerable<int> GetCollection()
        {
            yield return 1;
            yield return 2;
            yield return -13;
            yield return 48;
            yield return 11;
            yield return 27;
            foreach (var item in new[] { 1, 2, 3, 4 })
            {
                yield return item;
            }
        }
        
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
            // int, uint, short, ushort, byte, sbyte, long, ulong
            // char, string, bool
            // float, double
            // enum
            // class, struct
            // delegate, event

            //OOPeDemo obj

            //var obj = new OOPeDemo(10);
            //var obj1 = obj;
            //
            //obj.Foo();
            //Console.WriteLine(obj.MyField);
            //var x = obj.MyField = 15;

            //MihailGdeLaby obj = new MihailGdeLaby(16, "ъ");
            //obj.Foo();
            //var obj2 = new MihailGdeLaby(213, "1234");
//
            //Console.WriteLine(obj.Equals(obj2));
            //
            //Console.WriteLine(obj.Equals(16));
            //Console.WriteLine(obj.Equals("ъ"));
            //Console.WriteLine(obj.Equals(4.15));
            
            // obj1 as object

            //MihailGdeLaby obj = new MihailGdeLaby(13, string.Empty);
            //MihailGdeLaby obj1 = new MihailGdeLaby(14, string.Empty);
            //Console.WriteLine(obj.Equals((object)obj1));
            //Console.WriteLine(obj.Equals(obj1 as object));
            //Console.WriteLine(((IEquatable<object>)obj).Equals(obj1));

            //Dictionary<MihailGdeLaby, string> hashTable = new Dictionary<MihailGdeLaby, string>();
//
            //var key = new MihailGdeLaby(13, "123");
            //hashTable.Add(key, "1234");
            //
            //// TODO
            //key.Foo();
            //var removed = hashTable.Remove(key);
            //Console.WriteLine(key);

            //MihailGdeLaby objRef = new MihailGdeKursach("123", 13);
            //Console.WriteLine(objRef.Foo());
            //objRef.SomeMethod();
            //objRef = new MihailGdeDiplom("stroka", 25);
            //Console.WriteLine(objRef.Foo());
            //objRef.SomeMethod();

            int valueByRef = 10;
            RefInOutParamsDemo.NoRefValueDemo(valueByRef);
            Console.WriteLine(valueByRef);
            
            RefInOutParamsDemo.RefValueDemo(ref valueByRef);
            Console.WriteLine(valueByRef);
            
            int valueByOut;
            RefInOutParamsDemo.OutValueDemo(out valueByOut);
            Console.WriteLine(valueByOut);
            
            string refByRef = null;
            RefInOutParamsDemo.NoRefRefDemo(refByRef);
            Console.WriteLine(refByRef);
            
            RefInOutParamsDemo.RefRefDemo(ref refByRef);
            Console.WriteLine(refByRef);
            
            string refByOut;
            RefInOutParamsDemo.OutRefDemo(out refByOut);
            Console.WriteLine(refByOut);
            
            try
            {
                //RefInOutParamsDemo.Average(null);
                var avgParams = RefInOutParamsDemo.Average(1, 2, 3, 4, 5, 6);
                //var avgArray = RefInOutParamsDemo.Average(new int[] { 1, 2, 3, 4, 5, 6 });
            
                Console.WriteLine($"Avg of params == {avgParams}");
                Console.WriteLine($"Avg of array == {RefInOutParamsDemo.Average(new int[] { 1, 2, 3, 4, 5, 6 })}");
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine(ex.Message);
                throw new Exception();
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine(ex.Message);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                // TODO: handler for other exceptions
            }
            finally
            {
                
            }
            
            var ownArray = new OwnArray<MihailGdeLaby>();
            ownArray
                .Insert(new MihailGdeDiplom("123", 1), 0)
                .Insert(new MihailGdeDiplom("234", 2), 1)
                .Insert(new MihailGdeDiplom("345", -3), 0)
                .Insert(new MihailGdeDiplom("456", 4), 1)
                .Insert(new MihailGdeDiplom("456", -12), 1)
                .Insert(new MihailGdeDiplom("456", 28), 1)
                .Insert(new MihailGdeDiplom("456", 13), 1)
                .Insert(new MihailGdeDiplom("456", 87), 1)
                .Insert(new MihailGdeDiplom("456", -113), 1)
                .Insert(new MihailGdeDiplom("567", -5), 3)
                .FindByIndex(3, out var foundByIndex3Value);
            foreach (var item in ownArray)
            {
                Console.Write($"{item} ");
            }
            
            Console.WriteLine($"{Environment.NewLine}ownArray[3] == {foundByIndex3Value}");
            
            ownArray.Sort(MihailGdeLabyComparer.Instance);
            Console.WriteLine(ownArray);

            var dictionary = new Dictionary<MihailGdeLaby, string>(MihailGdeLabyEqualityComparer.Instance);
            dictionary.Add(new MihailGdeDiplom("123", 25), "");
            dictionary.Add(new MihailGdeDiplom("124", 24), "");
            var x = 10;

            var array = GetCollection().Where(IsEven).Select(DivBy2).ToArray();
                // .Where(new Predicate<T>(this, "IsEven"))
            var array1 = GetCollection()
                .Where(x => x % 2 == 0)
                .DivideBy2()
                .ToArray();

            var array2 = EnumerableExtensions.DivideBy2(GetCollection()
                .Where(x => x % 2 == 0)).ToArray();
            
            //var array1 = Enumerable.ToArray(GetCollection());
            foreach (var item in array)
            {
                Console.Write($"{item} ");
            }
            //var obj = default(MihailGdeLaby);
            //obj?.Foo();
            //Console.Write("\"Hi!\"");

            EqComparer<string> dlg = Subscriber;
            dlg += Subscriber2;
            dlg += Subscriber;
            dlg += delegate(string? value1, string? value2)
            {
                if (ReferenceEquals(value1, null) && ReferenceEquals(value2, null))
                {
                    return true;
                }

                if (ReferenceEquals(value1, null))
                {
                    return false;
                }

                if (ReferenceEquals(value2, null))
                {
                    return false;
                }
                
                return value1.Equals(value2, StringComparison.Ordinal);
            };
            Delegates(dlg);
            DelegateVsEventDemoDemo();
        }

        private static bool IsEven(int value) // Func<int, bool>
        {
            return value % 2 == 0;
        }

        private static int DivBy2(int value)
        {
            return value / 2;
        }

        private static bool Subscriber(string? value1, string? value2)
        {
            Console.WriteLine($"{Environment.NewLine}Subscriber method work...");
            return true;
        }

        private static bool Subscriber2(string? value1, string? value2)
        {
            Console.WriteLine($"{Environment.NewLine}Subscriber2 method work...");
            return false;
        }
        
        // Func<int, MihailGdeKursach[], IEnumerable<string>, string>
        //public string Foo(
        //    int value1,
        //    MihailGdeKursach[] value2,
        //    IEnumerable<string> value3)
        //{}
//
        //public int Foo1()
        //{
        //}
// Func<int>

        // delegate Delegate MulticastDelegate
        // Action<int, MihailGdeKursach[], IEnumerable<string>>
        // Action<...>, Func<..., T>
        // Predicate<T> == Func<T, bool>
        // Comparer<T> == Func<T, T, int>
        // EventHandler == Action<object, EventArgs>

        private static void Delegates(EqComparer<string> dlg)
        {
            //var result = dlg("", "");
            var result = dlg?.Invoke("", "123");
            Console.WriteLine(result);
        }

        private static void DelegateVsEventDemoDemo()
        {
            var obj = new DelegateVsEventDemo();
            obj.Action += (@int, @string) =>
            {
                Console.WriteLine("Lambda subscriber work...");
            };
            obj.Action += delegate(int @int, string @string)
            {
                Console.WriteLine("Anonymous function work...");
            };
            //obj.Action?.Invoke(1, "");
        }
        public delegate bool EqComparer<in T>(T? obj1, T? obj2);
    }
}