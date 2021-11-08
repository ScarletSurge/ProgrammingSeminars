using ThirdCourse.WPF.MVVM;

namespace ThirdCourse.WPF.Spinner.ViewModels
{

    public sealed class SpinnerItemViewModel : BaseViewModel
    {

        private double _x;
        private double _y;
        private double _angle;

        public double X
        {
            get =>
                _x;

            set
            {
                _x = value;
                OnPropertyChanged(nameof(X));
            }
        }

        public double Y
        {
            get =>
                _y;

            set
            {
                _y = value;
                OnPropertyChanged(nameof(Y));
            }
        }

        public double Angle
        {
            get =>
                _angle;

            set
            {
                _angle = value;
                OnPropertyChanged(nameof(Angle));
            }
        }

    }

}