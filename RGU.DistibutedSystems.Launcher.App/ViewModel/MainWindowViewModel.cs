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
    
    /// <summary>
    /// 
    /// </summary>
    private bool _leftButtonVisible;
    
    /// <summary>
    /// 
    /// </summary>
    private bool _rightButtonVisible;
    
    /// <summary>
    /// 
    /// </summary>
    private int _buttonsVisibilityState;
    
    #region Commands
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Lazy<ICommand> _incrementInt;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Lazy<ICommand> _zhmakCommand;

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
        _zhmakCommand = new Lazy<ICommand>(() => new RelayCommand(_ => Zhmak()));
    }
    
    #endregion
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
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
    
    /// <summary>
    /// 
    /// </summary>
    public bool LeftButtonVisible
    {
        get =>
            _leftButtonVisible;

        private set
        {
            _leftButtonVisible = value;
            RaisePropertyChanged(nameof(LeftButtonVisible));
        }
    }
    
    /// <summary>
    /// 
    /// </summary>
    public bool RightButtonVisible
    {
        get =>
            _rightButtonVisible;

        private set
        {
            _rightButtonVisible = value;
            RaisePropertyChanged(nameof(RightButtonVisible));
        }
    }

    private int ButtonsVisibilityState
    {
        get =>
            _buttonsVisibilityState;
        
        set
        {
            if (value < 0 || value > 3)
            {
                // TODO: validate
                return;
            }

            _buttonsVisibilityState = value;
            LeftButtonVisible = (value & 1) == 1;
            RightButtonVisible = ((value >> 1) & 1) == 1;
        }
    }
    
    #region Command
    
    /// <summary>
    /// 
    /// </summary>
    public ICommand IncrementIntCommand =>
        _incrementInt.Value;
    
    /// <summary>
    /// 
    /// </summary>
    public ICommand ZhmakCommand =>
        _zhmakCommand.Value;
    
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
    
    /// <summary>
    /// 
    /// </summary>
    private void Zhmak()
    {
        ButtonsVisibilityState = (ButtonsVisibilityState + 1) % 4;
    }
    
    #endregion
    
    #endregion

}