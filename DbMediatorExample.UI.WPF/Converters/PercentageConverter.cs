using System;
using System.Globalization;

namespace DbMediatorExample.UI.WPF.Converters
{

    public sealed class PercentageConverter : BaseConverter
    {

        public override object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            double valueToConvert = (double)value;
            double multiplier = (double)parameter;
            return valueToConvert * multiplier;
        }

        public override object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            double valueToConvert = (double)value;
            double divisor = (double)parameter;
            return valueToConvert / divisor;
        }

    }

}