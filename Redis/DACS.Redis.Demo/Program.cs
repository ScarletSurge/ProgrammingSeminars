using System;
using System.Text;
using DACS.RedisSample.Interceptor;

namespace DACS.Redis.Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            // serialize/deserialize testing
            /*var book = new Book
            {
                Author = "Вася Пупкин",
                Title = "Название книжки",
                Year = new DateTime(2005, 1, 1),
                SN = "1234567890123",
                Count = 5000
            };

            var serializedBookBytes = default(byte[]);
            using (var stream = new MemoryStream())
            {
                book.SerializeAsync(stream).GetAwaiter().GetResult();
                serializedBookBytes = stream.GetBuffer();
            }
            
            var deserializedBook = default(Book);
            using (var stream = new MemoryStream(serializedBookBytes))
            {
                deserializedBook = Book.Deserialize(stream).GetAwaiter().GetResult();
            }
            
            Console.WriteLine(book.Equals(deserializedBook));*/

            var requester = new Requester();
            
            var result = requester.RequestAsync().GetAwaiter().GetResult();

            foreach (var item in result)
            {
                Console.WriteLine(item);
            }

            Console.WriteLine();
            
            result = requester.RequestAsync("Мемч").GetAwaiter().GetResult();

            foreach (var item in result)
            {
                Console.WriteLine(item);
            }
        }
    }
}