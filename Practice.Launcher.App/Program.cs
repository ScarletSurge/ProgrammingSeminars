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

            MihailGdeLaby obj = new MihailGdeLaby(16, "ъ");
            obj.Foo();
            var obj2 = new MihailGdeLaby(213, "dick");

            Console.WriteLine(obj.Equals(obj2));
            
            Console.WriteLine(obj.Equals(16));
            Console.WriteLine(obj.Equals("ъ"));
            Console.WriteLine(obj.Equals(4.15));

        }
    }
}