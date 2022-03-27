using System;

using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Compudahter.Dell
{
    
    public sealed class DellCompudahter : ICompudahter
    {
        
        #region Constructors

        public DellCompudahter(
            ICpu cpu,
            IOperatingSystem operatingSystem)
        {
            Cpu = cpu ?? throw new ArgumentNullException(nameof(cpu));
            OperatingSystem = operatingSystem ??
                throw new ArgumentNullException(nameof(operatingSystem));
        }
        
        #endregion
        
        #region ICompudahter implementation
        
        public ICpu Cpu { get; }
        
        public IOperatingSystem OperatingSystem { get; }
        
        public void PowerOn()
        {
            Console.WriteLine("Dell power on started...");
            
            Cpu.Razgon();
            
            Console.WriteLine("Dell power on finished...");
        }

        public void PowerOff()
        {
            Console.WriteLine("Dell power off started...");
            Console.WriteLine("Dell power off finished...");
        }
        
        #endregion
        
        #region System.Object overrides

        public override string ToString()
        {
            return $"Producer: Dell," +
                   $" Cpu producer: {Cpu.Producer}," +
                   $"OS: {OperatingSystem.Name}, version: {OperatingSystem.Version}";
        }

        #endregion
        
    }
    
}