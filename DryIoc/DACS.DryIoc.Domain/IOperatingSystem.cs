namespace DACS.DryIoc.Domain
{

    /// <summary>
    /// 
    /// </summary>
    public interface IOperatingSystem
    {

        string Producer { get; }

        string Name { get; }

        string Version { get; }

        BitDepth BitDepth { get; }

    }
    
}