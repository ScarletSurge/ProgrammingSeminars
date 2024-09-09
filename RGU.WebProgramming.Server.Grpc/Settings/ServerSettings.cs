namespace RGU.WebProgramming.Server.Grpc.Settings;

/// <summary>
/// 
/// </summary>
public sealed class ServerSettings
{
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
    public string ListenAddress
    {
        get;

        set;
    }
    
    /// <summary>
    /// 
    /// </summary>
    public ushort ListenPort
    {
        get;

        set;
    }
    
    /// <summary>
    /// 
    /// </summary>
    public string CertPath
    {
        get;

        set;
    }
    
    /// <summary>
    /// 
    /// </summary>
    public string CertPassword
    {
        get;

        set;
    }
    
    #endregion
    
}