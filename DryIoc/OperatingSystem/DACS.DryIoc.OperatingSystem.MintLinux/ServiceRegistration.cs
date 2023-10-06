using DACS.DryIoc.Domain;
using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.OperatingSystem.MintLinux
{
    public class ServiceRegistration : IServiceRegistrator
    {
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<IOperatingSystem, MintLinuxOS>(Reuse.Transient);
            registrator.Register<OperatingSystemSettings>(Reuse.Singleton);
        }
    }
}