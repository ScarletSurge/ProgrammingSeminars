namespace DACS.DryIoc.Domain
{
    
    /// <summary>
    /// 
    /// </summary>
    public interface IAnimal
    {
        
        /// <summary>
        /// 
        /// </summary>
        int LegsCount { get; }
        
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        string Voice();

    }
    
}