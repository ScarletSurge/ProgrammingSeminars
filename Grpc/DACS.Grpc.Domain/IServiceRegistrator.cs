using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;

namespace DACS.Grpc.Domain;

public interface IServiceRegistrator
{

    public void Register(IServiceCollection serviceProvider, IConfiguration configuration);

}