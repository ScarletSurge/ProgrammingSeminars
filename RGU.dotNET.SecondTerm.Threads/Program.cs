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

        public static void Main(
            string[] args)
        {
            // WaitCallback
            ThreadPool.QueueUserWorkItem(Foo2, 10, false);
            var thr = new Thread(Foo1)
            {
                IsBackground = false
            };
            thr.Start("\"12345\"");
            Thread.Sleep(2000);
            Console.WriteLine("Waiting...");
            //thr.Join();
            Console.WriteLine("Wait succeeded!");
        }
        
    }
    
}