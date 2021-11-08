using System;
using System.Globalization;
using System.Windows.Media;

using DACS.WPF.MVVM.Converter;

namespace DACS.HelloWorld.Converters
{
    
    internal sealed class NullableBoolToBrushConverter : ConverterBase<NullableBoolToBrushConverter>
    {
        
        #region ConverterBase overrides
        
        public override object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is bool @bool))
            {
                throw new ArgumentException("value is not of type System.Bool", nameof(value));
            }

            return @bool
                ? Brushes.Green
                : Brushes.Red;
        }
        
        #endregion
        
    }
    
}