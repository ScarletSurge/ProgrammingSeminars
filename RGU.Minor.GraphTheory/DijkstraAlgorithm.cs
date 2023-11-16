using System.Collections.ObjectModel;
using RGU.Minor.GraphTheory.Domain;

namespace RGU.Minor.GraphTheory;

/// <summary>
/// 
/// </summary>
public static class DijkstraAlgorithm
{
    
    #region Constants

    private const double Epsilon = 1e-9;
    
    #endregion
    
    #region Methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="targetGraph"></param>
    /// <param name="vertexName"></param>
    /// <returns></returns>
    /// <exception cref="ArgumentNullException"></exception>
    /// <exception cref="ArgumentException"></exception>
    public static IReadOnlyDictionary<string, double> Make(
        Graph? targetGraph,
        string? vertexName)
    {
        _ = targetGraph ?? throw new ArgumentNullException(nameof(targetGraph));
        _ = vertexName ?? throw new ArgumentNullException(nameof(vertexName));
        
        // TODO: additional validation

        var targetVertex = default(Vertex);
        if (!targetGraph.GetVertex(vertexName, ref targetVertex))
        {
            throw new ArgumentException($"Vertex with name \"{targetVertex}\" not exist in graph", nameof(vertexName));
        }
        
        IDictionary<Vertex, double> pathsWeights = new Dictionary<Vertex, double>();

        foreach (var vertex in targetGraph as IEnumerable<Vertex>)
        {
            pathsWeights.Add(vertex, ReferenceEquals(targetVertex, vertex)
                ? 0
                : -1);
        }

        Make(targetGraph, targetVertex, pathsWeights);

        return new ReadOnlyDictionary<string, double>(pathsWeights.ToDictionary(kvp => kvp.Key.Name, kvp => kvp.Value));
    }

    private static void Make(
        Graph targetGraph,
        Vertex targetVertex,
        IDictionary<Vertex, double> pathsWeights)
    {
        var shortenedWeightsVertices = new HashSet<Vertex>();
        
        foreach (var incidentEdge in targetGraph.GetIncidentEdges(targetVertex.Name))
        {
            var notTargetVertex = incidentEdge.First();
            if (ReferenceEquals(notTargetVertex, targetVertex))
            {
                notTargetVertex = incidentEdge.Last();
            }

            var currentWeight = pathsWeights[notTargetVertex!];

            if (Math.Abs(currentWeight + 1) < Epsilon ||
                pathsWeights[targetVertex] + incidentEdge.Weight - currentWeight < -Epsilon)
            {
                pathsWeights[notTargetVertex!] = pathsWeights[targetVertex] + incidentEdge.Weight;

                shortenedWeightsVertices.Add(notTargetVertex!);
            }
        }

        foreach (var vertex in shortenedWeightsVertices)
        {
            Make(targetGraph, vertex, pathsWeights);
        }
    }
    
    #endregion
    
}