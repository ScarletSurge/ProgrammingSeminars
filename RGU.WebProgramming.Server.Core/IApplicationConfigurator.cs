using Microsoft.AspNetCore.Builder;

namespace RGU.WebProgramming.Server.Core;

/// <summary>
/// 
/// </summary>
public interface IApplicationConfigurator
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="applicationBuilder"></param>
    void Configure(
        IApplicationBuilder applicationBuilder);
    
}