using DACS.RedisSample.Interceptor;

namespace DACS.RedisSample.Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            var result = new Requester().RequestAsync().GetAwaiter().GetResult();
        }
    }
}