namespace RGU.DistributedSystems.WPF.MVVM.Navigation;

/// <summary>
/// 
/// </summary>
public interface INavigatable
{

    /// <summary>
    /// 
    /// </summary>
    /// <param name="navigationContext"></param>
    void OnNavigatingFrom(
        NavigationContext navigationContext);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="navigationContext"></param>
    void OnNavigatedFrom(
        NavigationContext navigationContext);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="navigationContext"></param>
    void OnNavigatedTo(
        NavigationContext navigationContext);

}