using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

using DbMediatorExample.Database;
using DbMediatorExample.Database.Models.Enums;
using DbMediatorExample.UI.WPF.Commands;
using DbMediatorExample.UI.WPF.Navigation;
using DbMediatorExample.UI.WPF.Views.Pages;

namespace DbMediatorExample.UI.WPF.ViewModels.Pages
{

    internal sealed class AuthorizationPageViewModel : BaseViewModel
    {

        private string _login = string.Empty;
        private string _password = string.Empty;
        private ICommand _authorizeCommand;

        public string Login
        {
            private get =>
                _login;

            set
            {
                _login = value;
                OnPropertyChanged(nameof(Login));
            }
        }

        public string Password
        {
            private get =>
                _password;

            set
            {
                _password = value;
                OnPropertyChanged(nameof(Password));
            }
        }

        public ICommand AuthorizeCommand =>
            _authorizeCommand ?? (_authorizeCommand = new RelayCommand(async _ => await AuthorizeAsync(),
                _ => CanAuthorize()));

        private async Task AuthorizeAsync()
        {
            var mediator = new DatabaseMediator();
            var authorizationResult = await mediator.AuthorizeAsync(Login, Password);
            if (authorizationResult is null)
            {
                MessageBox.Show("Query execution error!");
                return;
            }
            switch (authorizationResult.Value.Item1)
            {
                case AuthorizationStatus.LoginNotExists:
                    MessageBox.Show("Login not exists!");
                    break;
                case AuthorizationStatus.InvalidPassword:
                    MessageBox.Show("Invalid password!");
                    break;
                case AuthorizationStatus.Authorized:
                    MessageBox.Show("Authorization succeeded!");
                    switch (authorizationResult.Value.Item2)
                    {
                        case Role.Admin:
                            var users = (await mediator.GetUsersAsync()).ToArray();
                            var logs = (await mediator.GetLogsAsync()).ToArray();
                            NavigationManager.Navigate<AdminPage>(new AdminPageViewModel(users, logs));
                            break;
                        case Role.User:
                            var regions = (await mediator.GetRegionsAsync()).ToArray();
                            var target = (await mediator.GetTargetsAsync(0)).ToArray();
                            NavigationManager.Navigate<TargetDataPage>(new TargetDataPageViewModel(regions, target));
                            break;
                    }
                    Login = Password = string.Empty;
                    break;
            }
        }

        private bool CanAuthorize()
        {
            return Login.Length > 0 && Password.Length > 0;
        }

    }

}