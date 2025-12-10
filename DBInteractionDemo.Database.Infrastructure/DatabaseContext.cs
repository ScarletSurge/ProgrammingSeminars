using DbInteractionDemo.Database.Data;
using DbInteractionDemo.Database.Repository;
using Npgsql;

namespace DBInteractionDemo.Database.Infrastructure;

/// <summary>
/// 
/// </summary>
public sealed class DatabaseContext
{

    private sealed class IDisposableImpl:
        IDisposable
    {

        private StreamReader _stream;

        public IDisposableImpl()
        {
            _stream = new StreamReader(new FileStream("file.txt", FileMode.Open));
        }

        public void Dispose()
        {
            _stream.Dispose();
            // способ курильщика со стажем 52 года
            //_stream = null;

            GC.SuppressFinalize(this);
        }

        ~IDisposableImpl()
        {
            // if (_stream != null)
            _stream?.Dispose();
        }

    }

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

    public DatabaseContext()
    {

        //using var connection = _connectionFactory();

        // NpgsqlConnection conn = null;
        // try
        // {
        //     conn = _connectionFactory();
        //     conn.Open();
        // 
        // }
        // finally
        // {
        //     // if (conn != null) conn.Close();
        //     conn?.Close(); 
        // }
    }

}
