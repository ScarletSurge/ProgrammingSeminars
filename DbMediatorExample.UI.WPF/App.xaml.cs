using System.Windows;

using DbMediatorExample.UI.WPF.ViewModels;
using DbMediatorExample.UI.WPF.Views;

namespace DbMediatorExample.UI.WPF
{

    public partial class App : Application
    {

        public App()
        {
            (App.Current.MainWindow = new MainWindow { DataContext = new MainViewModel() }).Show();
        }

    }

}