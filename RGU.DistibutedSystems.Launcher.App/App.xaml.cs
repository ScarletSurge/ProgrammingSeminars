using System.Windows;
using DryIoc;
using RGU.DistibutedSystems.Launcher.App.Utils;
using RGU.DistibutedSystems.Launcher.App.View;
using RGU.DistibutedSystems.Launcher.App.View.Pages;
using RGU.DistibutedSystems.Launcher.App.ViewModel;
using RGU.DistibutedSystems.Launcher.App.ViewModel.Pages;

namespace RGU.DistibutedSystems.Launcher.App;

/// <summary>
/// Interaction logic for App.xaml
/// </summary>
public partial class App:
    Application
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private static readonly Lazy<IContainer> _container;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    static App()
    {
        _container = new Lazy<IContainer>(() => new Container());
    }
    
    #endregion
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
    public static IContainer Container =>
        _container.Value;
    
    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterLogging()
    {
        // TODO
        
        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterConfiguration()
    {
        // TODO
        
        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterWindowsViews()
    {
        Container.Register<MainWindow>(Reuse.Singleton);
        
        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterPagesViews()
    {
        Container.Register<HelloWPFPage>(Reuse.Singleton);

        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterDialogsViews()
    {
        // TODO: 

        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterViews()
    {
        return RegisterWindowsViews()
            .RegisterPagesViews()
            .RegisterDialogsViews();
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterWindowsViewModels()
    {
        Container.Register<MainWindowViewModel>(Reuse.Singleton);
        
        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterPagesViewModels()
    {
        Container.Register<HelloWPFPageViewModel>(Reuse.Singleton);

        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterDialogsViewModels()
    {
        // TODO: 

        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterViewModels()
    {
        return RegisterWindowsViewModels()
            .RegisterPagesViewModels()
            .RegisterDialogsViewModels();
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private App RegisterNavigation()
    {
        var navigationManager = new NavigationManager();
        Container.RegisterInstance(navigationManager);
        
        navigationManager
            .AddMapping<HelloWPFPage, HelloWPFPageViewModel>();

        return this;
    }
    
    #endregion
    
    #region System.Windows.Application overrides
    
    /// <inheritdoc cref="Application.OnStartup" />
    protected override void OnStartup(
        StartupEventArgs e)
    {
        this.RegisterLogging()
            .RegisterConfiguration()
            .RegisterViews()
            .RegisterViewModels()
            .RegisterNavigation();

        Container.Resolve<MainWindow>().Show();
    }
    
    #endregion
    
}