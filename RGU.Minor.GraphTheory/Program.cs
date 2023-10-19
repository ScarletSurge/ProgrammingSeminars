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
        .AddEdge("edge1", "234", "345")
        .AddEdge("edge2", "234", "345", "456");
        //.RemoveVertex("234", Graph.RemoveVertexStrategy.CascadeDeleteEdges);

    Console.WriteLine($"Got graph: {graph}");

    var stream = new FileStream("graph.bin", File.Exists("graph.bin")
        ? FileMode.Truncate
        : FileMode.Create);
    
    graph.StoreInto(stream);
    stream.Flush();
}
catch (ArgumentNullException ex)
{
    Console.WriteLine(ex.Message);
}
catch (ArgumentException ex)
{
    Console.WriteLine(ex.Message);
}

Edge e = new Edge("I'm an edge!", new Vertex("1"), new Vertex("2"));