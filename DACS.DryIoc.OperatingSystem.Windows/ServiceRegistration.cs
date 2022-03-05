using DACS.DryIoc.Domain;
using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.OperatingSystem.Windows
{
    public class ServiceRegistration : IServiceRegistrator
    {
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<IOperatingSystem, WindowsOS>(Reuse.Transient);
        }
    }
}