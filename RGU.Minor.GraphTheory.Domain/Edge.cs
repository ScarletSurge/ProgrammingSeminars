using System;
using System.Collections;
using System.Collections.Generic;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Edge:
    IEquatable<Edge>,
    IEnumerable<Vertex>
{
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Vertex[] _vertices;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly string _name;
    
    /// <summary>
    /// Create edge instance from vertices.
    /// </summary>
    /// <param name="name">name of a edge.</param>
    /// <param name="vertices">vertices array.</param>
    /// <exception cref="ArgumentNullException">vertices array is empty.</exception>
    /// <exception cref="ArgumentException">vertices array is empty or any it's component is empty.</exception>
    public Edge(
        string name,
        params Vertex[] vertices)
    {
        _name = name ?? throw new ArgumentNullException(nameof(name));
        _vertices = vertices ?? throw new ArgumentNullException(nameof(vertices));
        
        if (_vertices.Length == 0)
        {
            throw new ArgumentException("Vertices array is empty", nameof(vertices));
        }
        
        if (_vertices.Any(x => x is null))
        {
            throw new ArgumentNullException(nameof(vertices), "Item inside collection is null");
        }

        if (_vertices.Length != _vertices.Distinct().Count())
        {
            throw new ArgumentException("There are some equal vertices inside collection", nameof(vertices));
        }
    }
    
    /// <summary>
    /// Get name of an edge.
    /// </summary>
    public string Name =>
        _name;
    
    /// <summary>
    /// Get first vertex of an edge.
    /// </summary>
    public Vertex FirstVertex =>
        _vertices[0];

    /// <summary>
    /// Get second vertex of an edge; if not exists, returns null.
    /// </summary>
    public Vertex? SecondVertex =>
        _vertices.Length == 1 ? null : _vertices[1];
    
    /// <summary>
    /// 
    /// </summary>
    public int VerticesCount =>
        _vertices.Length;
    
    #region System.Object overrides
    
    /// <inheritdoc cref="object.Equals(object?)" />
    public override bool Equals(
        object? obj)
    {
        if (obj is null)
        {
            return false;
        }

        if (obj is Edge edge)
        {
            return Equals(edge);
        }

        return false;
    }
    
    /// <inheritdoc cref="object.GetHashCode" />
    public override int GetHashCode()
    {
        HashCode result = new HashCode();
        
        result.Add(_name);
        foreach (var vertex in _vertices)
        {
            result.Add(vertex);
        }

        return result.ToHashCode();
    }
    
    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"[{string.Join(", ", _vertices as IEnumerable<Vertex>)}]";
    }

    #endregion
    
    #region IEquatable<Edge>
    
    /// <inheritdoc cref="IEquatable{T}.Equals(T?)" />
    public bool Equals(
        Edge? edge)
    {
        if (edge is null)
        {
            return false;
        }
        
        return _name == edge.Name && _vertices.SequenceEqual(edge._vertices);
    }
    
    #endregion
    
    #region IEnumerable<out Vertex>
    
    /// <inheritdoc cref="IEnumerable.GetEnumerator" />
    public IEnumerator GetEnumerator()
    {
        return _vertices.GetEnumerator();
    }
    
    /// <inheritdoc cref="IEnumerable{T}.GetEnumerator" />
    IEnumerator<Vertex> IEnumerable<Vertex>.GetEnumerator()
    {
        foreach (var vertex in _vertices)
        {
            yield return vertex;
        }
    }
    
    #endregion

}