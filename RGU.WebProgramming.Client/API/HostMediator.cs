using Google.Protobuf.WellKnownTypes;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

using RGU.WebProgramming.Client.Grpc;
using RGU.WebProgramming.Domain.Converters;
using RGU.WebProgramming.Grpc;

namespace RGU.WebProgramming.Client.API;

/// <summary>
/// 
/// </summary>
internal sealed class HostMediator
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly GrpcChannelFactory _grpcChannelFactory;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly IOptions<HostMediatorSettings> _options;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly ILogger<HostMediator>? _logger;

    #endregion
    
    #region Constructor
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="grpcChannelFactory"></param>
    /// <param name="options"></param>
    /// <param name="logger"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public HostMediator(
        GrpcChannelFactory grpcChannelFactory,
        IOptions<HostMediatorSettings> options,
        ILogger<HostMediator>? logger)
    {
        _grpcChannelFactory = grpcChannelFactory ?? throw new ArgumentNullException(nameof(grpcChannelFactory));
        _options = options ?? throw new ArgumentNullException(nameof(options));
        _logger = logger;
    }
    
    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private MyFirstService.MyFirstServiceClient CreateClient()
    {
        return new MyFirstService.MyFirstServiceClient(_grpcChannelFactory.Create());
    }
    
    #endregion
    
    #region API
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="cancellationToken"></param>
    /// <returns></returns>
    public async Task<Domain.Models.MyFirstModel> MyFirstRPCAsync(
        CancellationToken cancellationToken = default)
    {
        try
        {
            return (await CreateClient().MyFirstRPCAsync(new Empty(), cancellationToken: cancellationToken).ConfigureAwait(false)).ConvertBack();
        }
        catch (Exception ex)
        {
            // TODO: handle exception
            return new Domain.Models.MyFirstModel();
        }
    }
    
    #endregion

}