using Google.Protobuf.WellKnownTypes;
using Grpc.Core;

using RGU.WebProgramming.Grpc;

namespace RGU.WebProgramming.Server.Services;

/// <summary>
/// 
/// </summary>
public class MyFirstServiceImpl:
    MyFirstService.MyFirstServiceBase
{
    
    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private int _value = 0;
    
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