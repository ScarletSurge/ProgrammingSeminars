namespace RGU.Magisters.Dev;

public interface IRam
{
    ulong SizeInGB { get; }
    
    string Producer { get; }

    string Version { get; }
}