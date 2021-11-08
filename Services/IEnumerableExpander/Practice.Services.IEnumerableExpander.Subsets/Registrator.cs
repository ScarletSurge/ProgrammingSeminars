using DryIoc;
using Microsoft.Extensions.Configuration;

using Practice.DI.Core;
using Practice.Services.IEnumerableExpander.Subsets.Services;

namespace Practice.Services.IEnumerableExpander.Subsets
{
    
    public sealed class Registrator : IPracticeServiceRegistrator
    {

        public void Register(IRegistrator registrator, IConfiguration configuration)
        {
            registrator.Register(typeof(Core.IEnumerableExpander<>), typeof(SubsetsExpander<>));
        }
        
    }
    
}