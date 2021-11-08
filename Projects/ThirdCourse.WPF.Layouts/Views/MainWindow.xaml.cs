using System.Windows;

namespace Wpf120321
{

    public partial class MainWindow : Window
    {

        private string[] _strings;

        public MainWindow()
        {
            InitializeComponent();
            _strings = new string[]
            {
                "First",
                "Second",
                "Third",
                "Fourth"
            };
        }

        public string[] Strings =>
            _strings;

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("MessageBox.Show called...");
        }

    }

}