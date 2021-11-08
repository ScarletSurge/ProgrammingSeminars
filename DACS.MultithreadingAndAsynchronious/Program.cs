using System;
using System.IO;
using System.Threading;

namespace DACS.MultithreadingAndAsynchronious
{
    class Program
    {
        static void Main(string[] args)
        {
            var thread = new Thread(Foo)
            {
                IsBackground = true
            };
            //ThreadPool.QueueUserWorkItem(Foo);
            //var threadWithParametrizedCallback = new Thread(ParametrizedFoo);
            thread.Start();
            Console.WriteLine("Code after Foo() call");
            thread.Join();
            // IAsyncResult - oldfag
            // newfags: Task, Task<TResult>, ValueTask<T>, async/await

            var sr = new StreamReader(Path.Combine(Environment.CurrentDirectory, "in.txt"));
            //sr.
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