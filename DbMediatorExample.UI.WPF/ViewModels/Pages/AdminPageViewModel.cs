using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

using DbMediatorExample.Database;
using DbMediatorExample.Database.Models;
using DbMediatorExample.UI.WPF.Commands;
using DbMediatorExample.UI.WPF.Navigation;

namespace DbMediatorExample.UI.WPF.ViewModels.Pages
{

    internal sealed class AdminPageViewModel : BaseViewModel
    {

        private ICommand _goBackCommand;
        private ICommand _saveChangesCommand;
        private UserViewModel[] _users;
        private LogViewModel[] _logs;

        public AdminPageViewModel(User[] users, Log[] logs)
        {
            Users = users.Select(user => new UserViewModel(user)).ToArray();
            Logs = logs.Select(log => new LogViewModel(log)).ToArray();
        }

        public UserViewModel[] Users
        {
            get =>
                _users;

            private set
            {
                _users = value;
                OnPropertyChanged(nameof(Users));
            }
        }

        public LogViewModel[] Logs
        {
            get =>
                _logs;

            private set
            {
                _logs = value;
                OnPropertyChanged(nameof(Logs));
            }
        }

        public ICommand GoBackCommand =>
            _goBackCommand ?? (_goBackCommand = new RelayCommand(_ => GoBack()));

        public ICommand SaveChangesCommand =>
            _saveChangesCommand ?? (_saveChangesCommand = new RelayCommand(async _ => await SaveChanges()));

        private void GoBack()
        {
            NavigationManager.GoBack();
        }

        private async Task SaveChanges()
        {
            var mediator = new DatabaseMediator();
            if (!await mediator.UpdateUsersAsync(Users.Select(userVM => userVM.User).ToArray()))
            {
                MessageBox.Show("Script executing error!");
                return;
            }
            MessageBox.Show("Success!");
            NavigationManager.GoBack();
        }

    }

}