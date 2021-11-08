using System.Windows.Input;

using ThirdCourse.WPF.MVVM;

namespace ThirdCourse.WPF.Spinner.ViewModels
{

    internal sealed class MainWindowViewModel : BaseViewModel
    {

        private int _circlesCount;
        private bool _isRotating;
        private bool _isRotatingClockwise;
        private ICommand _decrementCirclesCountCommand;
        private ICommand _incrementCirclesCountCommand;

        public MainWindowViewModel()
        {
            CirclesCount = 3;
        }

        public bool IsRotating
        {
            get =>
                _isRotating;

            set
            {
                _isRotating = value;
                OnPropertyChanged(nameof(IsRotating));
            }
        }

        public bool IsRotatingClockwise
        {
            get =>
                _isRotatingClockwise;

            set
            {
                _isRotatingClockwise = value;
                OnPropertyChanged(nameof(IsRotatingClockwise));
            }
        }

        public int CirclesCount
        {
            get =>
                _circlesCount;

            private set
            {
                _circlesCount = value;
                OnPropertyChanged(nameof(CirclesCount));
            }
        }

        public ICommand DecrementCirclesCountCommand =>
            _decrementCirclesCountCommand ?? (_decrementCirclesCountCommand = new RelayCommand(_ => DecrementCirclesCount(),
                _ => CanDecrementCirclesCount()));

        public ICommand IncrementCirclesCountCommand =>
            _incrementCirclesCountCommand ?? (_incrementCirclesCountCommand = new RelayCommand(_ => IncrementCirclesCount()));

        private void DecrementCirclesCount()
        {
            CirclesCount--;
        }

        private bool CanDecrementCirclesCount()
        {
            return CirclesCount != 3;
        }

        private void IncrementCirclesCount()
        {
            CirclesCount++;
        }

    }

}