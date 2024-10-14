using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using RGU.WebProgramming.Domain.Converters;
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
    private readonly IOptions<MyFirstServiceImplementationSettings> _options;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly ILogger<MyFirstServiceImplementation>? _logger;

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
    /// <param name="logger"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public MyFirstServiceImplementation(
        IOptions<MyFirstServiceImplementationSettings> options,
        ILogger<MyFirstServiceImplementation>? logger)
    {
        _options = options ?? throw new ArgumentNullException(nameof(options));
        _logger = logger;
    }

    #endregion
    
    #region RGU.WebProgramming.Grpc.MyFirstService.MyFirstServiceBase overrides
    
    /// <inheritdoc cref="MyFirstService.MyFirstServiceBase.MyFirstRPC" />
    public override Task<MyFirstModel> MyFirstRPC(
        Empty request,
        ServerCallContext context)
    {
        _logger?.LogDebug($"{nameof(MyFirstRPC)} request execution started");
        
        try
        {
            ++_value;
            
            var responseTask = Task.FromResult(new Domain.Models.MyFirstModel
            {
                Value = _value
            }.Convert());
            
            _logger?.LogDebug($"{nameof(MyFirstRPC)} request execution succeeded.");

            return responseTask;
        }
        catch (Exception ex)
        {
            _logger?.LogError($"Failed to execute {nameof(MyFirstRPC)} request");
            
            return Task.FromResult(new MyFirstModel
            {
                Value = 0
            });
        }
    }

    #endregion
    
}