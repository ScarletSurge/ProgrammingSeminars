using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ThirdCourse.WPF.Spinner.Views.Attached
{

    public class ButtonAttachedProperties : Button
    {

        public static readonly DependencyProperty SecondBackgroundProperty = DependencyProperty.RegisterAttached(
            "SecondBackground", typeof(Brush), typeof(ButtonAttachedProperties), new FrameworkPropertyMetadata(Brushes.Red));

        public static Brush GetSecondBackground(DependencyObject obj)
        {
            return (Brush)obj.GetValue(SecondBackgroundProperty);
        }

        public static void SetSecondBackground(DependencyObject obj, Brush value)
        {
            obj.SetValue(SecondBackgroundProperty, value);
        }

    }

}