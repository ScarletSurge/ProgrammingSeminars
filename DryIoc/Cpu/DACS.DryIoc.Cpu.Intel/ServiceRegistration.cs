using DryIoc;
using Microsoft.Extensions.Configuration;

using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Cpu.Intel
{
    
    public sealed class ServiceRegistration : IServiceRegistrator
    {
        
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<ICpu, IntelCpu>(Reuse.Transient);
        }
        
    }
    
}