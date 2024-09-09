using DryIoc;
using Microsoft.Extensions.Configuration;

using RGU.WebProgramming.Server.Core;
using RGU.WebProgramming.Server.Core.Extensions;
using RGU.WebProgramming.Server.Grpc.Settings;

namespace RGU.WebProgramming.Server.Grpc;

/// <summary>
/// 
/// </summary>
public sealed class ServiceRegistrator:
    IServiceRegistrator
{
    
    #region RGU.WebProgramming.Server.Core.IServiceRegistrator implementation
    
    /// <inheritdoc cref="IServiceRegistrator.Register" />
    public void Register(
        IRegistrator registrator,
        IConfiguration configuration)
    {
        registrator
            .Configure<ServerSettings>(configuration.GetSection(nameof(ServerSettings)))
            .RegisterMany<ApplicationConfigurator>();
    }
    
    #endregion
    
}