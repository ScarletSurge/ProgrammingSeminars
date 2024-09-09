using Microsoft.Extensions.Hosting;

namespace RGU.WebProgramming.Server.Deployment;

/// <summary>
/// 
/// </summary>
internal sealed class App
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly IHost _host;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="host"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public App(
        IHost host)
    {
        _host = host ?? throw new ArgumentNullException(nameof(host));
    }
    
    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    public void Start()
    {
        _host.Run();
    }
    
    #endregion
    
}