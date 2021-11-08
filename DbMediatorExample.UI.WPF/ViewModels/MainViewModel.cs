using DbMediatorExample.UI.WPF.Navigation;
using DbMediatorExample.UI.WPF.ViewModels.Pages;
using DbMediatorExample.UI.WPF.Views.Pages;

namespace DbMediatorExample.UI.WPF.ViewModels
{

    internal sealed class MainViewModel : BaseViewModel
    {

        public MainViewModel()
        {
            NavigationManager.Navigate<AuthorizationPage>(new AuthorizationPageViewModel());
        }

    }

}