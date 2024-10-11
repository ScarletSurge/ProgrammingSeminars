using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Windows.Input;
using RGU.DistibutedSystems.Launcher.App.Utils;
using RGU.DistributedSystems.WPF.MVVM.Command;
using RGU.DistributedSystems.WPF.MVVM.Navigation;
using RGU.DistributedSystems.WPF.MVVM.ViewModel;

namespace RGU.DistibutedSystems.Launcher.App.ViewModel.Pages;

/// <summary>
/// 
/// </summary>
internal sealed class TargetToNavigatePageViewModel:
    PageViewModelBase
{
    
    #region Nested
    
    /// <summary>
    /// 
    /// </summary>
    public sealed class StringWrapperViewModel:
        ViewModelBase
    {

        private string _value;

        public StringWrapperViewModel(
            string value)
        {
            Value = value;
        }

        public string Value
        {
            get =>
                _value;

            private set
            {
                _value = value;
                RaisePropertyChanged(nameof(Value));
            }
        }
        
    }

    public sealed class ModifiableIntViewModel:
        ViewModelBase
    {

        private int _value;
        private readonly Lazy<ICommand> _incrementCommand;
        private readonly Lazy<ICommand> _decrementCommand;

        public ModifiableIntViewModel()
        {
            Value = 0;
            _incrementCommand = new Lazy<ICommand>(() => new RelayCommand(_ => Increment()));
            _decrementCommand = new Lazy<ICommand>(() => new RelayCommand(_ => Decrement()));
        }
        
        public int Value
        {
            get =>
                _value;

            private set
            {
                _value = value;
                RaisePropertyChanged(nameof(Value));
            }
        }

        public ICommand IncrementCommand =>
            _incrementCommand.Value;

        public ICommand DecrementCommand =>
            _decrementCommand.Value;

        private void Increment()
        {
            ++Value;
        }

        private void Decrement()
        {
            --Value;
        }

    }
    
    #endregion
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Lazy<ICommand> _navigateBackCommand;

    private readonly Lazy<ICommand> _addStringWrapperCommand;
    
    private readonly Lazy<ICommand> _addModifiableIntCommand;

    private ObservableCollection<ViewModelBase> _valuesToDisplay;

    private ObservableCollection<string> _strings;
    
    private ObservableCollection<StringWrapperViewModel> _stringsWrappers;

    private int _valueToAdd;
    
    #endregion

    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="navigationManager"></param>
    public TargetToNavigatePageViewModel(
        NavigationManager navigationManager):
            base(navigationManager)
    {
        _valueToAdd = 0;
        
        _navigateBackCommand = new Lazy<ICommand>(() => new RelayCommand(_ => NavigateBack()));

        _addStringWrapperCommand = new Lazy<ICommand>(() => new RelayCommand(_ => AddStringWrapper()));
        
        _addModifiableIntCommand = new Lazy<ICommand>(() => new RelayCommand(_ => AddModifiableInt()));

        ValuesToDisplay = new ObservableCollection<ViewModelBase>();
        
        Strings = new ObservableCollection<string> { "16", "126", "1236", "12346", "123456" };
        
        StringsWrappers = new ObservableCollection<StringWrapperViewModel> { new StringWrapperViewModel("1"), new StringWrapperViewModel("12"), new StringWrapperViewModel("123"), new StringWrapperViewModel("1234"), new StringWrapperViewModel("12345") };
    }
    
    #endregion
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
    public ICommand NavigateBackCommand =>
        _navigateBackCommand.Value;
    
    /// <summary>
    /// 
    /// </summary>
    public ICommand AddStringWrapperCommand =>
        _addStringWrapperCommand.Value;
    
    /// <summary>
    /// 
    /// </summary>
    public ICommand AddModifiableIntCommand =>
        _addModifiableIntCommand.Value;

    /// <summary>
    /// 
    /// </summary>
    public ObservableCollection<StringWrapperViewModel> StringsWrappers
    {
        get =>
            _stringsWrappers;

        private set
        {
            _stringsWrappers = value;
            RaisePropertyChanged(nameof(StringsWrappers));
        }
    }

    public ObservableCollection<string> Strings
    {
        get =>
            _strings;

        private set
        {
            _strings = value;
            RaisePropertyChanged(nameof(Strings));
        }
    }

    public ObservableCollection<ViewModelBase> ValuesToDisplay
    {
        get =>
            _valuesToDisplay;

        set
        {
            _valuesToDisplay = value;
            RaisePropertyChanged(nameof(ValuesToDisplay));
        }
    }

    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    private void NavigateBack()
    {
        NavigationManager.Navigate(NavigationContext.Builder
            .Create()
            .From<TargetToNavigatePageViewModel>()
            .To<HelloWPFPageViewModel>()
            .Build());
    }
    
    /// <summary>
    /// 
    /// </summary>
    private void AddStringWrapper()
    {
        ++_valueToAdd;
        ValuesToDisplay.Add(new StringWrapperViewModel(_valueToAdd.ToString()));
    }
    
    /// <summary>
    /// 
    /// </summary>
    private void AddModifiableInt()
    {
        ValuesToDisplay.Add(new ModifiableIntViewModel());
    }
    
    #endregion

}