using Npgsql;

using DbInteractionDemo.Core;

namespace DbInteractionDemo.Database.Repository;

/// <summary>
/// 
/// </summary>
public sealed class DatabaseConnectionFactory:
    IAbstractFactory<NpgsqlConnection>
{

    #region DBInteractionDemo.Core.IAbstractFactory<NpgsqlConnection> implementation

    /// <inheritdoc cref="IAbstractFactory{T}.Create" />
    public NpgsqlConnection Create()
    {
        return new NpgsqlConnection("User ID=postgres;Password=postgres;Host=localhost;Port=5432;Database=puksrenjk;");
    }

    #endregion

}