using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.Domain
{
    
    /// <summary>
    /// 
    /// </summary>
    public interface IServiceRegistrator
    {
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="registrator"></param>
        /// <param name="configuration"></param>
        void Register(
            IRegistrator registrator,
            IConfiguration configuration);

    }
    
}