using System.Windows;
using System.Windows.Controls;

namespace DACS.DependencyProperties.Views.Controls
{
    public partial class OurCustomControl : UserControl
    {
        public OurCustomControl()
        {
            InitializeComponent();
        }
        
        /// <summary>
        /// SomeString documentation
        /// </summary>
        public string SomeString
        {
            get =>
                (string)GetValue(SomeStringProperty);
            
            set =>
                SetValue(SomeStringProperty, value);
        }
        public static readonly DependencyProperty SomeStringProperty = DependencyProperty.Register(
            nameof(SomeString), typeof(string), typeof(OurCustomControl));
    }
}