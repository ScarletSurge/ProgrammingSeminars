using System.Globalization;
using System.Windows.Data;
using System.Windows.Markup;

namespace RGU.DistributedSystems.WPF.MVVM;

// covariance
// contravariance
// invariance

/// <summary>
/// 
/// </summary>
public abstract class MultiValueConverterBase<TMultiValueConverter>:
    MarkupExtension,
    IMultiValueConverter
        where TMultiValueConverter: new()
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private static readonly Lazy<TMultiValueConverter> _instance;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    static MultiValueConverterBase()
    {
        _instance = new Lazy<TMultiValueConverter>(() => new TMultiValueConverter());
    }

    #endregion
    
    #region System.Windows.Markup.MarkupExtension overrides
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="serviceProvider"></param>
    /// <returns></returns>
    public override object ProvideValue(
        IServiceProvider serviceProvider)
    {
        return _instance.Value;
    }

    #endregion
    
    #region System.Windows.Data.IMultiValueConverter implementation
    
    /// <inheritdoc cref="IMultiValueConverter.Convert" />
    public abstract object? Convert(
        object[] values,
        Type targetType,
        object? parameter,
        CultureInfo culture);
    
    /// <inheritdoc cref="IMultiValueConverter.ConvertBack" />
    public virtual object[] ConvertBack(
        object? value,
        Type[] targetTypes,
        object? parameter,
        CultureInfo culture)
    {
        throw new NotSupportedException("Reverse conversion is not supported");
    }
    
    #endregion
    
}