using System;
using System.IO;
using System.Text;
using System.Threading;

namespace DACS.MultithreadingAndAsynchronious
{
    class Program
    {
        static void Main(string[] args)
        {
            // var thread = new Thread(Foo)
            // {
            //     IsBackground = true
            // };
            // //ThreadPool.QueueUserWorkItem(Foo);
            // //var threadWithParametrizedCallback = new Thread(ParametrizedFoo);
            // thread.Start();
            // Console.WriteLine("Code after Foo() call");
            // thread.Join();
            // // IAsyncResult - oldfag
            // // newfags: Task, Task<TResult>, ValueTask<T>, async/await
            //
            // var sr = new StreamReader(Path.Combine(Environment.CurrentDirectory, "in.txt"));
            // //sr.

            int i = 5;
            object o = (object)i;
            double d = (double)(int)o;
            // sync block index
            // type object pointer

            var s1 = "1234";
            var s2 = "1234";
            var s3 = "12" + "34";
            Console.WriteLine(ReferenceEquals(s1, s2) && ReferenceEquals(s2, s3));
            var s4 = string.Intern(new StringBuilder()
                .Append("12")
                .Append("34")
                .ToString());
            var s5 = string.Intern(new StringBuilder()
                .Append("12")
                .Append("34")
                .ToString());
            Console.WriteLine(ReferenceEquals(s4, s5));
            Console.WriteLine(ReferenceEquals(s1, s4));
            Console.WriteLine(ReferenceEquals(s1, s5));
        }

        static void Foo(object parameter)
        {
            Thread.Sleep(100);
            for (int i = 0; i < 100; i++)
            {
                Console.WriteLine(i);
            }
        }

        static void ParametrizedFoo(object parameter)
        {
            
        }
    }
}