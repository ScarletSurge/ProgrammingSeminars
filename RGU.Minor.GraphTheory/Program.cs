// See https://aka.ms/new-console-template for more information

using System.Text;
using RGU.Minor.GraphTheory;
using RGU.Minor.GraphTheory.Domain;

try
{
    var graph = new Graph();
    graph.AddVertex("1")
        .AddVertex("2")
        .AddVertex("3")
        .AddVertex("4")
        .AddVertex("5")
        .AddVertex("6")
        .AddVertex("7")
        .AddEdge("edge1", 2.0, Edge.Direction.Bidirectional, "1", "2")
        .AddEdge("edge2", 1.0, Edge.Direction.Bidirectional, "1", "4")
        .AddEdge("edge3",  3.0, Edge.Direction.Bidirectional, "1", "7")
        .AddEdge("edge4", 3.0, Edge.Direction.Bidirectional, "1", "6")
        .AddEdge("edge5", 4.0, Edge.Direction.Bidirectional, "3", "5")
        .AddEdge("edge6", 1.0, Edge.Direction.Bidirectional, "4", "6");
    var paths = DijkstraAlgorithm.Make(graph, "2");
    foreach (var path in paths)
    {
        Console.WriteLine($"Shortest path from \"2\" to \"{path.Key}\" == {path.Value}");
    }

    Console.WriteLine($"Got graph: {graph}");

    var stream = new FileStream("graph.bin", File.Exists("graph.bin")
        ? FileMode.Truncate
        : FileMode.Create);
    
    graph.StoreInto(stream);
    stream.Flush();
    stream.Close();

    stream = new FileStream("graph.bin", FileMode.Open);
    var restoredGraph = GraphExtensions.RestoreFrom(stream);
    stream.Close();

    Console.WriteLine($"{(graph.Equals(restoredGraph.Clone()) ? "E" : "Not e")}quals");
}
catch (ArgumentNullException ex)
{
    Console.WriteLine(ex.Message);
}
catch (ArgumentException ex)
{
    Console.WriteLine(ex.Message);
}