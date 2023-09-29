namespace RGU.Magisters.Dev;

public interface ICpu
{

    double FrequencyGHz { get; }

    string Producer { get; }

    string Version { get; }

}