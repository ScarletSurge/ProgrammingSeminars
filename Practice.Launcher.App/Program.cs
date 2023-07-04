// See https://aka.ms/new-console-template for more information

using Practice.Domain;

namespace Practice.Launcher.App
{
    class Program
    {
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

            var ownArray = new OwnArray();
            foreach (var item in ownArray)
            {
                Console.Write($"{item} ");
            }
        }
    }
}