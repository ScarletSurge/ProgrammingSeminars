using System.Dynamic;
using System.Windows.Input;
using System.Windows.Threading;
using RGU.DistibutedSystems.Launcher.App.Utils;
using RGU.DistributedSystems.WPF.MVVM.Command;
using RGU.DistributedSystems.WPF.MVVM.Navigation;
using RGU.DistributedSystems.WPF.MVVM.ViewModel;

namespace RGU.DistibutedSystems.Launcher.App.ViewModel.Pages;

/// <summary>
/// 
/// </summary>
internal sealed class HelloWPFPageViewModel:
    PageViewModelBase
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
    /// <param name="navigationManager"></param>
    public HelloWPFPageViewModel(
        NavigationManager navigationManager):
            base(navigationManager)
    {
        _timer = new DispatcherTimer(TimeSpan.FromSeconds(1), DispatcherPriority.Normal, (s, e) =>
        {
            //++Int;
        }, Dispatcher.CurrentDispatcher);

        _incrementInt = new Lazy<ICommand>(() => new RelayCommand(_ => IncrementInt(), _ => Int != 2));
        _zhmakCommand = new Lazy<ICommand>(() => new RelayCommand(_ => Zhmak()));

        ButtonsVisibilityState = 0;
        
        // Arrange
        // Measure
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

    public int ButtonsVisibilityState
    {
        get =>
            _buttonsVisibilityState;
        
        private set
        {
            if (value < 0 || value > 3)
            {
                // TODO: validate
                return;
            }

            _buttonsVisibilityState = value;
            RaisePropertyChanged(nameof(ButtonsVisibilityState));
            LeftButtonVisible = (value & 1) == 1;
            RightButtonVisible = ((value >> 1) & 1) == 1;
        }
    }
    
    /// <summary>
    /// 
    /// </summary>
    public string? NullValueContent =>
        null;
    
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

        dynamic y = new ExpandoObject();
        y.Prop = 10;
        y.Prop = "123";
        y.Prop = new ExpandoObject();
        y.Method = (Action<int>)delegate(int x) { };
        y.Method(10);
        y.Method(10);
        y.Event = null;
        y.Event += (Action<int>)(i => { });
        y.Event(10);
        
        
        dynamic x = new System.Text.StringBuilder();
        var res = x.Append("123").Append("456").Append("789").ToString();
        Value = res;
        
        NavigationManager.Navigate(NavigationContext.Builder
            .Create()
            .From<HelloWPFPageViewModel>()
            .To<OtherPageViewModel>()
            .WithParameter("123", new object())
            .Build());
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