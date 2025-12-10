namespace DbInteractionDemo.Database.Data;

/// <summary>
/// 
/// </summary>
public sealed class Airport
{

    /// <summary>
    /// 
    /// </summary>
    public string Code
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public string FullName
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public string Country
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    public string City
    {
        get;

        set;
    }

    /// <summary>
    /// 
    /// </summary>
    private int _utcOffset;

    /// <summary>
    /// 
    /// </summary>
    public int UTCOffset
    {
        get =>
            _utcOffset;

        set
        {
            if (Math.Abs(value) > 12)
            {
                throw new ArgumentOutOfRangeException("Invalid UTC offset value provided");
            }

            _utcOffset = value;
        }
    }

    /// <summary>
    /// количество ВПП
    /// </summary>
    public uint AirstripsCount
    {
        get;

        set;
    }

}

// Code first (Entity first) (сначала код на ЯП, дальше обмазать SQLем)
// Database first 