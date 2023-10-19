namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public static class GraphExtensions
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="graphToStore"></param>
    /// <param name="stream"></param>
    public static void StoreInto(
        this Graph? graphToStore,
        Stream stream)
    {
        _ = graphToStore ?? throw new ArgumentNullException(nameof(graphToStore));
        
        stream.Write(BitConverter.GetBytes(graphToStore.VerticesCount));
        foreach (var vertex in graphToStore as IEnumerable<Vertex>)
        {
            vertex.Name.ToStream(stream);
        }
        
        stream.Write(BitConverter.GetBytes(graphToStore.EdgesCount));
        foreach (var edge in graphToStore as IEnumerable<Edge>)
        {
            edge.Name.ToStream(stream);
            stream.Write(BitConverter.GetBytes(edge.VerticesCount));
            foreach (var vertex in edge)
            {
                vertex.Name.ToStream(stream);
            }
        }
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stream"></param>
    /// <returns></returns>
    public static Graph RestoreFrom(
        MemoryStream stream)
    {
        throw new NotImplementedException();
    }

}