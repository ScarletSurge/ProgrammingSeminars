namespace RGU.Magisters.Dev;

public class NVidiaGpu : IGpu
{
    public ulong CUDACoresCount => 3000;
    public string Producer => "NVidia";
    public string Version => "RTX 3060";
}