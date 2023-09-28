// See https://aka.ms/new-console-template for more information

using RGU.Minor.GraphTheory.Domain;

try
{
    var edge = new Edge(new Vertex[] { new Vertex("123"), new Vertex("456") });
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