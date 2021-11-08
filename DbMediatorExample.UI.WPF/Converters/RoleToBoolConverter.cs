using System;
using System.Globalization;
using System.Windows.Data;

using DbMediatorExample.Database.Models.Enums;

namespace DbMediatorExample.UI.WPF.Converters
{

    internal sealed class RoleToBoolConverter : IValueConverter
    {

        private readonly Role _falseValue;
        private readonly Role _trueValue;

        public RoleToBoolConverter(Role falseValue, Role trueValue)
        {
            _falseValue = falseValue;
            _trueValue = trueValue;
        }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is Role role)
            {
                return role == _trueValue ? true : false;
            }
            throw new ArgumentException(nameof(value));
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is bool @bool)
            {
                return @bool ? _trueValue : _falseValue;
            }
            throw new ArgumentException(nameof(value));
        }

    }

}