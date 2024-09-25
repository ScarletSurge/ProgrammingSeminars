using System.Globalization;
using System.Windows.Data;

namespace RGU.DistributedSystems.WPF.MVVM;

public sealed class FromBoolConverter:
    IMultiValueConverter
{
    public object? Convert(object?[] values, Type targetType, object parameter, CultureInfo culture)
    {
        if (values.Length != 3)
        {
            throw new ArgumentException("Invalid count of values!");
        }
        
        return (bool)values[0]
            ? values[1]
            : values[2];
    }

    public object?[] ConvertBack(object? value, Type[] targetType, object parameter, CultureInfo culture)
    {
        throw new NotSupportedException();
    }
    
}