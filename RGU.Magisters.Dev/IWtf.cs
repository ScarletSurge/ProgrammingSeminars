namespace RGU.Magisters.Dev;

public class Wtf : ICpu, IGpu, IRam
{

    public double FrequencyGHz => 4.0;

    public ulong CUDACoresCount => 12345;

    public ulong SizeInGB => 1024;
    
    string ICpu.Producer => Producer;

    string IGpu.Producer => Producer;

    public string Producer => "?!";

    string ICpu.Version => Version;

    string IGpu.Version => Version;

    public string Version => "v1.0.0";

}