using System.Windows.Input;
using System.Windows.Threading;
using RGU.DistributedSystems.WPF.MVVM;

namespace RGU.DistibutedSystems.Launcher.App.ViewModel;

/// <summary>
/// 
/// </summary>
internal sealed class MainWindowViewModel:
    ViewModelBase
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private int _int = 0;
    
    /// <summary>
    /// 
    /// </summary>
    private int _valueInt = 0;
    
    /// <summary>
    /// 
    /// </summary>
    private string _value = "Ruslan 4to s c# =)";
    
    /// <summary>
    /// 
    /// </summary>
    private DispatcherTimer _timer;
    
    #region Commands
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Lazy<ICommand> _incrementInt;
    
    #endregion

    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="interval"></param>
    public MainWindowViewModel(
        TimeSpan interval)
    {
        _timer = new DispatcherTimer(interval, DispatcherPriority.Normal, (s, e) =>
        {
            //++Int;
        }, Dispatcher.CurrentDispatcher);

        _incrementInt = new Lazy<ICommand>(() => new RelayCommand(_ => IncrementInt(), _ => Int != 2));
    }
    
    #endregion
    
    #region Properties

    public int Int
    {
        get =>
            _int;

        set
        {
            _int = value;
            RaisePropertyChanged(nameof(Int));
        }
    }
    
    /// <summary>
    /// 
    /// </summary>
    public string Value
    {
        get =>
            _value;

        set
        {
            _value = value;
            RaisePropertyChanged(nameof(Value));
        }
    }
    
    #region Command
    
    /// <summary>
    /// 
    /// </summary>
    public ICommand IncrementIntCommand =>
        _incrementInt.Value;
    
    #endregion
    
    #endregion
    
    #region Methods
    
    #region Command
    
    /// <summary>
    /// 
    /// </summary>
    private void IncrementInt()
    {
        ++Int;
    }
    
    #endregion
    
    #endregion

}