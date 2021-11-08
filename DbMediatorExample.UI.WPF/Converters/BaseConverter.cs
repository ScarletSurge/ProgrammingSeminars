using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Markup;

namespace DbMediatorExample.UI.WPF.Converters
{

    public abstract class BaseConverter : MarkupExtension, IValueConverter
    {

        public abstract object Convert(object value, Type targetType, object parameter, CultureInfo culture);

        public virtual object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return this;
        }

    }

}