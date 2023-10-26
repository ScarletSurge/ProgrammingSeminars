using System;
using System.Collections;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Graph:
    IEquatable<Graph>,
    IEnumerable<Vertex>,
    IEnumerable<Edge>
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
    
    /// <summary>
    /// Graph's vertices collection.
    /// </summary>
    private readonly SortedSet<Vertex> _vertices;
    
    /// <summary>
    /// Graph's edges collection.
    /// </summary>
    private readonly SortedSet<Edge> _edges;
    
    /// <summary>
    /// 
    /// </summary>
    public Graph()
    {
        _vertices = new SortedSet<Vertex>();
        _edges = new SortedSet<Edge>();
    }
    
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
            .SingleOrDefault(v => v.Name.Equals(vertexName));

        if (foundVertex is null)
        {
            return false;
        }

        gotVertex = foundVertex;

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
        ref Edge gotEdge)
    {
        var foundEdge = _edges
            .SingleOrDefault(v => v.Name.Equals(edgeName));

        if (foundEdge is null)
        {
            return false;
        }

        gotEdge = foundEdge;

        return true;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    /// <param name="weight"></param>
    /// <param name="verticesNames"></param>
    /// <returns></returns>
    /// <exception cref="ArgumentException"></exception>
    /// <exception cref="InvalidOperationException"></exception>
    public Graph AddEdge(
        string name,
        double weight,
        params string[] verticesNames)
    {
        if (_edges.Any(x => x.Name.Equals(name)))
        {
            throw new ArgumentException($"Edge with name \"{name}\" already exists.", nameof(name));
        }

        var vertices = verticesNames
            .Select(x => _vertices.SingleOrDefault(y => y.Name.Equals(x)))
            .ToArray();

        if (vertices.Any(x => x is null))
        {
            throw new InvalidOperationException("One or more graph's vertices not found.");
        }

        _edges.Add(new Edge(name, weight, vertices!));

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

        return this;
    }
    
    #endregion
    
    #region System.Object overrides

    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"{{graph: vertices = [{string.Join(", ", _vertices)}], edges = [{string.Join(", ", _edges)}]}}";
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
        return _vertices.GetEnumerator();
    }
    
    #endregion
    
    #region System.Collections.Generic.IEnumerable<Edge> implementation
    
    /// <inheritdoc cref="IEnumerable{T}.GetEnumerator" />
    IEnumerator<Edge> IEnumerable<Edge>.GetEnumerator()
    {
        return _edges.GetEnumerator();
    }
    
    #endregion
    
}