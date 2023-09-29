namespace RGU.Magisters.Dev;

public interface IOperatingSystem
{
    
    string Distro { get; }

    string Edition { get; }

    string Producer { get; }

    string Version { get; }
    
}