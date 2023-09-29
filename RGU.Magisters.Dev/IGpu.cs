namespace RGU.Magisters.Dev;

public interface IGpu
{

    ulong CUDACoresCount { get; }

    string Producer { get; }

    string Version { get; }
    
}