using DbInteractionDemo.Database.Data;
using DbInteractionDemo.Database.Repository;

namespace DBInteractionDemo.Database.Infrastructure;

/// <summary>
/// 
/// </summary>
public sealed class DatabaseContextFacade
{

    /// <summary>
    /// 
    /// </summary>
    private MigrationsRepository _migrationsRepository;

    /// <summary>
    /// 
    /// </summary>
    private AirlineRepository _airlines;
    
    /// <summary>
    /// 
    /// </summary>
    private IQueryable<Airport> _airports;
    
    /// <summary>
    /// 
    /// </summary>
    private IEnumerable<Flight> _flights;
    
    /// <summary>
    /// 
    /// </summary>
    private IEnumerable<Plane> _planes;

    #region Constructors

    /// <summary>
    /// 
    /// </summary>
    /// <param name="postgresDcf"></param>
    /// <param name="targetDcf"></param>
    public DatabaseContextFacade(
        DatabaseConnectionFactory postgresDcf,
        DatabaseConnectionFactory targetDcf)
    {
        _migrationsRepository = new MigrationsRepository(postgresDcf, targetDcf);
        _airlines = new AirlineRepository(targetDcf);
        // TODO: other repositories initialization o_O
    }

    #endregion

    #region Properties

    /// <summary>
    /// 
    /// </summary>
    public MigrationsRepository MigrationsRepository
    {
        get =>
            _migrationsRepository;
    }

    #endregion

    #region Methods

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cancellationToken"></param>
    /// <returns></returns>
    public Task MigrateAsync(
        CancellationToken cancellationToken = default)
    {
        return _migrationsRepository.MigrateAsync(cancellationToken);
    }

    #endregion

}
