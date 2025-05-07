using DB.Client.Backend.DBInteraction.Redis;
using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

using DB.Client.Backend.Entrypoint.Grpc.Settings;
using DB.Client.Domain.Converters;
using DB.Client.Domain.Infrastructure;
using DB.Client.Grpc;

namespace DB.Client.Backend.Entrypoint.Grpc.Services;

/// <summary>
/// 
/// </summary>
public sealed class GrpcServiceSample:
    ProductService.ProductServiceBase
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly IOptions<GrpcServiceSampleSettings> _options;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly ILogger<GrpcServiceSample>? _logger;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly IRepository<Domain.Product> _productsRepository;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly RedisProvider _hotProductsRepository;
    
    #endregion

    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="options"></param>
    /// <param name="logger"></param>
    /// <param name="hotProductsRepository"></param>
    /// <param name="productsRepository"></param>
    /// <exception cref="ArgumentNullException"></exception>
    /// <exception cref="ArgumentException"></exception>
    public GrpcServiceSample(
        IOptions<GrpcServiceSampleSettings> options,
        ILogger<GrpcServiceSample>? logger,
        RedisProvider hotProductsRepository,
        IRepository<Domain.Product> productsRepository)
    {
        _options = options ?? throw new ArgumentNullException(nameof(options));
        _logger = logger;
        _hotProductsRepository = hotProductsRepository ?? throw new ArgumentNullException(nameof(hotProductsRepository));
        _productsRepository = productsRepository ?? throw new ArgumentException(nameof(productsRepository));
    }

    #endregion
    
    #region DB.Client.Grpc.ProductService.ProductServiceBase overrides
    
    /// <inheritdoc cref="ProductService.ProductServiceBase.GetProducts" />
    public override async Task<Products> GetProducts(
        Empty request,
        ServerCallContext context)
    {
        try
        {
            var result = new Products();
            var hotResult = new Domain.Product();
            await _hotProductsRepository.FooAsync("key", hotResult, context.CancellationToken).ConfigureAwait(false);
            result.Products_.AddRange((await _productsRepository.SelectEntitiesAsync(context.CancellationToken)).Select(ConverterExtensions.Convert));
            return result;
        }
        catch (Exception ex)
        {
            _logger?.LogError("something went wrong...");
            return new Products();
        }
    }

    #endregion
    
}