using System.Windows;

using RGU.DistibutedSystems.Launcher.App.ViewModel;

namespace RGU.DistibutedSystems.Launcher.App.View;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{

    private int _value = 0;
    
    public MainWindow()
    {
        InitializeComponent();
        DataContext = new MainWindowViewModel(TimeSpan.FromMilliseconds(150));
        // DataContext = App.Container.Resolve<MainWindowViewModel>();
    }

    private void ButtonBase1_OnClick(
        object sender,
        RoutedEventArgs e)
    {
        Application.Current.Shutdown();
    }

    private void ButtonBase2_OnClick(
        object sender,
        RoutedEventArgs e)
    {
        MessageBox.Show("Hello!");
    }
    
}