namespace RGU.Minor.GraphTheory.Domain;

// @scarletsurge

/// <summary>
/// 
/// </summary>
public sealed class Vertex : IEquatable<Vertex>
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

    // public string GetName()
    // {
    //     return _name;
    // }
    
    /// <summary>
    /// 
    /// </summary>
    public string Name =>
        _name;

    public override bool Equals(object? obj)
    {
        if (obj is null)
        {
            return false;
        }

        // Vertex v;
        // if (obj is Vertex)
        // {
        //     v = (Vertex)obj;
        // }
        
        if (obj is Vertex vertex)
        {
            return this.Equals(vertex);
        }

        return false;
    }

    public bool Equals(
        Vertex? vertex)
    {
        if (vertex is null)
        {
            return false;
        }

        return _name.Equals(vertex.Name);
    }

    public override int GetHashCode()
    {
        return _name.GetHashCode();
    }
    
}