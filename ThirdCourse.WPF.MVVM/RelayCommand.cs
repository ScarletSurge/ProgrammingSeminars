using System;
using System.Windows.Input;

namespace ThirdCourse.WPF.MVVM
{

    public sealed class RelayCommand : ICommand
    {

        private Func<object, bool> _canExecute;
        private Action<object> _execute;

        public RelayCommand(Action<object> execute, Func<object, bool> canExecute = null)
        {
            _execute = execute;
            _canExecute = canExecute;
        }

        public event EventHandler CanExecuteChanged
        {
            add =>
                CommandManager.RequerySuggested += value;

            remove =>
                CommandManager.RequerySuggested -= value;
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute is null || _canExecute(parameter);
        }

        public void Execute(object parameter)
        {
            _execute?.Invoke(parameter);
        }

    }

}