using System.Windows;
using System.Windows.Input;

using DbMediatorExample.UI.WPF.Navigation;

namespace DbMediatorExample.UI.WPF.Views
{

    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
            NavigationCommands.BrowseBack.InputGestures.Clear();
            NavigationCommands.BrowseForward.InputGestures.Clear();
            NavigationManager.NavigationService = _navigationFrame.NavigationService;
        }
        
    }

}