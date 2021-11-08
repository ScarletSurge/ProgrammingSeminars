using System;
using System.Globalization;

using ThirdCourse.WPF.MVVM.Converters.Base;
using ThirdCourse.WPF.Spinner.Data;

namespace ThirdCourse.WPF.Spinner.Converters
{

    internal sealed class BoolToRotationDirectionConverter : ConverterBase
    {

        public override object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is bool @bool))
            {
                throw new ArgumentException(nameof(value));
            }
            return @bool ? RotationDirection.Clockwise : RotationDirection.Counterclockwise;
        }

    }

}