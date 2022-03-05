using StackExchange.Redis;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using DACS.RedisSample.Domain;

namespace DACS.RedisSample.Interceptor
{
    
    // IoC/DI, DryIoC
    // Autofac
    // Windsor.Castle
    // IServiceProvider (Microsoft)
    // DryIoc
    // Unity (Microsoft)
    
    /// <summary>
    /// 
    /// </summary>
    public sealed class Requester
    {
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="authorSubstr"></param>
        /// <param name="titleSubstr"></param>
        /// <param name="minYear"></param>
        /// <param name="maxYear"></param>
        /// <param name="token"></param>
        /// <returns></returns>
        /// <exception cref="ApplicationException"></exception>
        public async Task<IEnumerable<Book>> RequestAsync(
            string authorSubstr = "",
            string titleSubstr = "",
            int minYear = -3000,
            int maxYear = 2022,
            CancellationToken token = default)
        {
            var hash = ComputeHash(authorSubstr, titleSubstr, minYear, maxYear);
            var hashString = hash.ToHexString();
            var redisConnection = await ConnectionMultiplexer.ConnectAsync("127.0.0.1:6379");
            var redisDatabase = redisConnection.GetDatabase();
            var cachedRequestResult = await redisDatabase.StringGetAsync(hashString);
            
            if (cachedRequestResult == RedisValue.Null)
            {
                var booksFilePath = Path.Combine(Environment.CurrentDirectory, "books.csv");
                var resultList = new List<Book>();
                using (var reader = new StreamReader(new FileStream(booksFilePath, FileMode.Open)))
                {
                    while (!reader.EndOfStream)
                    {
                        var @string = await reader.ReadLineAsync();
                        
                        token.ThrowIfCancellationRequested();
                        
                        var stringParts = @string.Split(new[] { ',' },
                            StringSplitOptions.RemoveEmptyEntries);
    
                        if (stringParts.Length != 5)
                        {
                            throw new ApplicationException("Invalid input file format");
                        }
    
                        var author = stringParts[0];
                        var title = stringParts[1];
    
                        if (!int.TryParse(stringParts[2], out var yearNumber))
                        {
                            throw new ApplicationException("Invalid input file format");
                        }
                        
                        // TODO: extra year value validation
    
                        var year = new DateTime(yearNumber, 1, 1);
    
                        var sn = stringParts[3];
                        /*if (sn.Length != 13)
                        {
                            throw new ApplicationException("Invalid input file format");
                        }*/
                        
                        if (!int.TryParse(stringParts[4], out var count))
                        {
                            throw new ApplicationException("Invalid input file format");
                        }
                        
                        // TODO: extra count value validation
                        // TODO: move validation after data received
                        resultList.Add(new Book
                        {
                            Author = author,
                            Title = title,
                            Year = year,
                            SN = sn,
                            Count = count
                        });
                    }
                }
    
                var receivedBooks = resultList
                    .Where(book => book.Author.Contains(authorSubstr))
                    .Where(book => book.Title.Contains(titleSubstr))
                    .Where(book => book.Year.Year >= minYear && book.Year.Year <= maxYear)
                    .ToArray();

                var serializedBooks = default(byte[]);
                var writtenBytesCount = sizeof(int);
                await using (var stream = new MemoryStream())
                {
                    await stream.WriteAsync(BitConverter.GetBytes(receivedBooks.Length), token);
                    
                    foreach (var receivedBook in receivedBooks)
                    {
                        writtenBytesCount += await receivedBook.SerializeAsync(stream, token);
                    }
                    
                    serializedBooks = stream.GetBuffer();
                }
                
                Array.Resize(ref serializedBooks, writtenBytesCount);

                var toCache = serializedBooks.ToHexString();

                await redisDatabase.StringSetAsync(hashString, toCache, TimeSpan.FromMinutes(10));
                
                return receivedBooks;
            }

            var cachedBooksBytes = cachedRequestResult.ToString()
                .FromHexString();

            await using var cachedBooksStream = new MemoryStream(cachedBooksBytes);
            var cachedBooksCountBytes = new byte[sizeof(int)];
            _ = await cachedBooksStream.ReadAsync(cachedBooksCountBytes, token);
            var cachedBooksCount = BitConverter.ToInt32(cachedBooksCountBytes);
            var cachedBooksList = new List<Book>(cachedBooksCount);
            for (var i = 0; i < cachedBooksCount; i++)
            {
                cachedBooksList.Add(await Book.DeserializeAsync(cachedBooksStream, token));
            }

            return cachedBooksList.ToArray();
        }
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="authorSubstr"></param>
        /// <param name="titleSubstr"></param>
        /// <param name="minYear"></param>
        /// <param name="maxYear"></param>
        /// <returns></returns>
        [Obsolete("это калич -_-")]
        private static byte[] ComputeHash(string authorSubstr, string titleSubstr, int minYear, int maxYear)
        {
            using var md5 = MD5.Create();
            
            var authorSubstrBytes = Encoding.Unicode.GetBytes(authorSubstr);
            var titleSubstrBytes = Encoding.Unicode.GetBytes(titleSubstr);
            var minYearBytes = BitConverter.GetBytes(minYear);
            var maxYearBytes = BitConverter.GetBytes(maxYear);

            var notConcatenated = new[]
            {
                authorSubstrBytes,
                titleSubstrBytes,
                minYearBytes,
                maxYearBytes
            };

            var concatenated = notConcatenated.SelectMany(x => x)
                .ToArray();
                
            return md5.ComputeHash(concatenated);
        }
        
    }
    
}