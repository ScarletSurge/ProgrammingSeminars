// See https://aka.ms/new-console-template for more information

using System.Text;
using RGU.Minor.GraphTheory.Domain;

try
{
    var graph = new Graph();
    graph.AddVertex("123")
        .AddVertex("234")
        .AddVertex("345")
        .AddVertex("456")
        .AddEdge("edge1", 1.13, "234", "345")
        .AddEdge("edge2", -8.91, "234", "345", "456")
        .AddEdge("edge3", 10, "234", "345", "456", "123")
        .AddVertex("I'm so sad :(");
    graph.RemoveVertex("234", Graph.RemoveVertexStrategy.CascadeDeleteEdges);

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