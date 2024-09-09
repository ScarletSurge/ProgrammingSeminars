using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Microsoft.Extensions.Options;
using RGU.WebProgramming.Grpc;
using RGU.WebProgramming.Server.MyFirstServiceImplementation.Settings;

namespace RGU.WebProgramming.Server.MyFirstServiceImplementation.Services;

/// <summary>
/// 
/// </summary>
public sealed class MyFirstServiceImplementation:
    MyFirstService.MyFirstServiceBase
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private IOptions<MyFirstServiceImplementationSettings> _options;

    /// <summary>
    /// 
    /// </summary>
    private int _value = 0;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="options"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public MyFirstServiceImplementation(
        IOptions<MyFirstServiceImplementationSettings> options)
    {
        _options = options ?? throw new ArgumentNullException(nameof(options));
    }

    #endregion
    
    #region RGU.WebProgramming.Grpc.MyFirstService.MyFirstServiceBase overrides
    
    /// <inheritdoc cref="MyFirstService.MyFirstServiceBase.MyFirstRPC" />
    public override Task<MyFirstModel> MyFirstRPC(
        Empty request,
        ServerCallContext context)
    {
        ++_value;
        return Task.FromResult(new MyFirstModel
        {
            Value = _value
        });
    }

    #endregion
    
}