using System.Collections;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Edge:
    IEquatable<Edge>,
    IComparable,
    IComparable<Edge>,
    IEnumerable<Vertex>
{
    
    #region Constants
    
    /// <summary>
    /// 
    /// </summary>
    private const double Epsilon = 1e-9;
    
    #endregion
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly SortedSet<Vertex> _vertices;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly string _name;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly double _weight;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// Create edge instance from vertices.
    /// </summary>
    /// <param name="name">name of the edge.</param>
    /// <param name="weight">weight of the edge instance.</param>
    /// <param name="vertices">vertices array contained by the edge instance.</param>
    /// <exception cref="ArgumentNullException">vertices array is empty.</exception>
    /// <exception cref="ArgumentException">vertices array is empty or any it's component is empty.</exception>
    public Edge(
        string name,
        double weight,
        params Vertex[] vertices)
    {
        _name = name ?? throw new ArgumentNullException(nameof(name));
        _weight = weight;
        _ = vertices ?? throw new ArgumentNullException(nameof(vertices));
        _vertices = new SortedSet<Vertex>(vertices);
        
        if (_vertices.Count == 0)
        {
            throw new ArgumentException("Vertices array is empty", nameof(vertices));
        }
        
        if (_vertices.Any(x => x is null))
        {
            throw new ArgumentNullException(nameof(vertices), "Item inside collection is null");
        }

        if (_vertices.Count != _vertices.Distinct().Count())
        {
            throw new ArgumentException("There are some equal vertices inside collection", nameof(vertices));
        }
    }
    
    #endregion
    
    #region Properties
    
    /// <summary>
    /// Get name of the edge.
    /// </summary>
    public string Name =>
        _name;
    
    /// <summary>
    /// Get weight of the edge.
    /// </summary>
    public double Weight =>
        _weight;
    
    /// <summary>
    /// 
    /// </summary>
    public int VerticesCount =>
        _vertices.Count;
    
    #endregion
    
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
        var result = new HashCode();
        
        result.Add(_name);
        result.Add(_weight);
        foreach (var vertex in _vertices)
        {
            result.Add(vertex);
        }

        return result.ToHashCode();
    }
    
    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"{{edge: name = \"{_name}\", weight = {_weight}, vertices = [{string.Join(", ", _vertices as IEnumerable<Vertex>)}]}}";
    }

    #endregion
    
    #region System.IEquatable<out Edge> implementation
    
    /// <inheritdoc cref="IEquatable{T}.Equals(T?)" />
    public bool Equals(
        Edge? edge)
    {
        if (edge is null)
        {
            return false;
        }
        
        return _name == edge.Name && Math.Abs(_weight - edge.Weight) < Epsilon &&
            _vertices.SequenceEqual(edge._vertices);
    }
    
    #endregion
    
    #region System.IComparable implementation
    
    /// <inheritdoc cref="IComparable.CompareTo" />
    public int CompareTo(
        object? obj)
    {
        if (obj is null)
        {
            throw new ArgumentNullException(nameof(obj));
        }

        if (obj is Edge edge)
        {
            return CompareTo(edge);
        }

        throw new ArgumentException("Can't compare objects", nameof(obj));
    }

    #endregion
    
    #region System.IComparable<Edge> implementation
    
    /// <inheritdoc cref="IComparable{T}.CompareTo" />
    public int CompareTo(
        Edge? other)
    {
        if (other is null)
        {
            throw new ArgumentNullException(nameof(other));
        }

        var comparisonResult = string.CompareOrdinal(_name , other._name);
        if (comparisonResult != 0)
        {
            return comparisonResult;
        }

        comparisonResult = _vertices.Count.CompareTo(other._vertices.Count);
        if (comparisonResult != 0)
        {
            return comparisonResult;
        }
        
        using var thisEnumerator = _vertices.GetEnumerator();
        using var otherEnumerator = other.GetEnumerator();
        while (true)
        {
            var thisVertex = thisEnumerator.Current;
            var otherVertex = otherEnumerator.Current;

            comparisonResult = thisVertex.CompareTo(otherVertex);
            if (comparisonResult != 0)
            {
                return comparisonResult;
            }

            thisEnumerator.MoveNext();
            if (!otherEnumerator.MoveNext())
            {
                break;
            }
        }

        var weightsDifference = _weight - other._weight;
        if (weightsDifference < -Epsilon)
        {
            // TODO: think about it
            return -1;
        }

        return Math.Abs(weightsDifference) < Epsilon
            ? 0
            : 1;
    }

    #endregion
    
    #region System.Collections.IEnumerable implementation
    
    /// <inheritdoc cref="IEnumerable.GetEnumerator" />
    IEnumerator IEnumerable.GetEnumerator()
    {
        return _vertices.GetEnumerator();
    }
    
    #endregion
    
    #region System.Collections.Generic.IEnumerable<out Vertex> implementation

    /// <inheritdoc cref="IEnumerable{T}.GetEnumerator" />
    public IEnumerator<Vertex> GetEnumerator()
    {
        foreach (var vertex in _vertices)
        {
            yield return vertex;
        }
    }
    
    #endregion

}