using Microsoft.Extensions.Options;
using StackExchange.Redis;

using DB.Client.Backend.DBInteraction.Redis.Settings;
using DB.Client.Domain;

namespace DB.Client.Backend.DBInteraction.Redis;

// RedisConnectionFactory
// IServer
// Redis arch
// Redis keys
// StackExchange.Redis Exceptions

/// <summary>
/// 
/// </summary>
public sealed class RedisProvider
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly IOptions<RedisProviderSettings> _options;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="options"></param>
    public RedisProvider(
        IOptions<RedisProviderSettings> options)
    {
        _options = options ?? throw new ArgumentNullException(nameof(options));
    }
    
    #endregion
    
    #region Methods
    
    // T obj; // class T  { public IEnumerator GetEnumerator() {  } }
    // foreach (var item in obj)
    // {
    //     
    // }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="toStore"></param>
    /// <param name="cancellationToken"></param>
    public async Task FooAsync(
        string key,
        Product toStore,
        CancellationToken cancellationToken = default)
    {
        await using var redisConnection =
            await ConnectionMultiplexer.ConnectAsync($"{_options.Value.Address}:{_options.Value.Port}");

        var db = redisConnection.GetDatabase(0);
        
        await using var stream = toStore.Serialize();
        var objectBinaryState = stream.GetBuffer().ToHexString();
        await db.StringGetSetAsync(new RedisKey(key), new RedisValue(objectBinaryState));
    }
    
    #endregion

}