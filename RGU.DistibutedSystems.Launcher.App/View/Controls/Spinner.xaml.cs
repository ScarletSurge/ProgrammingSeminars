using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using RGU.DistributedSystems.WPF.MVVM.ViewModel;

namespace RGU.DistibutedSystems.Launcher.App.View.Controls;

/// <summary>
/// 
/// </summary>
public partial class Spinner:
    UserControl
{
    
    #region Nested

    public sealed class SpinnerItemViewModel:
        ViewModelBase
    {
        
        #region Fields
        
        /// <summary>
        /// 
        /// </summary>
        private double _radius;
        
        /// <summary>
        /// 
        /// </summary>
        private double _phiInDegrees;

        #endregion
        
        #region Properties
        
        /// <summary>
        /// 
        /// </summary>
        public double Radius
        {
            get =>
                _radius;

            set
            {
                _radius = value;
                RaisePropertiesChanged(nameof(Radius));
            }
        }
        
        /// <summary>
        /// 
        /// </summary>
        public double Phi
        {
            get =>
                _phiInDegrees;

            set
            {
                _phiInDegrees = value;
                RaisePropertyChanged(nameof(Phi));
            }
        }
        
        #endregion

    }
    
    #endregion
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private SpinnerItemViewModel[] _items;
    
    #endregion

    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    public Spinner()
    {
        InitializeComponent();
    }
    
    #endregion
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
    public SpinnerItemViewModel[] Items =>
        _items;
    
    #endregion
    
    #region Dependency properties
    
    /// <summary>
    /// 
    /// </summary>
    public int ItemsCount
    {
        get =>
            (int)GetValue(ItemsCountProperty);
        
        set =>
            SetValue(ItemsCountProperty, value);
    }
    
    /// <summary>
    /// 
    /// </summary>
    public static readonly DependencyProperty ItemsCountProperty = DependencyProperty.Register(nameof(ItemsCount), typeof(int), typeof(Spinner));

    public Brush ItemsBrush
    {
        get =>
            (Brush)GetValue(ItemsBrushProperty);

        set =>
            SetValue(ItemsBrushProperty, value);
    }
    
    /// <summary>
    /// 
    /// </summary>
    public static readonly DependencyProperty ItemsBrushProperty = DependencyProperty.Register(nameof(ItemsBrush), typeof(Brush), typeof(Spinner));
    
    #endregion
    
}