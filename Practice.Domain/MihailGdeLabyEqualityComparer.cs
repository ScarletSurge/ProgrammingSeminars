namespace Practice.Domain;

public class MihailGdeLabyEqualityComparer:
    IEqualityComparer<MihailGdeLaby>
{
    private static MihailGdeLabyEqualityComparer? _instance;

    private MihailGdeLabyEqualityComparer()
    {
        
    }

    public static MihailGdeLabyEqualityComparer Instance =>
        _instance ??= new MihailGdeLabyEqualityComparer();
    
    public bool Equals(
        MihailGdeLaby? x,
        MihailGdeLaby? y)
    {
        if (ReferenceEquals(x, y)) return true;
        if (ReferenceEquals(x, null)) return false;
        if (ReferenceEquals(y, null)) return false;
        if (x.GetType() != y.GetType()) return false;
        return x.StringValue.Equals(y.StringValue, StringComparison.Ordinal);
    }

    public int GetHashCode(
        MihailGdeLaby obj)
    {
        return obj.StringValue.GetHashCode();
    }
}