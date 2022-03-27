using DryIoc;
using Microsoft.Extensions.Configuration;

using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Compudahter.Dell
{
    
    public sealed class ServiceRegistration : IServiceRegistrator
    {
        
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            registrator.Register<ICompudahter, DellCompudahter>(Reuse.Transient);
        }
        
    }
    
}