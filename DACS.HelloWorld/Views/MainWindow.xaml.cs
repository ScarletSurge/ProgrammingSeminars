using System.Windows;

namespace DACS.HelloWorld.Views
{

    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button1_OnClick(object sender, RoutedEventArgs e)
        {
            MessageBox.Show(this, "Header", "Content", MessageBoxButton.OK);
        }
        
    }
    
}