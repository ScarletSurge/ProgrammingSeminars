using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Windows.Input;

using ThirdCourse.WPF.MVVM;

namespace ThirdCourse.WPF.Strings.ViewModels
{

    internal sealed class MainWindowViewModel : BaseViewModel
    {

        #region Fields

        private ObservableCollection<StringsViewModel> _strings;
        private string _myStringFromViewModel;

        #region Command fields

        private ICommand _addStringsCommand;

        #endregion

        #endregion

        #region Constructors

        public MainWindowViewModel()
        {
            Strings = new ObservableCollection<StringsViewModel>();
        }

        #endregion

        #region Properties

        public ObservableCollection<StringsViewModel> Strings
        {
            get =>
                _strings;

            private set
            {
                _strings = value;
                OnPropertyChanged(nameof(Strings));
            }
        }

        public string MyStringFromViewModel
        {
            get =>
                _myStringFromViewModel;

            private set
            {
                _myStringFromViewModel = value;
                OnPropertyChanged(nameof(MyStringFromViewModel));
            }
        }

        #region Command properties

        public ICommand AddStringsCommand =>
            _addStringsCommand ?? (_addStringsCommand = new RelayCommand(_ => AddStrings(),
                _ => CanAddStrings()));

        #endregion

        #endregion

        #region Methods

        private void AddStrings()
        {
            //var stringsViewModel = new StringsViewModel();
            //stringsViewModel.RemovingRequested += (itemToRemove) =>
            //{
            //    Strings.Remove(itemToRemove);
            //    //OnPropertyChanged(nameof(Strings));

            //    // SHITCODE DETECTED!!1!11
            //    //var s = Strings;
            //    //Strings = null;
            //    //Strings = s;
            //};
            var alphabet = string.Concat(Enumerable.Range(0, 26).Select(i => (char)(i + 65)).Concat(
                Enumerable.Range(0, 26).Select(i => (char)(i + 97))));
            var random = new Random();
            var firstNewLength = random.Next(10, 26);
            var sbFirst = new StringBuilder(firstNewLength);
            for (var i = 0; i < firstNewLength; i++)
            {
                sbFirst.Append(alphabet[random.Next(alphabet.Length)]);
            }
            var newStringsViewModel = new StringsViewModel();

            newStringsViewModel.RemovingRequested += (itemToRemove) =>
            {
                Strings.Remove(itemToRemove);
            };
            Strings.Add(newStringsViewModel);
        }

        private bool CanAddStrings()
        {
            return Strings.Count < 5;
        }

        #endregion

    }

}