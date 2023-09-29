namespace RGU.Magisters.Dev;

public class SamsungRam : IRam
{
    public ulong SizeInGB => 16;
    public string Producer => "Samsung";
    public string Version => "2.1";
}