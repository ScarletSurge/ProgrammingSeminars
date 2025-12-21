using Npgsql;
using System.Xml;

namespace DbInteractionDemo.Database.Repository;

/// <summary>
/// 
/// </summary>
public sealed class MigrationsRepository
{

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
        ("n1","CREATE TABLE airlines (...)"),
        ("n2","CREATE TABLE planes (...)")
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
        _postgresDcf = _postgresDcf ?? throw new ArgumentNullException(nameof(postgresDcf));
        _targetDcf = targetDcf ?? throw new ArgumentNullException(nameof(targetDcf));
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
    
    // a = (b.operator=(c))

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cancellationToken"></param>
    /// <returns></returns>
    public async Task MigrateAsync(
        CancellationToken cancellationToken = default)
    {
        var sb = new System.Text.StringBuilder();
        sb
            .Append("Где")
            .Append(" Никита")
            .Append(" Демч")
            .Append("енко??!?!")
            .ToString();

        var databaseName = new NpgsqlConnectionStringBuilder(_targetDcf.ConnectionString).Database;

        var query = $"CREATE DATABASE IF NOT EXISTS puksrenjk;";
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="migrationName"></param>
    /// <param name="migrationText"></param>
    public void AddMigration(
        string migrationName,
        string migrationText)
    {

    }

    #endregion

}