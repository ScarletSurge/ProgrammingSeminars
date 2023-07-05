namespace Practice.Domain;

public sealed class MihailGdeLabyComparer:
    IComparer<MihailGdeLaby>
{
    private static MihailGdeLabyComparer? _instance;

    private MihailGdeLabyComparer()
    {
        
    }

    public static MihailGdeLabyComparer Instance =>
        _instance ??= new MihailGdeLabyComparer();
    
    public int Compare(
        MihailGdeLaby? x,
        MihailGdeLaby? y)
    {
        if (ReferenceEquals(x, y)) return 0;
        if (ReferenceEquals(null, y)) return 1;
        if (ReferenceEquals(null, x)) return -1;

        if ((x.IntValue & 1) == 0 && (y.IntValue & 1) == 1)
        {
            return 1;
        }

        if ((x.IntValue & 1) == 1 && (y.IntValue & 1) == 0)
        {
            return -1;
        }
        
        return x.IntValue.CompareTo(y.IntValue);
    }
}