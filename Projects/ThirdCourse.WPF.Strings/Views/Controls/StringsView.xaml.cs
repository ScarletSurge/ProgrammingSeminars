using System.Windows;
using System.Windows.Controls;

namespace ThirdCourse.WPF.Strings.Views.Controls
{

    public partial class StringsView : UserControl
    {

        public StringsView()
        {
            InitializeComponent();
        }

        public string LeftString
        {
            get =>
                (string)GetValue(LeftStringProperty);

            set =>
                SetValue(LeftStringProperty, value);
        }
        public static readonly DependencyProperty LeftStringProperty = DependencyProperty.Register(
            nameof(LeftString), typeof(string), typeof(StringsView), new PropertyMetadata("default"));

    }

}