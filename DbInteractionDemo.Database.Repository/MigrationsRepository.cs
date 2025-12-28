using Npgsql;
using System.Data;
using System.Text;

using DbInteractionDemo.Core;

namespace DbInteractionDemo.Database.Repository;

/// <summary>
/// 
/// </summary>
public sealed class MigrationsRepository
{

    #region Constants

    /// <summary>
    /// 
    /// </summary>
    private const string TableSchema = "public";

    /// <summary>
    /// 
    /// </summary>
    private const string TableName = "migrations";

    /// <summary>
    /// 
    /// </summary>
    private const string TableNameAlias = "m";

    #endregion

    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private readonly DatabaseConnectionFactory _postgresDcf;

    /// <summary>
    /// 
    /// </summary>
    private readonly DatabaseConnectionFactory _targetDcf;

    /// <summary>
    /// 
    /// </summary>
    private readonly List<(string, string)> _migrationsTexts =
    [
        ("v1.0.1", CreateTableAirlinesQueryBuilder()),
        ("v1.0.2", CreateTableAirlinesQueryBuilder()),
        ("v1.0.3", CreateTableAirlinesQueryBuilder()),
        ("v1.0.4", CreateTableAirlinesQueryBuilder()),
        ("v1.1.0", CreateTableAirlinesQueryBuilder()),
        ("v1.1.1", CreateTableAirlinesQueryBuilder()),
        ("v1.1.2", CreateTableAirlinesQueryBuilder()),
        ("v1.2.0", CreateTableAirlinesQueryBuilder()),
        //("v1.0.2", "CREATE TABLE planes (...)")
    ];

    #endregion

    #region Constructors

    /// <summary>
    /// 
    /// </summary>
    /// <param name="postgresDcf"></param>
    /// <param name="targetDcf"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public MigrationsRepository(
        DatabaseConnectionFactory postgresDcf,
        DatabaseConnectionFactory targetDcf)
    {
        _migrationsTexts = _migrationsTexts;
        _postgresDcf = postgresDcf ?? throw new ArgumentNullException(nameof(postgresDcf));
        _targetDcf = targetDcf ?? throw new ArgumentNullException(nameof(targetDcf));
    }

    #endregion

    #region Methods

    private static string CreateTableAirlinesQueryBuilder()
    {
        return new StringBuilder()
            .Append("CREATE TABLE public.airline")
            .Append("(")
            .Append("id VARCHAR(100) NOT NULL PRIMARY KEY,")
            .Append("full_name VARCHAR(255) NOT NULL,")
            .Append("base_airport_code VARCHAR(16) NOT NULL") // FK
            .Append(");")
            .ToString();
    }

    #endregion

    #region Public API

    /// <summary>
    /// 
    /// </summary>
    /// <param name="query"></param>
    /// <param name="cancellationToken"></param>
    /// <returns></returns>
    public async Task ExecuteQueryAsync(
        string query,
        CancellationToken cancellationToken = default)
    {

    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cancellationToken"></param>
    /// <returns></returns>
    public async Task MigrateAsync(
        CancellationToken cancellationToken = default)
    {
        var targetDatabaseName = new NpgsqlConnectionStringBuilder(_targetDcf.ConnectionString).Database;

        var targetDbExistsQuery = $"SELECT EXISTS(SELECT datname FROM pg_catalog.pg_database WHERE LOWER(datname) = LOWER('{targetDatabaseName}'));";

        await using var postgresConnection = ((IAbstractFactory<NpgsqlConnection>)_postgresDcf).Create();
        await postgresConnection.OpenAsync(cancellationToken);
        await using var targetDbExistsCommand = ((IAbstractFactory<NpgsqlCommand>)_postgresDcf).Create();
        targetDbExistsCommand.Connection = postgresConnection;
        targetDbExistsCommand.CommandType = CommandType.Text;
        targetDbExistsCommand.CommandText = targetDbExistsQuery;
        if (!(bool)await targetDbExistsCommand.ExecuteScalarAsync(cancellationToken))
        {
            var createDatabaseQuery = $"CREATE DATABASE {targetDatabaseName};";

            await using var postgresCommand = ((IAbstractFactory<NpgsqlCommand>)_postgresDcf).Create();

            postgresCommand.Connection = postgresConnection;
            postgresCommand.CommandType = CommandType.Text;
            postgresCommand.CommandText = createDatabaseQuery;

            await postgresCommand.ExecuteNonQueryAsync(cancellationToken);
        }

        {
            var migrationsTableCreateQuery = new StringBuilder()
                .Append($"CREATE TABLE IF NOT EXISTS {TableSchema}.{TableName}")
                .Append("(")
                .Append("version VARCHAR(16) NOT NULL PRIMARY KEY")
                .Append(")")
                .ToString();
            await using var migrationsTableCreateCommand = ((IAbstractFactory<NpgsqlCommand>)_targetDcf).Create();
            await using var targetConnection = ((IAbstractFactory<NpgsqlConnection>)_targetDcf).Create();
            await targetConnection.OpenAsync(cancellationToken);
            migrationsTableCreateCommand.Connection = targetConnection;
            migrationsTableCreateCommand.CommandType = CommandType.Text;
            migrationsTableCreateCommand.CommandText = migrationsTableCreateQuery;
            await migrationsTableCreateCommand.ExecuteNonQueryAsync(cancellationToken);
        }

        {

        }


    }

    #endregion

}