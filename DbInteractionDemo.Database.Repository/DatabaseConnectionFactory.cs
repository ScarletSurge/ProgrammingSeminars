using Npgsql;

using DbInteractionDemo.Core;

namespace DbInteractionDemo.Database.Repository;

/// <summary>
/// 
/// </summary>
public sealed class DatabaseConnectionFactory:
    IAbstractFactory<NpgsqlConnection>
{

    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private readonly string _connectionString;

    #endregion

    #region Constructors

    /// <summary>
    /// 
    /// </summary>
    /// <param name="connectionString"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public DatabaseConnectionFactory(
        string connectionString)
    {
        _connectionString = connectionString ?? throw new ArgumentNullException(nameof(connectionString));
    }

    #endregion

    #region Properties

    /// <summary>
    /// 
    /// </summary>
    public string ConnectionString =>
        _connectionString;

    #endregion

    #region DBInteractionDemo.Core.IAbstractFactory<NpgsqlConnection> implementation

    /// <inheritdoc cref="IAbstractFactory{T}.Create" />
    public NpgsqlConnection Create()
    {
        return new NpgsqlConnection(_connectionString);
    }

    #endregion

}