using Npgsql;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Input;

using DbDemo.Models;
using DbDemo.WPF.MVVM.Command;
using DbDemo.WPF.MVVM.ViewModel;

namespace DbDemo.ViewModels
{
    
    internal sealed class MainWindowViewModel : ViewModelBase
    {
        
        private const string ConnectionString = "Host=localhost;Username=postgres;Password=postgres;Database=db2122";

        private ICommand _selectCommand;
        private ICommand _insertCommand;
        private ObservableCollection<EmployeeFullInfo> _employees;

        public MainWindowViewModel()
        {
            Employees = new ObservableCollection<EmployeeFullInfo>();
        }

        public ICommand SelectCommand =>
            _selectCommand ??= new RelayCommand(async _ => await SelectAsync());
        public ICommand InsertCommand =>
            _insertCommand ??= new RelayCommand(async _ => await InsertAsync());

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
        
        private async Task SelectAsync1(CancellationToken token = default)
        {
            await using var connection = new NpgsqlConnection(ConnectionString);
            await connection.OpenAsync(token);
            
            // Retrieve all rows
            await using var cmd = new NpgsqlCommand(
              "SELECT" +
                       $"{FrameWithQuotes("e")}.{FrameWithQuotes("id")} AS {FrameWithQuotes("employee_id")}, " +
                       $"{FrameWithQuotes("e")}.{FrameWithQuotes("name")} AS {FrameWithQuotes("employee_name")}, " +
                       $"{FrameWithQuotes("e")}.{FrameWithQuotes("salary")} AS {FrameWithQuotes("employee_salary")}, " +
                       $"{FrameWithQuotes("r")}.{FrameWithQuotes("name")} AS {FrameWithQuotes("role_name")}, " +
                       $"{FrameWithQuotes("r")}.{FrameWithQuotes("description")} AS {FrameWithQuotes("role_description")} " +
                $"FROM {FrameWithQuotes("employees")} AS {FrameWithQuotes("e")} " +
                  $"INNER JOIN {FrameWithQuotes("roles")} AS {FrameWithQuotes("r")} " +
                    $"ON {FrameWithQuotes("r")}.{FrameWithQuotes("id")} = {FrameWithQuotes("e")}.{FrameWithQuotes("role_id")}", connection);
            await using var reader = await cmd.ExecuteReaderAsync(token);

            var selectedItems = new List<EmployeeFullInfo>();
            while (await reader.ReadAsync(token))
            {
                var employeeId = (int)reader["employee_id"];
                var employeeName = (string)reader["employee_name"];
                var employeeSalary = (decimal)reader["employee_salary"];
                var roleName = (string)reader["role_name"];
                var roleDescription = (string)reader["role_description"];

                selectedItems.Add(new EmployeeFullInfo(
                    employeeId, employeeName, employeeSalary, roleName, roleDescription));
            }

            Employees = new ObservableCollection<EmployeeFullInfo>(selectedItems);
        }

        private async Task SelectAsync(CancellationToken token = default)
        {
            await using var connection = new NpgsqlConnection(ConnectionString);
            await connection.OpenAsync(token);
            
            // Retrieve all rows
            await using var cmd = new NpgsqlCommand("test_function", connection)
            {
                CommandType = CommandType.StoredProcedure
            };
            await using var reader = await cmd.ExecuteReaderAsync(token);

            var selectedItems = new List<EmployeeFullInfo>();
            while (await reader.ReadAsync(token))
            {
                var employeeName = (string)reader["name"];
                var employeeSalary = (decimal)reader["salary"];
                var roleName = (string)reader["role"];
                var roleDescription = (string)reader["description"];

                selectedItems.Add(new EmployeeFullInfo(
                    0, employeeName, employeeSalary, roleName, roleDescription));
            }

            Employees = new ObservableCollection<EmployeeFullInfo>(selectedItems);
        }

        private string FrameWithQuotes(string toFrame)
        {
            return $"\"{toFrame}\"";
        }

        private async Task InsertAsync()
        {
            // TODO
        }

    }
    
}