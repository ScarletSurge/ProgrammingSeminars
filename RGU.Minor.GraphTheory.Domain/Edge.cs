using System.Collections;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Edge:
    IEquatable<Edge>,
    IComparable,
    IComparable<Edge>,
    IEnumerable<Vertex?>,
    ICloneable
{
    
    #region Nested
    
    /// <summary>
    /// 
    /// </summary>
    public enum Direction
    {
        /// <summary>
        /// 
        /// </summary>
        FromFirstToSecond,
        /// <summary>
        /// 
        /// </summary>
        FromSecondToFirst,
        /// <summary>
        /// 
        /// </summary>
        Bidirectional
    }
    
    #endregion
    
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
    private readonly string _name;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly SortedSet<Vertex> _vertices;

    /// <summary>
    /// 
    /// </summary>
    private readonly double _weight;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Direction _direction;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// Create edge instance from vertices.
    /// </summary>
    /// <param name="name">name of the edge.</param>
    /// <param name="weight">weight of the edge instance.</param>
    /// <param name="direction">direction of the edge instance.</param>
    /// <param name="vertices">vertices array contained by the edge instance.</param>
    /// <exception cref="ArgumentNullException">vertices array is empty.</exception>
    /// <exception cref="ArgumentException">vertices array is empty or any it's component is empty.</exception>
    public Edge(
        string name,
        double weight,
        Direction direction = Direction.Bidirectional,
        params Vertex?[] vertices)
    {
        _name = name ?? throw new ArgumentNullException(nameof(name));
        _weight = weight;
        _direction = direction;
        _ = vertices ?? throw new ArgumentNullException(nameof(vertices));

        if (vertices.Length == 0)
        {
            throw new ArgumentException("Vertices array is empty", nameof(vertices));
        }
        
        if (vertices.Any(x => x is null))
        {
            throw new ArgumentNullException(nameof(vertices), "Item inside collection is null");
        }

        if (vertices.Length != vertices.Distinct().Count())
        {
            throw new ArgumentException("There are some equal vertices inside collection", nameof(vertices));
        }
        
        _vertices = new SortedSet<Vertex>(vertices!);
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
    public Direction EdgeDirection =>
        _direction;
    
    /// <summary>
    /// 
    /// </summary>
    public int VerticesCount =>
        _vertices.Count;
    
    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="direction"></param>
    /// <returns></returns>
    private static string DirectionToString(
        Direction direction)
    {
        return direction switch
        {
            Direction.Bidirectional => "Bidirectional",
            Direction.FromFirstToSecond => "FromFirstToSecond",
            Direction.FromSecondToFirst => "FromSecondToFirst",
            _ => throw new ArgumentOutOfRangeException(nameof(direction))
        };
    }
    
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
        result.Add(_direction);
        foreach (var vertex in _vertices)
        {
            result.Add(vertex);
        }

        return result.ToHashCode();
    }
    
    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"{{edge: name = \"{_name}\", weight = {_weight}, direction = {DirectionToString(_direction)} vertices = [{string.Join(", ", _vertices)}]}}";
    }

    #endregion
    
    #region System.IEquatable<Edge> implementation
    
    /// <inheritdoc cref="IEquatable{T}.Equals(T?)" />
    public bool Equals(
        Edge? edge)
    {
        if (edge is null)
        {
            return false;
        }
        
        return _name == edge.Name
               && Math.Abs(_weight - edge.Weight) < Epsilon
               && _vertices.SequenceEqual(edge._vertices)
               && _direction == edge.EdgeDirection;
    }
    
    #endregion
    
    #region System.IComparable implementation
    
    /// <inheritdoc cref="IComparable.CompareTo" />
    public int CompareTo(
        object? obj)
    {
        return obj switch
        {
            null => throw new ArgumentNullException(nameof(obj)),
            Edge edge => CompareTo(edge),
            _ => throw new ArgumentException("Can't compare objects", nameof(obj))
        };
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
        
        if (ReferenceEquals(this, other))
        {
            return 0;
        }

        var comparisonResult = _direction.CompareTo(other._direction);
        if (comparisonResult != 0)
        {
            throw new InvalidOperationException("Can't compare edges with different directions");
        }

        comparisonResult = string.CompareOrdinal(_name , other._name);
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
    
    #region System.ICloneable implementation

    public object Clone()
    {
        return this;
    }
    
    #endregion
    
}