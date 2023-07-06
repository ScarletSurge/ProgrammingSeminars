namespace Practice.Domain;

public static class EnumerableExtensions
{
    public static IEnumerable<int> DivideBy2(
        this IEnumerable<int> collection)
    {
        foreach (var item in collection)
        {
            yield return item / 2;
        }
    }
}