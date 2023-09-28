using System.Collections;

namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Edge:
    IEnumerable<Vertex>
{
    
    /// <summary>
    /// 
    /// </summary>
    private readonly Vertex[] _vertices;
    
    /// <summary>
    /// Create edge instance from vertices.
    /// </summary>
    /// <param name="vertices">vertices array.</param>
    /// <exception cref="ArgumentNullException">vertices array is empty.</exception>
    /// <exception cref="ArgumentException">vertices array is empty or any it's component is empty.</exception>
    public Edge(
        params Vertex[] vertices)
    {
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

    public IEnumerator GetEnumerator()
    {
        return _vertices.GetEnumerator();
    }

    IEnumerator<Vertex> IEnumerable<Vertex>.GetEnumerator()
    {
        foreach (var vertex in _vertices)
        {
            yield return vertex;
        }
    }

}