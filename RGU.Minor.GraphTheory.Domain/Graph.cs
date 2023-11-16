using System;
using System.Collections;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Graph:
    IEquatable<Graph>,
    IEnumerable<Vertex>,
    IEnumerable<Edge>,
    ICloneable
{
    
    #region Nested
    
    /// <summary>
    /// 
    /// </summary>
    public enum RemoveVertexStrategy
    {
        /// <summary>
        /// 
        /// </summary>
        CascadeDeleteEdges,
        /// <summary>
        /// 
        /// </summary>
        ThrowAnException
    }
    
    #endregion
    
    #region Fields
    
    /// <summary>
    /// Graph's vertices collection.
    /// </summary>
    private readonly SortedDictionary<Vertex, SortedSet<Edge>> _vertices;
    
    /// <summary>
    /// Graph's edges collection.
    /// </summary>
    private readonly SortedSet<Edge> _edges;
    
    #endregion
    
    #region Constructor
    
    /// <summary>
    /// 
    /// </summary>
    public Graph()
    {
        _vertices = new SortedDictionary<Vertex, SortedSet<Edge>>();
        _edges = new SortedSet<Edge>();
    }
    
    #endregion
    
    #region Vertex
    
    /// <summary>
    /// 
    /// </summary>
    public int VerticesCount =>
        _vertices.Count;
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexName"></param>
    /// <param name="gotVertex"></param>
    /// <returns></returns>
    public bool GetVertex(
        string vertexName,
        ref Vertex gotVertex)
    {
        var foundVertex = _vertices
            .SingleOrDefault(v => v.Key.Name.Equals(vertexName));

        if (foundVertex.Equals(default(KeyValuePair<Vertex, SortedSet<Edge>>)))
        {
            return false;
        }

        gotVertex = foundVertex.Key;

        return true;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexToAdd"></param>
    /// <exception cref="ArgumentNullException"></exception>
    private void AddVertex(
        Vertex vertexToAdd)
    {
        _ = vertexToAdd ?? throw new ArgumentNullException(nameof(vertexToAdd));
        _vertices.Add(vertexToAdd, new SortedSet<Edge>());
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
        var targetVertex = _vertices.SingleOrDefault(x => x.Key.Name == vertexName);
        if (targetVertex.Equals(default(KeyValuePair<Vertex, SortedSet<Edge>>)))
        {
            throw new InvalidOperationException("Can't remove vertex, as it doesn't exist in graph");
        }
        
        if (targetVertex.Value.Count != 0 && removeStrategy == RemoveVertexStrategy.ThrowAnException)
        {
            throw new InvalidOperationException(
                "Can't remove vertex, as it contains in one or more graph's edges.");
        }

        var affectedEdges = new List<Edge>();
        // TODO: this maybe could be done faster
        foreach (var affectedEdge in targetVertex.Value)
        {
            affectedEdges.Add(affectedEdge);
            _edges.Remove(affectedEdge);
        }

        foreach (var vertex in _vertices)
        {
            foreach (var edge in affectedEdges)
            {
                vertex.Value.Remove(edge);
            }
        }

        _vertices.Remove(targetVertex.Key);

        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexName"></param>
    /// <returns></returns>
    public IEnumerable<Edge> GetIncidentEdges(
        string vertexName)
    {
        var vertexByName = default(Vertex);
        if (!GetVertex(vertexName, ref vertexByName))
        {
            throw new ArgumentException($"Vertex with name \"{vertexByName}\" not exist in graph", nameof(vertexName));
        }

        return _vertices[vertexByName];
    }
    
    #endregion
    
    #region Edge
    
    /// <summary>
    /// 
    /// </summary>
    public int EdgesCount =>
        _edges.Count;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="edgeName"></param>
    /// <param name="gotEdge"></param>
    /// <returns></returns>
    public bool GetEdge(
        string edgeName,
        out Edge? gotEdge)
    {
        var foundEdge = _edges
            .SingleOrDefault(v => v.Name.Equals(edgeName));

        if (foundEdge is null)
        {
            gotEdge = null;
            return false;
        }

        gotEdge = foundEdge;

        return true;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="edgeToAdd"></param>
    /// <exception cref="ArgumentException"></exception>
    /// <exception cref="InvalidOperationException"></exception>
    private void AddEdge(
        Edge edgeToAdd)
    {
        if (GetEdge(edgeToAdd.Name, out _))
        {
            throw new ArgumentException($"Edge with name \"{edgeToAdd.Name}\" already exists.", nameof(edgeToAdd));
        }

        if (edgeToAdd.Any(x => x is null))
        {
            throw new InvalidOperationException("One or more graph's vertices not found.");
        }

        _edges.Add(edgeToAdd);
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    /// <param name="weight"></param>
    /// <param name="direction"></param>
    /// <param name="verticesNames"></param>
    /// <returns></returns>
    /// <exception cref="ArgumentException"></exception>
    /// <exception cref="InvalidOperationException"></exception>
    public Graph AddEdge(
        string name,
        double weight,
        Edge.Direction direction = Edge.Direction.Bidirectional,
        params string[] verticesNames)
    {
        var edgeVertices = verticesNames
            .Select(vertexName => _vertices.SingleOrDefault(vertex => vertex.Key.Name.Equals(vertexName)))
            .ToArray();
        var addedEdge = new Edge(name, weight, direction, edgeVertices.Select(vertex => vertex.Key).ToArray());
        AddEdge(addedEdge);
        foreach (var vertex in edgeVertices)
        {
            vertex.Value.Add(addedEdge);
        }
        
        return this;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="edgeName"></param>
    /// <returns></returns>
    /// <exception cref="InvalidOperationException"></exception>
    public Graph RemoveEdge(
        string edgeName)
    {
        var edgeToRemove = _edges.SingleOrDefault(x => x.Name.Equals(edgeName));
        
        if (edgeToRemove is null)
        {
            throw new InvalidOperationException($"Edge with name \"{edgeName}\" doesn't exists.");
        }

        _edges.Remove(edgeToRemove);
        foreach (var vertex in _vertices)
        {
            vertex.Value.Remove(edgeToRemove);
        }

        return this;
    }
    
    #endregion
    
    #region System.Object overrides

    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"{{graph: vertices = [{string.Join(", ", this as IEnumerable<Vertex>)}], edges = [{string.Join(", ", _edges)}]}}";
    }
    
    /// <inheritdoc cref="object.Equals(object?)" />
    public override bool Equals(
        object? obj)
    {
        if (obj is null)
        {
            return false;
        }

        if (obj is Graph graph)
        {
            return Equals(graph);
        }

        return false;
    }
    
    /// <inheritdoc cref="object.GetHashCode" />
    public override int GetHashCode()
    {
        var result = new HashCode();
        
        foreach (var vertex in _vertices)
        {
            result.Add(vertex);
        }

        foreach (var edge in _edges)
        {
            result.Add(edge);
        }

        return result.ToHashCode();
    }

    #endregion
    
    #region System.IEquatable<Graph> implementation
    
    /// <inheritdoc cref="IEquatable{T}.Equals(T?)" />
    public bool Equals(
        Graph? other)
    {
        if (other is null)
        {
            return false;
        }

        return _vertices.SequenceEqual(other._vertices) && _edges.SequenceEqual(other._edges);
    }

    #endregion
    
    #region System.Collections.IEnumerable implementation
    
    /// <inheritdoc cref="GetEnumerator" />
    public IEnumerator GetEnumerator()
    {
        foreach (var vertex in this as IEnumerable<Vertex>)
        {
            yield return vertex;
        }
        
        foreach (var edge in this as IEnumerable<Edge>)
        {
            yield return edge;
        }
    }
    
    #endregion
    
    #region System.Collections.Generic.IEnumerable<Vertex> implementation
    
    /// <inheritdoc cref="IEnumerable{T}.GetEnumerator" />
    IEnumerator<Vertex> IEnumerable<Vertex>.GetEnumerator()
    {
        foreach (var vertex in _vertices)
        {
            yield return vertex.Key;
        }
    }
    
    #endregion
    
    #region System.Collections.Generic.IEnumerable<Edge> implementation
    
    /// <inheritdoc cref="IEnumerable{T}.GetEnumerator" />
    IEnumerator<Edge> IEnumerable<Edge>.GetEnumerator()
    {
        return _edges.GetEnumerator();
    }
    
    #endregion
    
    #region System.ICloneable implementation

    public object Clone()
    {
        var clonedGraph = new Graph();

        foreach (var vertex in this as IEnumerable<Vertex>)
        {
            clonedGraph.AddVertex((Vertex)vertex.Clone());
        }

        foreach (var edge in this as IEnumerable<Edge>)
        {
            clonedGraph.AddEdge((Edge)edge.Clone());
        }

        return clonedGraph;
    }
    
    #endregion
    
}