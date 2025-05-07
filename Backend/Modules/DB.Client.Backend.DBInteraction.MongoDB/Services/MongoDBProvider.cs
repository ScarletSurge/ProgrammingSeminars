using System;
using Microsoft.Extensions.Options;
using MongoDB.Driver;

using DB.Client.Backend.DBInteraction.MongoDB.Settings;
using MongoDB.Bson;

namespace DB.Client.Backend.DBInteraction.MongoDB.Services;

/// <summary>
/// 
/// </summary>
public sealed class MongoDBProvider:
    IDisposable
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly MongoClient _client;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly IOptions<MongoDBProviderSettings> _options;

    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="options"></param>
    public MongoDBProvider(
        IOptions<MongoDBProviderSettings> options)
    {
        _options = options ?? throw new ArgumentNullException(nameof(options));
        _client = new MongoClient(_options.Value.ConnectionString);
    }
    
    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="cancellationToken"></param>
    public async Task ExampleRequestAsync(
        CancellationToken cancellationToken = default)
    {
        IMongoDatabase db = _client.GetDatabase("databaseName"); // creates if not exists
        await _client.DropDatabaseAsync("databaseName", cancellationToken);

        db = _client.GetDatabase("databaseName");
        await db.CreateCollectionAsync("collectionName", cancellationToken: cancellationToken);
        IMongoCollection<BsonArray> collection = db.GetCollection<BsonArray>("collectionName"); // T is BSON
        // TODO: 
    }
    
    #endregion
    
    #region System.IDisposable implementation
    
    /// <inheritdoc cref="IDisposable.Dispose" />
    public void Dispose()
    {
        _client.Dispose();

        GC.SuppressFinalize(this);
    }
    
    /// <summary>
    /// 
    /// </summary>
    ~MongoDBProvider()
    {
        _client.Dispose();
    }
    
    #endregion

}