using DryIoc;
using Microsoft.Extensions.Configuration;

using DB.Client.Backend.DBInteraction.Redis.Settings;
using DB.Client.Backend.Host.Core;
using DB.Client.Backend.Host.Core.Extensions;

namespace DB.Client.Backend.DBInteraction.Redis;

/// <summary>
/// 
/// </summary>
public sealed class ServiceRegistrator:
    IServiceRegistrator
{
    
    #region DB.Client.Backend.Host.Core.IServiceRegistrator implementation
    
    /// <inheritdoc cref="IServiceRegistrator.Register" />
    public void Register(
        IRegistrator registrator,
        IConfiguration configuration)
    {
        registrator.Configure<RedisProviderSettings>(configuration.GetSection(nameof(RedisProviderSettings)));
        registrator.Register<RedisProvider>(Reuse.Singleton);
    }
    
    #endregion
    
}