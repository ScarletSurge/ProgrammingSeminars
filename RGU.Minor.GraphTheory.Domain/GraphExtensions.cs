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
            edge.Weight.ToStream(stream);
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
        Stream stream)
    {
        var restoredGraph = new Graph();
        
        var intBytes = new byte[sizeof(int)];
        
        stream.Read(intBytes, 0, sizeof(int));
        var verticesCount = BitConverter.ToInt32(intBytes, 0);
        for (var i = 0; i < verticesCount; i++)
        {
            restoredGraph.AddVertex(stream.StringFromStream());
        }
        
        stream.Read(intBytes, 0, sizeof(int));
        var edgesCount = BitConverter.ToInt32(intBytes, 0);
        for (var i = 0; i < edgesCount; i++)
        {
            var edgeName = stream.StringFromStream();
            var edgeWeight = stream.DoubleFromStream();
            stream.Read(intBytes, 0, sizeof(int));
            verticesCount = BitConverter.ToInt32(intBytes, 0);
            var edgeVerticesNames = new string[verticesCount];
            
            for (var j = 0; j < verticesCount; j++)
            {
                edgeVerticesNames[j] = stream.StringFromStream();
            }

            restoredGraph.AddEdge(edgeName, edgeWeight, edgeVerticesNames);
        }

        return restoredGraph;
    }

}