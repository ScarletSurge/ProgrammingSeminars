using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Markup;

namespace ThirdCourse.WPF.MVVM.Converters.Base
{

    public abstract class MultiConverterBase : MarkupExtension, IMultiValueConverter
    {

        public abstract object Convert(object[] values, Type targetType, object parameter, CultureInfo culture);

        public virtual object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return this;
        }

    }

}