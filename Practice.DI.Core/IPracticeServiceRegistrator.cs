using DryIoc;
using Microsoft.Extensions.Configuration;

namespace Practice.DI.Core
{
    
    public interface IPracticeServiceRegistrator
    {

        void Register(IRegistrator registrator, IConfiguration configuration);

    }
    
}