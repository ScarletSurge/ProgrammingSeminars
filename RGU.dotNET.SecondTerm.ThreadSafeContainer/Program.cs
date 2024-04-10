using RGU.dotNET.SecondTerm.ThreadSafeContainer;

for (var i = 0; i < 1000; i++)
{
    try
    {
        var container = new ThreadSafeContainer<string>();

        Parallel.For(0, 1000, i => { container.Add(i.ToString()); });

        Console.WriteLine(container.Length == 1000);
    }
    catch (Exception ex)
    {
        Console.WriteLine("Operation failed");
    }
}