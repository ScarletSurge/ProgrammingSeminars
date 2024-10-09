using System.Windows;
using System.Windows.Navigation;
using DryIoc;
using RGU.DistributedSystems.WPF.MVVM.Navigation;
using RGU.DistributedSystems.WPF.MVVM.ViewModel;

namespace RGU.DistibutedSystems.Launcher.App.Utils;

/// <summary>
/// 
/// </summary>
internal sealed class NavigationManager
{

    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private NavigationService? _navigationService;

    /// <summary>
    /// 
    /// </summary>
    private readonly Dictionary<Type, FrameworkElement> _viewTypeToViewMappings;

    /// <summary>
    /// 
    /// </summary>
    private readonly IResolver _resolver;

    #endregion

    #region Constructors

    /// <summary>
    /// 
    /// </summary>
    public NavigationManager()
    {
        _viewTypeToViewMappings = new Dictionary<Type, FrameworkElement>();
        _resolver = App.Container;
    }

    #endregion

    #region Properties

    /// <summary>
    /// 
    /// </summary>
    public NavigationService NavigationService
    {
        set
        {
            if (_navigationService is not null)
            {
                throw new InvalidOperationException("Navigation service already set to the instance of navigation manager");
            }

            _navigationService = value;
        }
    }

    #endregion

    #region Methods

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TView"></typeparam>
    /// <typeparam name="TViewModel"></typeparam>
    public NavigationManager AddMapping<TView, TViewModel>()
        where TView:
            FrameworkElement
        where TViewModel:
            ViewModelBase
    {
        _viewTypeToViewMappings.Add(typeof(TViewModel), (_resolver.Resolve(typeof(TView)) as FrameworkElement)!);

        return this;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="navigationContext"></param>
    /// <returns></returns>
    public void Navigate(
        NavigationContext navigationContext)
    {
        _ = _navigationService ?? throw new InvalidOperationException("Navigation service is not initialized");

        if (!_viewTypeToViewMappings.TryGetValue(navigationContext.To, out var view))
        {
            throw new ArgumentException("View model type is not registered");
        }

        var from = (INavigatable)_resolver.Resolve(navigationContext.From);
        var to = (INavigatable)_resolver.Resolve(navigationContext.To);

        from.OnNavigatingFrom(navigationContext);
        if (navigationContext.Cancelled)
        {
            return;
        }
        _navigationService.Navigate(view);
        from.OnNavigatedFrom(navigationContext);
        to.OnNavigatedTo(navigationContext);
    }

    #endregion

}