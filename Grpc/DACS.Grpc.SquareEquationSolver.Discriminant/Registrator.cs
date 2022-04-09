using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;

using DACS.Grpc.Domain;

namespace DACS.Grpc.SquareEquationSolver.Discriminant;

public sealed class Registrator : IServiceRegistrator
{
    
    public void Register(IServiceCollection serviceCollection, IConfiguration configuration)
    {
        serviceCollection.AddSingleton<ISquareEquationSolver, Services.SquareEquationSolver>();
    }
    
}