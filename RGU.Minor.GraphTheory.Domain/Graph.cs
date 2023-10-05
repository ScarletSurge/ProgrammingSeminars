namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Graph
{
    
    #region Nested

    public enum RemoveVertexStrategy
    {
        CascadeDeleteEdges,
        ThrowAnException
    }
    
    #endregion
    
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
    
    #region Vertex
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexToAdd"></param>
    /// <exception cref="ArgumentNullException"></exception>
    private void AddVertex(
        Vertex vertexToAdd)
    {
        _ = vertexToAdd ?? throw new ArgumentNullException(nameof(vertexToAdd));
        _vertices.Add(vertexToAdd);
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexName"></param>
    /// <returns></returns>
    public Graph AddVertex(
        string vertexName)
    {
        AddVertex(new Vertex(vertexName));
        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexName"></param>
    /// <param name="removeStrategy"></param>
    /// <returns></returns>
    public Graph RemoveVertex(
        string vertexName,
        RemoveVertexStrategy removeStrategy = RemoveVertexStrategy.ThrowAnException)
    {
        var targetVertex = _vertices.SingleOrDefault(x => x.Name == vertexName);
        if (targetVertex is null)
        {
            throw new InvalidOperationException("Can't remove vertex, as it doesn't exist in graph");
        }

        var affectedEdges = new LinkedList<Edge>();
        foreach (var edge in _edges)
        {
            if (edge.Any(edgeVertex => vertexName == edgeVertex.Name))
            {
                if (removeStrategy == RemoveVertexStrategy.ThrowAnException)
                {
                    throw new InvalidOperationException(
                        "Can't remove vertex, as it contains in one or more graph's edges.");
                }

                affectedEdges.AddFirst(edge);
            }       
        }

        foreach (var affectedEdge in affectedEdges)
        {
            _edges.Remove(affectedEdge);
        }

        _vertices.Remove(targetVertex);

        return this;
    }
    
    #endregion
    
    #region Edge

    public Graph AddEdge(
        string edgeName,
        // TODO: add edge weight parameter
        params string[] verticesNames)
    {
        if (_edges.Any(x => x.Name.Equals(edgeName)))
        {
            throw new ArgumentException($"Edge with name \"{edgeName}\" already exists.", nameof(edgeName));
        }

        var vertices = verticesNames
            .Select(x => _vertices.SingleOrDefault(y => y.Name.Equals(x)))
            .ToArray();

        if (vertices.Any(x => x is null))
        {
            throw new InvalidOperationException("One or more graph's vertices not found.");
        }

        _edges.Add(new Edge(edgeName, vertices!));

        return this;
    }

    public Graph RemoveEdge(
        string edgeName)
    {
        var edgeToRemove = _edges.SingleOrDefault(x => x.Name.Equals(edgeName));
        
        if (edgeToRemove is null)
        {
            throw new InvalidOperationException($"Edge with name \"{edgeName}\" doesn't exists.");
        }

        _edges.Remove(edgeToRemove);

        return this;
    }
    
    #endregion
    
    #region System.Object overrides
    
    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"Vertices: [{string.Join(", ", _vertices)}], Edges: [{string.Join(", ", _edges)}]";
    }
    
    #endregion
    
}