using System;

namespace DACS.RedisSample.Domain
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class Book
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
        public byte[] Serialize()
        {
            
        }
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="from"></param>
        /// <returns></returns>
        public static Book Deserialize(byte[] from)
        {
            
        }
    }
    
}