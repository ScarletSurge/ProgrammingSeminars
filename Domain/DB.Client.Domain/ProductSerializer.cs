namespace DB.Client.Domain;

/// <summary>
/// 
/// </summary>
public static class ProductSerializer
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="product"></param>
    /// <returns></returns>
    /// <exception cref="NotImplementedException"></exception>
    public static MemoryStream Serialize(
        this Product product)
    {
        var stream = new MemoryStream();
        
        // TODO: препад не смог в погромирование((9(9

        return stream;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stream"></param>
    /// <returns></returns>
    public static Product Deserialize(
        this MemoryStream stream)
    {
        var reader = new StreamReader(stream);
        
        // TODO: препад не смог в погромирование((9(9
        
        return new Product();
    }
    
}