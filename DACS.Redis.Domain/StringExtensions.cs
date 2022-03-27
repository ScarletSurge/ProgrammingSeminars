using System;

namespace DACS.Redis.Domain
{
    
    public static class StringExtensions
    {
        
        public static byte[] FromHexString(this string value)
        {
            var charsCount = value.Length;
            var result = new byte[charsCount / 2];
            
            for (var i = 0; i < charsCount; i += 2)
            {
                result[i / 2] = Convert.ToByte(value.Substring(i, 2), 16);
            }

            return result;
        }
        
    }
    
}