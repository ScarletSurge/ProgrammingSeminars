using System;
using System.IO;
using System.Linq;
using System.Text;

namespace DACS.RedisSample.Domain
{
    public static class SerializationHelper
    {

        public static byte[] ToByteArray(this string value)
        {
            using var stream = new MemoryStream();
            stream.Write(BitConverter.GetBytes(value.Length));
            stream.Write(value
                .ToCharArray()
                .SelectMany(c => BitConverter.GetBytes(c))
                .ToArray());
            var result = stream.GetBuffer();
            Array.Resize(ref result, sizeof(int) + sizeof(char) * value.Length);
            return result;
        }

        public static string StringFromMemoryStream(this MemoryStream stream
            /*, ref int offset*/)
        {
            var destination = new byte[sizeof(int)];
            stream.Read(destination, 0, destination.Length);
            var charsCount = BitConverter.ToInt32(destination, 0);

            destination = new byte[sizeof(char) * charsCount];
            stream.Read(destination, 0, destination.Length);

            return Encoding.Unicode.GetString(destination);
        }
        
    }
}