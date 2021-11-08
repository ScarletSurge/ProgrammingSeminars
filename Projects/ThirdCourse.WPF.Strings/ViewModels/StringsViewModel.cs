using System;
using System.Linq;
using System.Text;
using System.Windows.Input;

using ThirdCourse.WPF.MVVM;
using ThirdCourse.WPF.Strings.Models;

namespace ThirdCourse.WPF.Strings.ViewModels
{

    public sealed class StringsViewModel : BaseViewModel
    {

        #region Fields

        private StringsModel _model;

        #region Command fields

        private ICommand _refreshStringsCommand;
        private ICommand _switchBoolCommand;
        private ICommand _requestRemovingCommand;

        #endregion

        #region Event fields

        public event Action<StringsViewModel> RemovingRequested;

        #endregion

        #endregion

        #region Constructors

        public StringsViewModel()
        {
            _model = new StringsModel();
            OnPropertyChanged(nameof(IsLeftStringVisible));
        }

        #endregion

        #region Properties

        public string First
        {
            get =>
                _model.FirstString;

            private set
            {
                _model.FirstString = value;
                // TODO: nameof is better one
                OnPropertyChanged("First");
            }
        }

        public string Second
        {
            get =>
                _model.SecondString;

            private set
            {
                _model.SecondString = value;
                OnPropertyChanged(nameof(Second));
            }
        }

        public bool IsLeftStringVisible
        {
            get =>
                _model.IsLeftStringVisible;

            private set
            {
                _model.IsLeftStringVisible = value;
                OnPropertiesChanged(nameof(IsLeftStringVisible));
            }
        }

        //public string ButtonText =>
        //IsLeftStringVisible ? "Switch to right" : "Switch to left";

        #region Command properties

        public ICommand RefreshStringsCommand =>
            _refreshStringsCommand ?? (_refreshStringsCommand = new RelayCommand(_ => RefreshStrings()));

        public ICommand SwitchBoolCommand =>
            _switchBoolCommand ?? (_switchBoolCommand = new RelayCommand(_ => SwitchStringsVisibility()));

        public ICommand RequestRemovingCommand =>
            _requestRemovingCommand ?? (_requestRemovingCommand = new RelayCommand(_ => RequestRemoving()));

        #endregion

        #endregion

        #region Methods

        #region Command methods

        private void RefreshStrings()
        {
            var alphabet = string.Concat(Enumerable.Range(0, 26).Select(i => (char)(i + 65)).Concat(
                Enumerable.Range(0, 26).Select(i => (char)(i + 97))));
            var random = new Random();
            var firstNewLength = random.Next(10, 26);
            var secondNewLength = random.Next(10, 26);
            var sbFirst = new StringBuilder(firstNewLength);
            var sbSecond = new StringBuilder(secondNewLength);
            for (var i = 0; i < firstNewLength; i++)
            {
                sbFirst.Append(alphabet[random.Next(alphabet.Length)]);
            }
            for (var i = 0; i < secondNewLength; i++)
            {
                sbSecond.Append(alphabet[random.Next(alphabet.Length)]);
            }
            First = sbFirst.ToString();
            Second = sbSecond.ToString();
        }

        private void SwitchStringsVisibility()
        {
            IsLeftStringVisible = !IsLeftStringVisible;
        }

        private void RequestRemoving()
        {
            RemovingRequested?.Invoke(this);
        }

        #endregion

        #endregion

    }

}