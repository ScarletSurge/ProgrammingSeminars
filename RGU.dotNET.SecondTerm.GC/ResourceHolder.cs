namespace RGU.dotNET.SecondTerm.GC;

public sealed class ResourceHolder:
    IDisposable
{
    
    private readonly StreamReader _reader;

    public ResourceHolder(
        string filePath)
    {
        _reader = new StreamReader(new FileStream(filePath, FileMode.Create, FileAccess.Read));
    }

    public void Dispose()
    {
        _reader.Dispose();
        System.GC.SuppressFinalize(this);
    }

    ~ResourceHolder()
    {
        _reader.Dispose();
    }
    
}

public class ResourceHolderHolder:
    IDisposable
{
    private readonly ResourceHolder _field;
    private readonly ResourceHolder _field2;

    public void Dispose()
    {
        _field.Dispose();
    }

    ~ResourceHolderHolder()
    {
        _field.Dispose();
    }
}