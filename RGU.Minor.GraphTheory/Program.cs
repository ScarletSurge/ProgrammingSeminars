// See https://aka.ms/new-console-template for more information

using System.Text;
using RGU.Minor.GraphTheory.Domain;

try
{
    var graph = new Graph();
    graph.AddVertex("123")
        .AddVertex("234")
        .AddVertex("345")
        .AddVertex("456");
    Console.WriteLine(graph);

    if (!graph.RemoveVertex("notfound"))
    {
        Console.WriteLine("Vertex not found!");
    }
    
    Console.WriteLine(graph);
}
catch (ArgumentNullException ex)
{
    Console.WriteLine(ex.Message);
}
catch (ArgumentException ex)
{
    Console.WriteLine(ex.Message);
}

Edge e = new Edge(new Vertex("1"), new Vertex("2"));