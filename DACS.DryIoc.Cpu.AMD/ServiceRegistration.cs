using DACS.DryIoc.Domain;
using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.Cpu.AMD
{
    public class ServiceRegistration : IServiceRegistrator
    {
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<ICpu, AMDCpu>(Reuse.Transient);
        }
    }
}