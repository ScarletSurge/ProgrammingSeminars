using System.Globalization;

namespace RGU.DistributedSystems.WPF.MVVM;

public sealed class FromBoolConverter:
    MultiValueConverterBase<FromBoolConverter>
{
    
    #region RGU.DistributedSystems.WPF.MVVM.MultiValueConverterBase<FromBoolConverter> overrides
    
    /// <inheritdoc cref="MultiValueConverterBase{TMultiValueConverter}.Convert" />
    public override object? Convert(
        object?[] values,
        Type targetType,
        object? parameter,
        CultureInfo culture)
    {
        if (values.Length != 3)
        {
            throw new ArgumentException("Invalid count of values!");
        }
        
        return (bool)values[0]
            ? values[1]
            : values[2];
    }
    
    #endregion
    
}