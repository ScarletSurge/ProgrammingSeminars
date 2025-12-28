using Npgsql;

using DbInteractionDemo.Core;

namespace DbInteractionDemo.Database.Repository;

/// <summary>
/// 
/// </summary>
public sealed class DatabaseConnectionFactory:
    IAbstractFactory<NpgsqlConnection>,
    IAbstractFactory<NpgsqlCommand>
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
    NpgsqlConnection IAbstractFactory<NpgsqlConnection>.Create()
    {
        return new NpgsqlConnection(_connectionString);
        // TODO: open async may be placed here...
    }

    #endregion

    #region DBInteractionDemo.Core.IAbstractFactory<NpgsqlConnection> implementation

    /// <inheritdoc cref="IAbstractFactory{T}.Create" />
    NpgsqlCommand IAbstractFactory<NpgsqlCommand>.Create()
    {
        return new NpgsqlCommand();
    }

    #endregion

}