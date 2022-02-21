using System;
using System.Linq;
using System.Text;

namespace DACS.RedisSample.Domain
{
    
    public static class ByteArrayExtensions
    {
        
        public static string ToHexString(this byte[] value)
        {
            return new StringBuilder((value ?? throw new ArgumentNullException(nameof(value))).Length * 2)
                .AppendJoin(string.Empty, value.Select(@byte => $"{@byte:x2}"))
                .ToString();
        }
        
    }
    
}