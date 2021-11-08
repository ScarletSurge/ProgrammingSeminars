using System;
using System.Globalization;
using System.Windows;

using ThirdCourse.WPF.MVVM.Converters.Base;

namespace ThirdCourse.WPF.MVVM.Converters
{

    public sealed class BoolToInvertedVisibilityConverter : ConverterBase
    {

        public override object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is bool @bool))
            {
                throw new ArgumentException(string.Empty, nameof(value));
            }
            return @bool ? Visibility.Collapsed : Visibility.Visible;
        }

    }

}