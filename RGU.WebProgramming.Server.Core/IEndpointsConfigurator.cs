using Microsoft.AspNetCore.Routing;

namespace RGU.WebProgramming.Server.Core;

/// <summary>
/// 
/// </summary>
public interface IEndpointsConfigurator
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="routeBuilder"></param>
    void Configure(
        IEndpointRouteBuilder routeBuilder);
    
}