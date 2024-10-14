namespace RGU.WebProgramming.Domain.Converters;

/// <summary>
/// 
/// </summary>
public static class ConverterExtensions
{
    
    #region MyFirstModel
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="domainMyFirstModel"></param>
    /// <returns></returns>
    public static RGU.WebProgramming.Grpc.MyFirstModel Convert(
        this RGU.WebProgramming.Domain.Models.MyFirstModel domainMyFirstModel)
    {
        ArgumentNullException.ThrowIfNull(domainMyFirstModel, nameof(domainMyFirstModel));
        
        return new RGU.WebProgramming.Grpc.MyFirstModel
        {
            Value = domainMyFirstModel.Value,
            Abrakadabra = domainMyFirstModel.Abrakadabra
        };
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="protobufMyFirstModel"></param>
    /// <returns></returns>
    public static RGU.WebProgramming.Domain.Models.MyFirstModel ConvertBack(
        this RGU.WebProgramming.Grpc.MyFirstModel protobufMyFirstModel)
    {
        ArgumentNullException.ThrowIfNull(protobufMyFirstModel, nameof(protobufMyFirstModel));
        
        return new RGU.WebProgramming.Domain.Models.MyFirstModel
        {
            Value = protobufMyFirstModel.Value,
            Abrakadabra = protobufMyFirstModel.Abrakadabra
        };
    }
    
    #endregion
    
}