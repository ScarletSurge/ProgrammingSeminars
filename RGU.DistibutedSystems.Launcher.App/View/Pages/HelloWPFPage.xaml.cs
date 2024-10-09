using DryIoc;
using System.Windows;
using System.Windows.Controls;

using RGU.DistibutedSystems.Launcher.App.ViewModel.Pages;

namespace RGU.DistibutedSystems.Launcher.App.View.Pages;

/// <summary>
/// 
/// </summary>
public partial class HelloWPFPage:
    Page
{
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    public HelloWPFPage()
    {
        InitializeComponent();

        DataContext = App.Container.Resolve<HelloWPFPageViewModel>();
    }
    
    #endregion
    
    #region Event handlers
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void ButtonBase1_OnClick(
        object sender,
        RoutedEventArgs e)
    {
        Application.Current.Shutdown();
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void ButtonBase2_OnClick(
        object sender,
        RoutedEventArgs e)
    {
        MessageBox.Show("Hello!");
    }
    
    #endregion
    
}