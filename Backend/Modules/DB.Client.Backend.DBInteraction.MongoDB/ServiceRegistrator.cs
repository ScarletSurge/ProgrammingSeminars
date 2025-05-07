using DryIoc;
using Microsoft.Extensions.Configuration;

using DB.Client.Backend.DBInteraction.MongoDB.Services;
using DB.Client.Backend.DBInteraction.MongoDB.Settings;
using DB.Client.Backend.Host.Core;
using DB.Client.Backend.Host.Core.Extensions;

namespace DB.Client.Backend.DBInteraction.MongoDB;

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
        registrator.Configure<MongoDBProviderSettings>(configuration.GetSection(nameof(MongoDBProviderSettings)));
        registrator.Register<MongoDBProvider>(Reuse.Singleton);
    }
    
    #endregion
    
}