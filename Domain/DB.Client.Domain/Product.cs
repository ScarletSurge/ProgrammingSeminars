namespace DB.Client.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Product
{
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
    public string Barcode
    {
        get;

        set;
    }
    
    /// <summary>
    /// 
    /// </summary>
    public string Name
    {
        get;

        set;
    }
    
    /// <summary>
    /// напиши меня плиз
    /// </summary>
    public string PackageSize
    {
        get;

        set;
    }
    
    /// <summary>
    /// 
    /// </summary>
    public double Weight
    {
        get;

        set;
    }
    
    #endregion
    
}