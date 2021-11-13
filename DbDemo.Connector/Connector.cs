using System;
using System.Collections.Generic;
using System.Data;
using System.Threading;
using System.Threading.Tasks;
using DbDemo.Models;
using Npgsql;
using NpgsqlTypes;

namespace DbDemo.Connector
{
    
    public sealed class Connector
    {
        
        #region Constants

        private const string TestFunction = "test_function";
        private const string InsertEmployee = "f_insert_employee";
        
        #endregion
        
        #region Fields
        
        private readonly string _connectionString;
        
        #endregion
        
        #region Constructors
        
        public Connector(string connectionString)
        {
            _connectionString = connectionString ?? throw new ArgumentNullException(nameof(connectionString));
        }
        
        #endregion
        
        #region Query methods

        public async Task<List<EmployeeFullInfo>> RawTextSelectEmployeesAsync(CancellationToken token = default)
        {
            try
            {
                await using var connection = new NpgsqlConnection(_connectionString);
                await connection.OpenAsync(token);
                
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

                return selectedItems;
            }
            catch (Exception ex)
            {
                // TODO: logger
                throw new AggregateException($"Query \"{nameof(RawTextSelectEmployeesAsync)}\" to PostgreSQL failed", ex);
            }
        }
        
        public async Task<List<EmployeeFullInfo>> SelectEmployeesAsync(CancellationToken token = default)
        {
            try
            {
                await using var connection = new NpgsqlConnection(_connectionString);
                await connection.OpenAsync(token);
                
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

                return selectedItems;
            }
            catch (Exception ex)
            {
                // TODO: logger
                throw new AggregateException($"Query \"{nameof(SelectEmployeesAsync)}\" to PostgreSQL failed", ex);
            }
        }

        public async Task InsertEmployeeAsync(string name, decimal salary, int roleId = 4, CancellationToken token = default)
        {
            try
            {
                await using var connection = new NpgsqlConnection(_connectionString);
                await connection.OpenAsync(token);
                await using var transaction = await connection.BeginTransactionAsync(token);
                
                await using var cmd = new NpgsqlCommand("f_insert_employee", connection)
                {
                    CommandType = CommandType.StoredProcedure
                };
            
                cmd.Parameters.Add("name", NpgsqlDbType.Varchar, 50)
                    .Value = name;
                cmd.Parameters.Add("salary", NpgsqlDbType.Money)
                    .Value = salary;
                cmd.Parameters.Add("role_id", NpgsqlDbType.Integer)
                    .Value = roleId;
                
                await cmd.ExecuteScalarAsync(token);
                await transaction.CommitAsync(token);
            }
            catch (Exception ex)
            {
                // TODO: logger
                throw new AggregateException($"Query \"{nameof(InsertEmployeeAsync)}\" to PostgreSQL failed", ex);
            }
        }

        public List<RoleInfo> SelectRoles()
        {
            try
            {
                using var connection = new NpgsqlConnection(_connectionString);
                connection.Open();
                
                using var cmd = new NpgsqlCommand("SELECT * FROM \"roles\"", connection);
                using var reader = cmd.ExecuteReader();
                
                var selectedItems = new List<RoleInfo>();
                while (reader.Read())
                {
                    var roleId = (int)reader["id"];
                    var roleName = (string)reader["name"];
                    var roleDescription = (string)reader["description"];
                    
                    selectedItems.Add(new RoleInfo(
                        roleId, roleName, roleDescription));
                }

                return selectedItems;
            }
            catch (Exception ex)
            {
                // TODO: logger
                throw new AggregateException($"Query \"{nameof(SelectRoles)}\" to PostgreSQL failed", ex);
            }
        }
        
        #endregion
        
        #region Helper methods
        
        private string FrameWithQuotes(string toFrame)
        {
            return $"\"{toFrame}\"";
        }
        
        #endregion
        
    }
    
}