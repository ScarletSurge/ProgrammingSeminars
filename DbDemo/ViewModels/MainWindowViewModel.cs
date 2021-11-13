using System;
using System.Collections.ObjectModel;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

using DbDemo.Models;
using DbDemo.WPF.MVVM.Command;
using DbDemo.WPF.MVVM.ViewModel;

namespace DbDemo.ViewModels
{
    
    internal sealed class MainWindowViewModel : ViewModelBase
    {
        
        #region Fields
        
        private ICommand _selectCommand;
        private ICommand _insertCommand;
        private readonly Connector.Connector _dbConnector;
        private ObservableCollection<EmployeeFullInfo> _employees;
        private ReadOnlyObservableCollection<RoleInfo> _roles;
        private string _name;
        private string _salaryString;
        private RoleInfo _selectedRoleInfo;

        #endregion
        
        #region Constructors
        
        public MainWindowViewModel()
        {
            _dbConnector = new Connector.Connector("Host=localhost;Username=postgres;Password=postgres;Database=db_third_course");
            Employees = new ObservableCollection<EmployeeFullInfo>();
            
            try
            {
                Roles = new ReadOnlyObservableCollection<RoleInfo>(
                    new ObservableCollection<RoleInfo>(
                        _dbConnector.SelectRoles()));
            }
            catch (AggregateException ex)
            {
                
            }
        }
        
        #endregion
        
        #region Properties
        
        public ICommand SelectCommand =>
            _selectCommand ??= new RelayCommand(async _ => await SelectEmployeesAsync());
        public ICommand InsertCommand =>
            _insertCommand ??= new RelayCommand(async _ => await InsertEmployeeAsync(),
                _ => CanExecuteInsertEmployee());

        public ReadOnlyObservableCollection<RoleInfo> Roles
        {
            get =>
                _roles;

            private set
            {
                _roles = value;
                RaisePropertyChanged(nameof(Roles));
            }
        }

        public ObservableCollection<EmployeeFullInfo> Employees
        {
            get =>
                _employees;

            private set
            {
                _employees = value;
                RaisePropertyChanged(nameof(Employees));
            }
        }

        public string Name
        {
            private get =>
                _name;

            set
            {
                _name = value;
                RaisePropertyChanged(nameof(Name));
            }
        }

        public string SalaryString
        {
            private get =>
                _salaryString;

            set
            {
                _salaryString = value;
                RaisePropertyChanged(nameof(SalaryString));
            }
        }

        public RoleInfo SelectedRoleInfo
        {
            private get =>
                _selectedRoleInfo;

            set
            {
                _selectedRoleInfo = value;
            }
        }
        
        #endregion
        
        #region Methods
        
        private async Task RawTextSelectEmployeesAsync(CancellationToken token = default)
        {
            try
            {
                var employees = await _dbConnector.RawTextSelectEmployeesAsync(token);
                Employees = new ObservableCollection<EmployeeFullInfo>(employees);
            }
            catch (AggregateException ex)
            {
                MessageBox.Show($"Failed to execute query: \"{ex.Message}\"");
            }
        }
        
        private async Task SelectEmployeesAsync(CancellationToken token = default)
        {
            try
            {
                var employees = await _dbConnector.SelectEmployeesAsync(token);
                Employees = new ObservableCollection<EmployeeFullInfo>(employees);
            }
            catch (AggregateException ex)
            {
                MessageBox.Show($"Failed to execute query: \"{ex.Message}\"");
            }
        }

        private async Task InsertEmployeeAsync(CancellationToken token = default)
        {
            try
            {
                decimal.TryParse(SalaryString, out var salary);
                await _dbConnector.InsertEmployeeAsync(Name, salary, SelectedRoleInfo.Id, token);
                var employees = await _dbConnector.SelectEmployeesAsync(token);
                Employees = new ObservableCollection<EmployeeFullInfo>(employees);
            }
            catch (AggregateException ex)
            {
                MessageBox.Show($"Failed to execute query: \"{ex.Message}\"");
            }
        }

        private bool CanExecuteInsertEmployee()
        {
            return !string.IsNullOrEmpty(Name)
                   && decimal.TryParse(SalaryString, out var salary)
                   && salary >= 0
                   && (SelectedRoleInfo?.Id ?? 0) != 0;
        }
        
        #endregion

    }
    
}