using System.Windows.Input;

using DbMediatorExample.Database.Models;
using DbMediatorExample.UI.WPF.Commands;

namespace DbMediatorExample.UI.WPF.ViewModels
{

    internal sealed class TargetViewModel : BaseViewModel
    {

        private Target _target;
        private bool _isSelected;
        private ICommand _clickCommand;

        public TargetViewModel(Target target, bool isSelected = false)
        {
            Target = target;
            IsSelected = isSelected;
        }

        public Target Target
        {
            get =>
                _target;

            private set
            {
                _target = value;
                OnPropertyChanged(nameof(Target));
            }
        }

        public bool IsSelected
        {
            get =>
                _isSelected;

            private set
            {
                _isSelected = value;
                OnPropertyChanged(nameof(IsSelected));
            }
        }

        public ICommand ClickCommand =>
            _clickCommand ?? (_clickCommand = new RelayCommand(_ => Click()));

        private void Click()
        {
            IsSelected = !IsSelected;
        }

    }

}