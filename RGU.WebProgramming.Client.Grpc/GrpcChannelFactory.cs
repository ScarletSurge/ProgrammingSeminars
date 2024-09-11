using Grpc.Core;
using Microsoft.Extensions.Options;

using RGU.WebProgramming.Client.Grpc.Settings;
using RGU.WebProgramming.Core.Interfaces;

namespace RGU.WebProgramming.Client.Grpc;

/// <summary>
/// 
/// </summary>
public sealed class GrpcChannelFactory:
    IAbstractFactory<Channel>
{
    
    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private readonly IOptions<GrpcClientSettings> _options;

    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="options"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public GrpcChannelFactory(
        IOptions<GrpcClientSettings> options)
    {
        _options = options ?? throw new ArgumentNullException(nameof(options));
    }
    
    #endregion
    
    #region RGU.WebProgramming.Core.Interfaces.IAbstractFactory<out Channel> implementation
    
    /// <inheritdoc cref="IAbstractFactory{T}.Create" />
    public Channel Create()
    {
        return new Channel(_options.Value.TargetAddress, ChannelCredentials.Insecure);
    }
    
    #endregion
    
}