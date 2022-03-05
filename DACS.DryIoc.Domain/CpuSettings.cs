using System;

namespace DACS.DryIoc.Domain
{
    
    public class CpuSettings
    {
        
        public ulong Hz { get; set; }
        
        public int ThreadsCount { get; set; }
        
        public string Producer { get; set; }
        
    }
    
}