using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

using RGU.WebProgramming.Server.Core;

namespace RGU.WebProgramming.Server.Grpc;

/// <summary>
/// 
/// </summary>
public sealed class ApplicationConfigurator:
    IApplicationConfigurator,
    IStartup
{
    
    #region RGU.WebProgramming.Server.Core.IApplicationConfigurator implementation

    /// <inheritdoc cref="IApplicationConfigurator.Configure" />
    public void Configure(
        IApplicationBuilder applicationBuilder)
    {
        var endpointsConfigurators = applicationBuilder.ApplicationServices.GetServices<IEndpointsConfigurator>();

        applicationBuilder
            .UseRouting()
            .UseAuthentication()
            .UseAuthorization()
            .UseEndpoints(routeBuilder =>
            {
                foreach (var endpointsConfigurator in endpointsConfigurators)
                {
                    endpointsConfigurator.Configure(routeBuilder);
                }
            });
    }
    
    #endregion
    
    #region RGU.WebProgramming.Server.Core.IStartup implementation

    /// <inheritdoc cref="Core.IStartup.ConfigureServices(HostBuilderContext, IServiceCollection)" />
    public void ConfigureServices(
        HostBuilderContext ctx,
        IServiceCollection services)
    {
        services.AddAuthentication();
        services.AddAuthorization();
        services.AddGrpc();
    }

    #endregion
    
}