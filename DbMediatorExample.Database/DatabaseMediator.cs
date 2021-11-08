using System.Data;
using System.Data.SqlClient;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

using DbMediatorExample.Database.Models;
using DbMediatorExample.Database.Models.Enums;

namespace DbMediatorExample.Database
{

    public class DatabaseMediator
    {

        private const string ConnectionString = "Data Source=localhost\\SQLEXPRESS;Initial Catalog=DbMediator;Trusted_Connection=True";
        private const string GetTargetsRequest = "[dbo].[sp_get_target]";
        private const string GetRegionsRequest = "[dbo].[sp_get_regions]";
        private const string AuthorizationRequest = "[dbo].[sp_authorize]";
        private const string GetUsersRequest = "[dbo].[sp_get_users]";
        private const string UpdateUserRequest = "[dbo].[sp_update_user]";
        private const string GetLogsRequest = "[dbo].[sp_get_logs]";

        public async Task<(AuthorizationStatus, Role)?> AuthorizeAsync(string login, string password)
        {
            try
            {
                var passwordBytes = default(byte[]);
                using (var md5 = MD5.Create())
                {
                    passwordBytes = md5.ComputeHash(Encoding.ASCII.GetBytes(password));
                }
                using (var connection = new SqlConnection(ConnectionString))
                {
                    await connection.OpenAsync();
                    using (var command = new SqlCommand(AuthorizationRequest, connection)
                    {
                        CommandType = CommandType.StoredProcedure
                    })
                    {
                        command.Parameters.AddWithValue("@login", login);
                        command.Parameters.AddWithValue("@password", passwordBytes);
                        var authorizedParameter = command.Parameters.Add("@authorized", SqlDbType.Int);
                        authorizedParameter.Direction = ParameterDirection.Output;
                        var roleParameter = command.Parameters.Add("@role_id", SqlDbType.Int);
                        roleParameter.Direction = ParameterDirection.Output;
                        await command.ExecuteScalarAsync();
                        var authorisationStatus = (AuthorizationStatus)(int)authorizedParameter.Value;
                        if (authorisationStatus != 0)
                        {
                            return (authorisationStatus, Role.User);
                        }
                        return (authorisationStatus, (Role)(int)roleParameter.Value);
                    }
                }
            }
            catch (SqlException)
            {
                return null;
            }
        }

        public async Task<IEnumerable<Target>> GetTargetsAsync(int regionId)
        {
            try
            {
                var result = new List<Target>();
                using (var connection = new SqlConnection(ConnectionString))
                {
                    await connection.OpenAsync();
                    using (var command = new SqlCommand(GetTargetsRequest, connection)
                    {
                        CommandType = CommandType.StoredProcedure
                    })
                    {
                        command.Parameters.AddWithValue("@region_id", regionId);
                        using (var reader = await command.ExecuteReaderAsync())
                        {
                            while (await reader.ReadAsync())
                            {
                                var target = new Target
                                {
                                    Id = reader.GetInt32(0),
                                    Login = reader.GetString(1),
                                    Name = reader.GetString(2),
                                    Surname = reader.GetString(3),
                                    BirthDate = reader.GetDateTime(4),
                                    Region = reader.GetString(5)
                                };
                                result.Add(target);
                            }
                        }
                    }
                }
                return result;
            }
            catch (SqlException)
            {
                return Enumerable.Empty<Target>();
            }
        }

        public async Task<IEnumerable<Region>> GetRegionsAsync()
        {
            try
            {
                var result = new List<Region>();
                using (var connection = new SqlConnection(ConnectionString))
                {
                    await connection.OpenAsync();
                    using (var command = new SqlCommand(GetRegionsRequest, connection)
                    {
                        CommandType = CommandType.StoredProcedure
                    })
                    {
                        using (var reader = await command.ExecuteReaderAsync())
                        {
                            while (await reader.ReadAsync())
                            {
                                var region = new Region
                                {
                                    Id = reader.GetInt32(0),
                                    Name = reader.GetString(1),
                                };
                                result.Add(region);
                            }
                        }
                    }
                }
                return result;
            }
            catch (SqlException)
            {
                return Enumerable.Empty<Region>();
            }
        }

        public async Task<IEnumerable<User>> GetUsersAsync()
        {
            try
            {
                var result = new List<User>();
                using (var connection = new SqlConnection(ConnectionString))
                {
                    await connection.OpenAsync();
                    using (var command = new SqlCommand(GetUsersRequest, connection)
                    {
                        CommandType = CommandType.StoredProcedure
                    })
                    {
                        using (var reader = await command.ExecuteReaderAsync())
                        {
                            while (await reader.ReadAsync())
                            {
                                var user = new User
                                {
                                    Id = reader.GetInt32(0),
                                    Login = reader.GetString(1),
                                    Role = (Role)reader.GetInt32(2)
                                };
                                result.Add(user);
                            }
                        }
                    }
                }
                return result;
            }
            catch (SqlException)
            {
                return Enumerable.Empty<User>();
            }
        }

        public async Task<bool> UpdateUsersAsync(User[] users)
        {
            using (var connection = new SqlConnection(ConnectionString))
            {
                await connection.OpenAsync();
                using (var transaction = connection.BeginTransaction())
                {
                    try
                    {
                        foreach (var user in users)
                        {
                            if (!await UpdateUserAsync(user, connection, transaction))
                            {
                                transaction.Rollback();
                                return false;
                            }
                        }
                        if (users.Any(User => User.Role == Role.Admin))
                        {
                            transaction.Commit();
                            return true;
                        }
                        transaction.Rollback();
                        return false;
                    }
                    catch (SqlException)
                    {
                        transaction.Rollback();
                        return false;
                    }
                }
            }

            async Task<bool> UpdateUserAsync(User user, SqlConnection connection, SqlTransaction transaction)
            {
                try
                {
                    using (var command = new SqlCommand(UpdateUserRequest, connection, transaction)
                    {
                        CommandType = CommandType.StoredProcedure
                    })
                    {
                        command.Parameters.AddWithValue("@user_id", user.Id);
                        command.Parameters.AddWithValue("@role_id", (int)user.Role);
                        await command.ExecuteScalarAsync();
                    }
                    return true;
                }
                catch (SqlException)
                {
                    return false;
                }
            }
        }

        public async Task<IEnumerable<Log>> GetLogsAsync()
        {
            try
            {
                var result = new List<Log>();
                using (var connection = new SqlConnection(ConnectionString))
                {
                    await connection.OpenAsync();
                    using (var command = new SqlCommand(GetLogsRequest, connection)
                    {
                        CommandType = CommandType.StoredProcedure
                    })
                    {
                        using (var reader = await command.ExecuteReaderAsync())
                        {
                            while (await reader.ReadAsync())
                            {
                                var log = new Log
                                {
                                    Id = reader.GetInt32(0),
                                    Description = reader.GetString(1),
                                    Created = reader.GetDateTime(2),
                                    UserLogin = reader.GetSqlString(3).IsNull ? null : reader.GetString(3)
                                };
                                result.Add(log);
                            }
                        }
                    }
                }
                return result;
            }
            catch (SqlException)
            {
                return Enumerable.Empty<Log>();
            }
        }

    }

}