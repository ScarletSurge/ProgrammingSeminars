using System.Windows.Input;

namespace RGU.DistributedSystems.WPF.MVVM;

public class RelayCommand:
    ICommand
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Action<object?> _execute;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Predicate<object?>? _canExecute;

    #endregion
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="execute"></param>
    /// <param name="canExecute"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public RelayCommand(
        Action<object?> execute,
        Predicate<object?>? canExecute = null)
    {
        _canExecute = canExecute;
        _execute = execute ?? throw new ArgumentNullException(nameof(execute));
    }
    
    #region System.Windows.Input.ICommand implementation
    
    /// <inheritdoc cref="ICommand.CanExecute" />
    public bool CanExecute(
        object? parameter)
    {
        return _canExecute?.Invoke(parameter) ?? true;
    }
    
    /// <inheritdoc cref="ICommand.Execute" />
    public void Execute(
        object? parameter)
    {
        _execute(parameter);
    }
    
    /// <inheritdoc cref="ICommand.CanExecuteChanged" />
    public event EventHandler? CanExecuteChanged
    {
        add =>
            CommandManager.RequerySuggested += value;

        remove =>
            CommandManager.RequerySuggested -= value;
    }

    #endregion

}