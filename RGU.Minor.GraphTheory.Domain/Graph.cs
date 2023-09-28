namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Graph
{
    
    /// <summary>
    /// Graph's vertices collection.
    /// </summary>
    private HashSet<Vertex> _vertices;
    
    /// <summary>
    /// Graph's edges collection.
    /// </summary>
    private HashSet<Edge> _edges;
    
    /// <summary>
    /// 
    /// </summary>
    public Graph()
    {
        _vertices = new HashSet<Vertex>();
        _edges = new HashSet<Edge>();
    }

    private void AddVertex(
        Vertex? vertexToAdd)
    {
        _ = vertexToAdd ?? throw new ArgumentNullException(nameof(vertexToAdd));
        _vertices.Add(vertexToAdd);
    }

    public Graph AddVertex(
        string vertexName)
    {
        AddVertex(new Vertex(vertexName));
        return this;
    }

    public bool RemoveVertex(
        string vertexName)
    {
        return _vertices.Remove(new Vertex(vertexName));
    }

    public override string ToString()
    {
        return $"Vertices: [{string.Join(", ", _vertices)}], Edges: []";
    }
    
}