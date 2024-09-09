using DryIoc;
using Microsoft.Extensions.Configuration;

using RGU.WebProgramming.Server.Core;
using RGU.WebProgramming.Server.Core.Extensions;
using RGU.WebProgramming.Server.MyFirstServiceImplementation.Settings;

namespace RGU.WebProgramming.Server.MyFirstServiceImplementation;

/// <summary>
/// 
/// </summary>
public class ServiceRegistrator:
    IServiceRegistrator
{
    
    #region RGU.WebProgramming.Server.Core.IServiceRegistrator implementation
    
    /// <inheritdoc cref="IServiceRegistrator.Register" />
    public void Register(
        IRegistrator registrator,
        IConfiguration configuration)
    {
        registrator
            .Configure<MyFirstServiceImplementationSettings>(
                configuration.GetSection(nameof(MyFirstServiceImplementationSettings)))
            .Register<IEndpointsConfigurator, EndpointsConfigurator>();
        registrator.Register<Services.MyFirstServiceImplementation>(Reuse.Singleton);
    }
    
    #endregion
    
}