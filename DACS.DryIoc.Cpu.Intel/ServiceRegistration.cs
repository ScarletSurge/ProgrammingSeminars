using DACS.DryIoc.Domain;
using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.Cpu.Intel
{
    public class ServiceRegistration : IServiceRegistrator
    {
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<ICpu, IntelCpu>(Reuse.Transient);
        }
    }
}