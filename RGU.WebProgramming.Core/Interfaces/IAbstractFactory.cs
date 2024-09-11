namespace RGU.WebProgramming.Core.Interfaces;

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
public interface IAbstractFactory<out T>
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    T Create();

}