using System;

namespace DACS.DryIoc.Domain
{
    
    /// <summary>
    /// 
    /// </summary>
    public interface ICpu
    {

        /// <summary>
        /// 
        /// </summary>
        ulong Hz { get; }

        /// <summary>
        /// 
        /// </summary>
        Guid Guid { get; }

        /// <summary>
        /// 
        /// </summary>
        int ThreadsCount { get; }

        /// <summary>
        /// 
        /// </summary>
        string Producer { get; }

        /// <summary>
        /// 
        /// </summary>
        void Razgon();

    }
    
}