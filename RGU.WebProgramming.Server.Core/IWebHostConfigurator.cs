using Microsoft.AspNetCore.Hosting;

namespace RGU.WebProgramming.Server.Core;

/// <summary>
/// 
/// </summary>
public interface IWebHostConfigurator
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="webHostBuilder"></param>
    void Configure(
        IWebHostBuilder webHostBuilder);
    
}