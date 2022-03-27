using System;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace DACS.Redis.Domain
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class Book : IEquatable<Book>
    {
        /// <summary>
        /// 
        /// </summary>
        public string Author { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public string Title { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public DateTime Year { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public string SN { get; set; }
        /// <summary>
        /// Тираж
        /// </summary>
        public int Count { get; set; }
        
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public async Task<int> SerializeAsync(MemoryStream stream, CancellationToken token = default)
        {
            var writtenBytesCount = 0;
            
            var authorBytes = await (Author ?? string.Empty).ToByteArrayAsync(token);
            writtenBytesCount += authorBytes.Length;
            await stream.WriteAsync(authorBytes, token);

            var titleBytes = await (Title ?? string.Empty).ToByteArrayAsync(token);
            writtenBytesCount += titleBytes.Length;
            await stream.WriteAsync(titleBytes, token);

            writtenBytesCount += sizeof(int);
            await stream.WriteAsync(BitConverter.GetBytes(Year.Year), token);

            var snBytes = await (SN ?? string.Empty).ToByteArrayAsync(token);
            writtenBytesCount += snBytes.Length;
            await stream.WriteAsync(snBytes, token);
            
            await stream.WriteAsync(BitConverter.GetBytes(Count), token);
            writtenBytesCount += sizeof(int);

            return writtenBytesCount;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public static async Task<Book> DeserializeAsync(MemoryStream stream, CancellationToken token = default)
        {
            var intBytesBuffer = new byte[sizeof(int)];
            
            var author = await stream.StringFromMemoryStreamAsync(token)
                .ConfigureAwait(false);
            var title = await stream.StringFromMemoryStreamAsync(token)
                .ConfigureAwait(false);
            _ = await stream.ReadAsync(intBytesBuffer, 0, intBytesBuffer.Length, token)
                .ConfigureAwait(false);
            var year = BitConverter.ToInt32(intBytesBuffer);
            var sn = await stream.StringFromMemoryStreamAsync(token)
                .ConfigureAwait(false);
            _ = await stream.ReadAsync(intBytesBuffer, 0, intBytesBuffer.Length, token)
                .ConfigureAwait(false);
            var count = BitConverter.ToInt32(intBytesBuffer);

            return new Book
            {
                Author = author,
                Title = title,
                Year = new DateTime(year, 1, 1),
                SN = sn,
                Count = count
            };
        }

        public bool Equals(Book other)
        {
            if (ReferenceEquals(null, other)) return false;
            if (ReferenceEquals(this, other)) return true;
            return Author == other.Author && Title == other.Title && Year.Equals(other.Year) && SN == other.SN && Count == other.Count;
        }

        public override bool Equals(object obj)
        {
            return ReferenceEquals(this, obj) || obj is Book other && Equals(other);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Author, Title, Year, SN, Count);
        }

        public override string ToString()
        {
            return $"[{Author}] [{Title}] [{Year.Year}] [{SN}] [{Count}]";
        }
    }
    
}