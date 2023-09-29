namespace RGU.Magisters.Dev;

public interface ICompukter
{
    
    ICpu Cpu { get; }
    
    IGpu Gpu { get; }
    
    IRam Ram { get; }

    IOperatingSystem OperatingSystem { get; }

}