using System.Windows;
using System.Windows.Input;

using DACS.WPF.DependencyProperties.ViewModels;

namespace DACS.WPF.DependencyProperties.Views
{
    
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
        }

        private void UIElement_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (!(DataContext is MainWindowViewModel mwvm))
            {
                return;
            }

            var controlTypeName = sender.GetType().Name;
            mwvm.AddLog($"{nameof(MouseLeftButtonDown)} event handler called for control of type {controlTypeName}");

            e.Handled = false;
        }

        private void UIElement_OnPreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (!(DataContext is MainWindowViewModel mwvm))
            {
                return;
            }
            
            var controlTypeName = sender.GetType().Name;
            mwvm.AddLog($"{nameof(PreviewMouseLeftButtonDown)} event handler called for control of type {controlTypeName}");
            
            e.Handled = false;
        }
    }
    
}