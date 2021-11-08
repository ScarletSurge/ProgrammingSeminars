using System;
using System.Collections.Generic;
using System.Linq;

using Practice.Services.IEnumerableExpander.Core;

namespace Practice.Services.IEnumerableExpander.Subsets.Services
{
    
    public sealed class SubsetsExpander<T> : IEnumerableExpander<T>
    {
        
        public IEnumerable<IEnumerable<T>> Expand(IEnumerable<T> enumerable, params object[] parameters)
        {
            if (parameters.Length != 1)
            {
                throw new ArgumentException(nameof(parameters));
            }

            if (!(parameters[0] is IEqualityComparer<T> equalityComparer))
            {
                throw new ArgumentException(nameof(parameters));
            }

            if (enumerable.Distinct(equalityComparer).Count() != enumerable.Count())
            {
                throw new ArgumentException("In array detected equals elements");
            }
            
            var ret = new List<IEnumerable<T>>();

            int k = enumerable.Count();

            for (int dim = 2; dim <= k; dim++)
            for (int i = 0; i < enumerable.Count() - 1; i++)
            {
                T it = enumerable.ElementAt(i);

                T[] comb = new T[dim];

                int iter = 0;
                ret.Add(new T[] { it });

                for (int j = i; j < enumerable.Count(); j++)
                {
                    if ((iter + 1) % dim == 0)
                    {
                        iter = 0;
                        comb[dim - 1] = it;
                        ret.Add(comb);
                    }
                    comb[iter++] = enumerable.ElementAt(j);
                }
            }

            return ret;
        }
        
    }
    
}