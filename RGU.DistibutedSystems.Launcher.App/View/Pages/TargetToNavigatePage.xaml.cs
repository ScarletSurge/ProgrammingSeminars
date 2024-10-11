using DryIoc;
using System.Windows.Controls;

using RGU.DistibutedSystems.Launcher.App.ViewModel.Pages;

namespace RGU.DistibutedSystems.Launcher.App.View.Pages;

/// <summary>
/// 
/// </summary>
public partial class TargetToNavigatePage:
    Page
{
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    public TargetToNavigatePage()
    {
        InitializeComponent();
        
        DataContext = App.Container.Resolve<TargetToNavigatePageViewModel>();
    }
    
    #endregion
    
}