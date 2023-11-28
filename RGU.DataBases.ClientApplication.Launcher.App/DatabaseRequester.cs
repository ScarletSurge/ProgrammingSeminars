using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Npgsql;

namespace RGU.DataBases.ClientApplication.Launcher.App;

public class DatabaseRequester
{
    
    private const string DbConnectionString =
        "Server=127.0.0.1;Port=5432;Database=helloworld;User Id=postgres;Password=postgres;";
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="surnameSubstring">aboba</param>
    /// <param name="nameSubstring">kryuksima</param>
    /// <param name="patronymicSubstring">tryukina</param>
    /// <param name="token"></param>
    /// <returns></returns>
    public async Task<List<Student>> GetAllStudentsAsync(
        string? surnameSubstring = null,
        string? nameSubstring = null,
        string? patronymicSubstring = null,
        CancellationToken token = default)
    {
        await using NpgsqlConnection conn = new NpgsqlConnection(DbConnectionString);
        await conn.OpenAsync(token);
        await using NpgsqlCommand comm = conn.CreateCommand();

        var commandTextBuilder = new StringBuilder(GetAllStudentsInfo);
        if (!string.IsNullOrEmpty(surnameSubstring))
        {
            commandTextBuilder.Append($" AND surname LIKE '%{surnameSubstring}%'");
        }
        if (!string.IsNullOrEmpty(nameSubstring))
        {
            commandTextBuilder.Append($" AND name LIKE '%{nameSubstring}%'");
        }
        if (!string.IsNullOrEmpty(patronymicSubstring))
        {
            commandTextBuilder.Append($" AND patronymic LIKE '%{patronymicSubstring}%'");
        }
        
        comm.CommandText = commandTextBuilder.ToString();
        await using NpgsqlDataReader reader = await comm.ExecuteReaderAsync(token);
        var resultStudents = new List<Student>();
        while (await reader.ReadAsync(token))
        {
            var gotValue = default(object);
            var recordBookNumber = (string) reader["record_book_number"];
            var surname = (gotValue = reader["surname"]).Equals(DBNull.Value)
                ? null
                : (string) gotValue;
            var name = (gotValue = reader["name"]).Equals(DBNull.Value)
                ? null
                : (string) gotValue;
            var patronymic = (gotValue = reader["patronymic"]).Equals(DBNull.Value)
                ? null
                : (string) gotValue;
            var birthday = (DateTime) reader["birthday"];
            var course = (gotValue = reader["course"]).Equals(DBNull.Value)
                ? null
                : (int?) gotValue;
            var faq = (gotValue = reader["faq"]).Equals(DBNull.Value)
                ? null
                : (string) gotValue;
            var scientificAdviserId = (gotValue = reader["scientific_adviser"]).Equals(DBNull.Value)
                ? null
                : (int?) gotValue;

            resultStudents.Add(new Student
            {
                RecordBookNumber = recordBookNumber,
                Surname = surname,
                Name = name,
                Patronymic = patronymic,
                Birthday = birthday,
                Course = course,
                Faq = faq,
                ScientificAdviserId = scientificAdviserId
            });
        }

        return resultStudents;
    }

    private const string GetAllStudentsInfo = "SELECT * FROM public.students WHERE 1=1";
}