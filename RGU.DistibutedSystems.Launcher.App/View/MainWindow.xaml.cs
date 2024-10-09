using DryIoc;
using System.Windows;
using RGU.DistibutedSystems.Launcher.App.Utils;
using RGU.DistibutedSystems.Launcher.App.View.Pages;
using RGU.DistibutedSystems.Launcher.App.ViewModel;

namespace RGU.DistibutedSystems.Launcher.App.View;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow:
    Window
{
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    public MainWindow()
    {
        InitializeComponent();
        
        DataContext = App.Container.Resolve<MainWindowViewModel>();
    }
    
    #endregion
    
    #region Event Handlers
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void MainWindow_OnLoaded(
        object sender,
        RoutedEventArgs e)
    {
        App.Container.Resolve<NavigationManager>().NavigationService = _mainWindowMainFrame.NavigationService;
        _mainWindowMainFrame.Navigate(App.Container.Resolve<HelloWPFPage>());
    }
    
    #endregion
    
}