using System.Windows;
using System.Windows.Controls;

namespace DACS.WPF.DependencyProperties.Views.Attached
{
    
    public class ButtonAttachedProperties : Button
    {

        public static readonly DependencyProperty SecondContentProperty = DependencyProperty.RegisterAttached(
            "SecondContent", typeof(object), typeof(ButtonAttachedProperties));

        public static object GetSecondContent(DependencyObject obj)
        {
            return obj.GetValue(SecondContentProperty);
        }
        
        public static void SetSecondContent(DependencyObject obj, object value)
        {
            obj.SetValue(SecondContentProperty, value);
        }

    }
    
}