using DbMediatorExample.Database.Models;
using DbMediatorExample.Database.Models.Enums;

namespace DbMediatorExample.UI.WPF.ViewModels
{

    internal sealed class UserViewModel : BaseViewModel
    {

        private User _user;

        public UserViewModel(User user)
        {
            User = user;
        }

        public User User
        {
            get =>
                _user;

            private set
            {
                _user = value;
                OnPropertyChanged(nameof(User));
            }
        }

        public Role Role
        {
            get =>
                User.Role;

            set
            {
                User.Role = value;
                OnPropertyChanged(nameof(Role));
            }
        }

    }

}