namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Vertex:
    IEquatable<Vertex>,
    IComparable,
    IComparable<Vertex>,
    ICloneable
{
    
    #region Fields
    
    /// <summary>
    /// 
    /// </summary>
    private readonly string _name;
    
    #endregion
    
    #region Constructors
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    public Vertex(
        string name)
    {
        _name = name;
    }
    
    #endregion
    
    #region Properties
    
    /// <summary>
    /// 
    /// </summary>
    public string Name =>
        _name;
    
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
        
        if (obj is Vertex vertex)
        {
            return Equals(vertex);
        }

        return false;
    }
    
    /// <inheritdoc cref="object.GetHashCode" />
    public override int GetHashCode()
    {
        return _name.GetHashCode();
    }
    
    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"{{vertex: name = \"{_name}\"}}";
    }
    
    #endregion
    
    #region System.IEquatable<Vertex> implementation
    
    /// <inheritdoc cref="IEquatable{T}.Equals(T?)" />
    public bool Equals(
        Vertex? vertex)
    {
        if (vertex is null)
        {
            return false;
        }

        return _name.Equals(vertex.Name);
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

        if (obj is Vertex vertex)
        {
            return CompareTo(vertex);
        }

        throw new ArgumentException("Can't compare objects", nameof(obj));
    }

    #endregion
    
    #region System.IComparable<Vertex> implementation
    
    /// <inheritdoc cref="IComparable{T}.CompareTo" />
    public int CompareTo(
        Vertex? other)
    {
        if (other is null)
        {
            throw new ArgumentNullException(nameof(other));
        }

        return string.CompareOrdinal(_name , other._name);
    }

    #endregion
    
    #region System.ICloneable implementation

    public object Clone()
    {
        return this;
    }
    
    #endregion

}