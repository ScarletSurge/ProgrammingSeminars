using System;
using System.Windows.Input;

using DACS.WPF.HelloWorld.Data;
using DACS.WPF.MVVM.Command;
using DACS.WPF.MVVM.ViewModel;

namespace DACS.WPF.HelloWorld.ViewModels
{
    
    internal sealed class MainWindowViewModel : ViewModelBase
    {
        
        #region Fields
        
        private Point[] _points;
        private bool _isGreenColor;
        
        #endregion
        
        #region Constructors

        public MainWindowViewModel()
        {
            RecalculatePointsCommand = new RelayCommand(
                _ => RecalculatePoints());
        }
        
        #endregion
        
        #region Bindable properties
        
        public Point[] Points
        {
            get =>
                _points;

            private set
            {
                _points = value;
                RaisePropertyChanged(nameof(Points));
            }
        }

        public bool IsGreenColor
        {
            get =>
                _isGreenColor;

            set
            {
                _isGreenColor = value;
                RaisePropertyChanged(nameof(IsGreenColor));
            }
        }
        
        #endregion
        
        #region Commands

        public ICommand RecalculatePointsCommand { get; }

        #endregion
        
        #region Methods

        private void RecalculatePoints()
        {
            var rndSource = new Random();
            var newPoints = new Point[rndSource.Next(5, 16)];
            for (var i = 0; i < newPoints.Length; i++)
            {
                newPoints[i].X = rndSource.Next(150);
                newPoints[i].Y = rndSource.Next(150);
                newPoints[i].Size = rndSource.Next(15, 26);
            }

            Points = newPoints;
        }
        
        #endregion
        
    }
    
}