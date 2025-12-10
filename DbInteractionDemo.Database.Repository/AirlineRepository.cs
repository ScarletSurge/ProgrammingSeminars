using Npgsql;

using DbInteractionDemo.Database.Data;

namespace DbInteractionDemo.Database.Repository;

/// <summary>
/// 
/// </summary>
public sealed class AirlineRepository
{

    #region Constants

    /// <summary>
    /// 
    /// </summary>
    private const string TableSchema = "public";

    /// <summary>
    /// 
    /// </summary>
    private const string TableName = "airline";

    /// <summary>
    /// 
    /// </summary>
    private const string TableNameAlias = "a";

    #endregion

    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private readonly DatabaseConnectionFactory _dcf;

    #endregion

    #region Constructors

    /// <summary>
    /// 
    /// </summary>
    /// <param name="dcf"></param>
    public AirlineRepository(
        DatabaseConnectionFactory dcf)
    {
        _dcf = dcf ?? throw new ArgumentNullException(nameof(dcf));
    }

    // public sealed class TaskLike
    // {
    //     public TaskAwaiter<int> GetAwaiter()
    //     {
    //         return new TaskAwaiter<int>();
    //     }
    // }
    // 
    // private async TaskLike PukPukAsync()
    // {
    //     return new TaskLike();
    // }

    #endregion

    #region API

    /// <summary>
    /// 
    /// </summary>
    /// <param name="airline"></param>
    /// <returns></returns>
    public async Task<string> AddAsync(
        Airline airline,
        CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="id"></param>
    /// <returns></returns>
    public async Task<Airline?> GetByIdAsync(
        string id,
        CancellationToken cancellationToken = default)
    {
        ArgumentNullException.ThrowIfNullOrEmpty(id);

        cancellationToken.ThrowIfCancellationRequested();

        // TODO: так делают только пуксреньки
        var query = $"SELECT * FROM {TableSchema}.{TableName} {TableNameAlias} WHERE {TableNameAlias}.id = '{id}'";

        using var connection = _dcf.Create();
        using var command = new NpgsqlCommand(query, connection);
        command.CommandType = System.Data.CommandType.Text;

        using var reader = await command.ExecuteReaderAsync(cancellationToken);

        if (!await reader.ReadAsync(cancellationToken))
        {
            return null;
        }

        var airlineId = (string)reader.GetValue(0);
        var airlineFullName = (string)reader.GetValue(1);
        var airlineBaseAirportCode = (string)reader.GetValue(2);

        return new Airline
        {
            Id = airlineId,
            FullName = airlineFullName,
            BaseAirportCode = airlineBaseAirportCode
        };
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    public async IAsyncEnumerable<Airline> GetAllAsync(
        CancellationToken cancellationToken = default)
    {
        cancellationToken.ThrowIfCancellationRequested();

        // TODO: так делают только пуксреньки
        var query = $"SELECT * FROM {TableSchema}.{TableName} {TableNameAlias}";

        using var connection = _dcf.Create();
        using var command = new NpgsqlCommand(query, connection);
        command.CommandType = System.Data.CommandType.Text;

        using var reader = await command.ExecuteReaderAsync(cancellationToken);

        while (await reader.ReadAsync(cancellationToken))
        {
            var airlineId = (string)reader.GetValue(0);
            var airlineFullName = (string)reader.GetValue(1);
            var airlineBaseAirportCode = (string)reader.GetValue(2);

            yield return new Airline
            {
                Id = airlineId,
                FullName = airlineFullName,
                BaseAirportCode = airlineBaseAirportCode
            };
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="id"></param>
    /// <param name="airline"></param>
    public async Task UpdateAsync(
        string id,
        Airline airline,
        CancellationToken cancellationToken = default)
    {
        throw new NotImplementedException();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="id"></param>
    public async Task DeleteAsync(
        string id)
    {
        throw new NotImplementedException();
    }

    #endregion

}