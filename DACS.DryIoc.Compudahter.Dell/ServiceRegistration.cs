using DACS.DryIoc.Domain;
using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.Compudahter.Dell
{
    public class ServiceRegistration : IServiceRegistrator
    {
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<ICompudahter, DellCompudahter>(Reuse.Transient);
        }
    }
}