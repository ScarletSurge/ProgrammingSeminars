using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace DACS.RedisSample.Domain
{
    public static class SerializationHelper
    {

        public static async Task<byte[]> ToByteArrayAsync(this string value,
            CancellationToken token = default)
        {
            if (value is null)
            {
                throw new ArgumentNullException(nameof(value));
            }
            
            await using var stream = new MemoryStream();
            await stream.WriteAsync(BitConverter.GetBytes(value.Length), token);
            await stream.WriteAsync(value
                .SelectMany(BitConverter.GetBytes)
                .ToArray(), token);
            var result = stream.GetBuffer();
            Array.Resize(ref result, sizeof(int) + sizeof(char) * value.Length);
            return result;
        }

        public static async Task<string> StringFromMemoryStreamAsync(this MemoryStream stream,
            CancellationToken token = default)
        {
            var destination = new byte[sizeof(int)];
            await stream.ReadAsync(destination, 0, destination.Length, token);
            var charsCount = BitConverter.ToInt32(destination, 0);

            destination = new byte[sizeof(char) * charsCount];
            await stream.ReadAsync(destination, 0, destination.Length, token);

            return Encoding.Unicode.GetString(destination);
        }
        
    }
}