using System;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Vertex:
    IEquatable<Vertex>
{
    
    /// <summary>
    /// 
    /// </summary>
    private readonly string _name;
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    public Vertex(
        string name)
    {
        _name = name;
    }
    
    /// <summary>
    /// 
    /// </summary>
    public string Name =>
        _name;
    
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
    
    /// <inheritdoc cref="object.GetHashCode" />
    public override int GetHashCode()
    {
        return _name.GetHashCode();
    }
    
    /// <inheritdoc cref="object.ToString" />
    public override string ToString()
    {
        return $"Vertex with name == \"{_name}\"";
    }
}