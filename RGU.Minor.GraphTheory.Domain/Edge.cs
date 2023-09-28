namespace RGU.Minor.GraphTheory.Domain;

/// <summary>
/// 
/// </summary>
public sealed class Edge
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

        // int i = 0;
        // foreach (var item in _vertices)
        // {
        //     if (item == null)
        //     {
        //         throw new ArgumentNullException($"{vertices}[{i}]");
        //     } // System.AggregateException
        //     
        //     i++;
        // }

        if (_vertices.Any(x => x is null))
        {
            throw new ArgumentNullException(nameof(vertices), "Item inside collection is null");
        }

        if (_vertices.Length != _vertices.Distinct().Count())
        {
            throw new ArgumentException("There are some equal vertices inside collection", nameof(vertices));
        }
    }
    
    

}