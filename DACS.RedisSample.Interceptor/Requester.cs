using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using DACS.RedisSample.Domain;
using StackExchange.Redis;

namespace DACS.RedisSample.Interceptor
{
    
    public sealed class Requester
    {

        public async Task<IEnumerable<Book>> RequestAsync(
            string authorSubstr = "1234",
            string titleSubstr = "56",
            int minYear = -3000,
            int maxYear = 2022,
            CancellationToken token = default)
        {
            // TODO: redis cache

            var hash = ComputeHash(authorSubstr, titleSubstr, minYear, maxYear);
            var hashString = string.Concat(hash
                .Select(b =>
                {
                    var div = b / 16;
                    var rem = b % 16;
                    return $"{(div < 10 ? div + '0' : div + 'A' - 10)}{(rem < 10 ? rem + '0' : rem + 'A' - 10)}";
                }));
            var redisConnection = await ConnectionMultiplexer.ConnectAsync("127.0.0.1:6379");
            var redisDatabase = redisConnection.GetDatabase();
            var cachedRequestResult = redisDatabase.StringGet(hashString);
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
                    
                    if (!int.TryParse(stringParts[2], out var count))
                    {
                        throw new ApplicationException("Invalid input file format");
                    }
                    
                    // TODO: extra count value validation
                    
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

            var result = resultList
                .Where(book => book.Author.Contains(authorSubstr))
                .Where(book => book.Title.Contains(titleSubstr))
                .Where(book => book.Year.Year >= minYear && book.Year.Year <= maxYear)
                .ToArray();
            
            
            
            return result;
            }
        }

        private byte[] ComputeHash(string authorSubstr, string titleSubstr, int minYear, int maxYear)
        {
            using (var md5 = MD5.Create())
            {
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
    
}