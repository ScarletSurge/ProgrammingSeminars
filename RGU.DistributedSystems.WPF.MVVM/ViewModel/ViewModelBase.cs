using System.ComponentModel;

namespace RGU.DistributedSystems.WPF.MVVM.ViewModel;

/// <summary>
/// 
/// </summary>
public abstract class ViewModelBase:
    INotifyPropertyChanged
{
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="propertyName"></param>
    protected void RaisePropertyChanged(
        string propertyName)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="propertiesNames"></param>
    protected void RaisePropertiesChanged(
        params string[]? propertiesNames)
    {
        foreach (var propertyName in propertiesNames ?? Enumerable.Empty<string>())
        {
            RaisePropertyChanged(propertyName);
        }
    }
    
    #endregion
    
    #region System.ComponentModel.INotifyPropertyChanged implementation
    
    /// <inheritdoc cref="INotifyPropertyChanged.PropertyChanged" />
    public event PropertyChangedEventHandler? PropertyChanged;
    
    #endregion
    
}