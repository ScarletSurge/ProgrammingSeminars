using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Markup;

namespace DACS.WPF.MVVM.Converter
{

    public abstract class ConverterBase<TConverter> : MarkupExtension, IValueConverter
        where TConverter: class, new()
    {

        private static TConverter _valueToProvide;

        public abstract object Convert(object value, Type targetType, object parameter, CultureInfo culture);

        public virtual object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return _valueToProvide ??= new TConverter();
        }
        
    }

}