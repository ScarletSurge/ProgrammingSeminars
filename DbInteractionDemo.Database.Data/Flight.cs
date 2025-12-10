namespace DbInteractionDemo.Database.Data;

/// <summary>
/// 
/// </summary>
public sealed class Flight
{

    /// <summary>
    /// 
    /// </summary>
    public int FlightId
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public int PlaneRegistrationId
    {
        get;

        set;
    }

    /// <summary>
    /// пук среньк
    /// </summary>
    public string DepartureAirportCode
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public string ArrivalAirportCode
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public DateTime Departure
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public TimeSpan PlannedFlightTime
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public string WebSite
    {
        get;

        set;
    }

}