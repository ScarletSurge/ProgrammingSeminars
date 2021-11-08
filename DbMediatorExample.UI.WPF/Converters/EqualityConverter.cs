using System;
using System.Globalization;
using System.Windows.Data;

namespace DbMediatorExample.UI.WPF.Converters
{

    internal sealed class EqualityConverter<T> : IMultiValueConverter
    {

        private readonly T _trueValue;
        private readonly T _falseValue;

        public EqualityConverter(T trueValue, T falseValue)
        {
            _trueValue = trueValue;
            _falseValue = falseValue;
        }

        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (values[1] is string && string.IsNullOrEmpty(values[1] as string))
            {
                return _trueValue;
            }
            return values[0].Equals(values[1]) ? _trueValue : _falseValue;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

}