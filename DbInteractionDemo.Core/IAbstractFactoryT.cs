namespace DbInteractionDemo.Core;

/// <summary>
/// 
/// </summary>
public interface IAbstractFactory<T>
{

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    T Create();

}