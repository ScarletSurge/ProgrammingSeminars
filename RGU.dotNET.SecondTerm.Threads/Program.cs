// System.Threading.Thread
// System.Threading.ThreadPool
// System.Threading.ThreadStart
// System.Threading.ParameterizedThreadStart
// System.Threading.Tasks.Parallel
// System.IAsyncResult, BeginInvoke(), EndInvoke()
// System.Threading.Tasks.Task
// System.Threading.Tasks.Task<T>
// System.Threading.Tasks.ValueTask
// System.Threading.Tasks.ValueTask<T>
// System.Threading.CancellationToken
// System.Threading.CancellationTokenSource
// System.Collections.Concurrent
// Thread-safety, lock operator

using System.Collections.Concurrent;

namespace RGU.dotNET.SecondTerm.Threads
{

    class Program
    {

        private static void Foo1()
        {
            Thread.Sleep(6000);
            Console.WriteLine("Program.Foo() is called");
        }
        
        private static void Foo2(
            int value)
        {
            Thread.Sleep(6000);
            Console.WriteLine($"Value: {value}");
            Thread.Sleep(1000);
        }

        class A
        {
            private readonly int _value;
            public A(int value) { _value = value; }

            public override string ToString() { return _value.ToString(); }
        }

        static void Bar(
            ref string value)
        {
            value = "54321";
        }
        
        

        public static void Main(
            string[] args)
        {
            var q = new ConcurrentQueue<string>();
            
            string str = "12345";
            Bar(ref str);
            Console.WriteLine(str);
            //return;
            Console.WriteLine(default(A));
            List<A> objects = new List<A>(10);
            //for (var i = 0; i < objects.Capacity; i++)
            //{
            //    objects[i] = new A(i);
            //}
            
            Parallel.For(0, 10, i =>
            {
                q.Enqueue(i.ToString());
            });

            foreach (var qItem in q)
            {
                Console.WriteLine(qItem);
            }

            var values = new A[10];
            for (var i = 0; i < values.Length; i++)
            {
                values[i] = new A(i);
            }

            Parallel.ForEach(values, value =>
            {
                value = new A(100500);
            });
            
            Parallel.Invoke();

            // // WaitCallback
            // ThreadPool.QueueUserWorkItem(Foo2, 10, false);
            // var thr = new Thread(Foo1)
            // {
            //     IsBackground = false
            // };
            // thr.Start("\"12345\"");
            // Thread.Sleep(2000);
            // Console.WriteLine("Waiting...");
            // //thr.Join();
            // Console.WriteLine("Wait succeeded!");
        }
        
    }
    
}