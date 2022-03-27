using DryIoc;
using Microsoft.Extensions.Configuration;

using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Cpu.AMD
{
    
    public sealed class ServiceRegistration : IServiceRegistrator
    {
        
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<ICpu, AMDCpu>(Reuse.Transient);
        }
        
    }
    
}