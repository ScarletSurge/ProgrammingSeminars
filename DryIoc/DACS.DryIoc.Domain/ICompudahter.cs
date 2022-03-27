namespace DACS.DryIoc.Domain
{
    
    /// <summary>
    /// 
    /// </summary>
    public interface ICompudahter
    {
        
        /// <summary>
        /// 
        /// </summary>
        ICpu Cpu { get; }
        
        /// <summary>
        /// 
        /// </summary>
        IOperatingSystem OperatingSystem { get; }
        
        /// <summary>
        /// 
        /// </summary>
        void PowerOn();
        
        /// <summary>
        /// 
        /// </summary>
        void PowerOff();

    }
    
}