using System.Linq;
using System.Windows.Input;

using DbMediatorExample.Database.Models;
using DbMediatorExample.UI.WPF.Commands;
using DbMediatorExample.UI.WPF.Navigation;

namespace DbMediatorExample.UI.WPF.ViewModels
{

    internal sealed class TargetDataPageViewModel : BaseViewModel
    {

        private string _selectedRegionName;
        private Region[] _regions;
        private TargetViewModel[] _targets;
        private ICommand _goBackCommand;

        public TargetDataPageViewModel(Region[] regions, Target[] targets)
        {
            Regions = regions;
            Targets = targets.Select(target => new TargetViewModel(target)).ToArray();
        }

        public Region[] Regions
        {
            get =>
                _regions;

            private set
            {
                _regions = value;
                OnPropertyChanged(nameof(Regions));
            }
        }

        public TargetViewModel[] Targets
        {
            get =>
                _targets;

            private set
            {
                _targets = value;
                OnPropertyChanged(nameof(Targets));
            }
        }

        public Region SelectedRegion
        {
            set
            {
                SelectedRegionName = value?.Name ?? string.Empty;
            }
        }

        public string SelectedRegionName
        {
            get =>
                _selectedRegionName;

            private set
            {
                _selectedRegionName = value;
                OnPropertyChanged(nameof(SelectedRegionName));
            }
        }

        public ICommand GoBackCommand =>
            _goBackCommand ?? (_goBackCommand = new RelayCommand(_ => GoBack()));

        private void GoBack()
        {
            NavigationManager.GoBack();
        }

    }

}