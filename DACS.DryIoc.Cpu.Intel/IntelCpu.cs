using System;
using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Cpu.Intel
{
    
    public sealed class IntelCpu : ICpu
    {
        
        #region Fields

        private readonly CpuSettings _cpuSettings;
        
        #endregion
        
        #region Constructors

        public IntelCpu(CpuSettings settings)
        {
            _cpuSettings = settings
                ?? throw new ArgumentNullException(nameof(settings));
            
            Guid = Guid.NewGuid();
        }
        
        #endregion
        
        #region ICpu inplementation

        public ulong Hz => _cpuSettings.Hz;

        public Guid Guid { get; }

        public int ThreadsCount => _cpuSettings.ThreadsCount;

        public string Producer => _cpuSettings.Producer;
        
        public void Razgon()
        {
            Console.WriteLine("Intel cpu razgon...");
        }
        
        #endregion
        
    }
    
}