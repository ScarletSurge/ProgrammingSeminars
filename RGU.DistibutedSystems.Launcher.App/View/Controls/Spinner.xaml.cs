using System.Windows;
using System.Windows.Controls;

namespace RGU.DistibutedSystems.Launcher.App.View.Controls;

/// <summary>
/// 
/// </summary>
public partial class Spinner:
    UserControl
{

    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    public Spinner()
    {
        InitializeComponent();
    }
    
    #endregion
    
    #region Dependency properties
    
    /// <summary>
    /// 
    /// </summary>
    public int PukSrenjk
    {
        get =>
            (int)GetValue(ItemsCountProperty);
        
        set =>
            SetValue(ItemsCountProperty, value);
    }
    
    /// <summary>
    /// 
    /// </summary>
    public static readonly DependencyProperty ItemsCountProperty = DependencyProperty.Register(nameof(PukSrenjk), typeof(int), typeof(Spinner));
    
    #endregion
    
}