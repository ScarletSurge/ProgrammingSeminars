using System.Collections.Generic;

namespace Practice.Services.IEnumerableExpander.Core
{
    
    public interface IEnumerableExpander<T>
    {

        IEnumerable<IEnumerable<T>> Expand(IEnumerable<T> enumerable, params object[] parameters);

    }
    
}