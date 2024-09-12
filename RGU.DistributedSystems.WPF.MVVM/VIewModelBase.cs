using System.ComponentModel;

namespace RGU.DistributedSystems.WPF.MVVM;

/// <summary>
/// 
/// </summary>
public abstract class ViewModelBase:
    INotifyPropertyChanged
{

    public void Foo()
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("1234"));
    }
    
    #region System.ComponentModel.INotifyPropertyChanged implementation
    
    /// <inheritdoc cref="INotifyPropertyChanged.PropertyChanged" />
    public event PropertyChangedEventHandler? PropertyChanged;
    
    #endregion
    
}