namespace RGU.Magisters.Dev;

public class Compukter : ICompukter
{

    public Compukter(
        ICpu cpu,
        IGpu gpu,
        IRam ram,
        IOperatingSystem operatingSystem)
    {
        Cpu = cpu;
        Gpu = gpu;
        Ram = ram;
        OperatingSystem = operatingSystem;
    }
    
    public ICpu Cpu { get; init; }
    public IGpu Gpu { get; init; }
    public IRam Ram { get; init; }
    public IOperatingSystem OperatingSystem { get; init; }
    
}