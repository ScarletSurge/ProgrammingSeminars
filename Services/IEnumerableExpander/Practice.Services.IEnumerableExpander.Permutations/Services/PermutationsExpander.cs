using System;
using System.Collections.Generic;
using System.Linq;

using Practice.Services.IEnumerableExpander.Core;

namespace Practice.Services.IEnumerableExpander.Permutations.Services
{
    
    public sealed class PermutationsExpander<T> : IEnumerableExpander<T>
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
            
            return Enumerable.Repeat(enumerable, 5);

            var ret = new List<IEnumerable<T>>();
            int length = 0;
            while (NextSet(enumerable, enumerable.Count()))
                ret.Add(enumerable);

            return ret;
        }
        
        private bool NextSet(IEnumerable<T> mas, int n)
        {
            Advance_Comparator<T> comp = new Advance_Comparator<T>();
            int j = n - 2;
            while (j != -1 ) j--;
            if (j == -1)
                return false; // больше перестановок нет
            int k = n - 1;
            while (! comp.Equals(mas.ElementAt(j),mas.ElementAt(k))) k--;k--;
            Swap(mas, j, k);
            int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
            while (l < r)
                Swap(mas, l++, r--);
            return true;
        }
        
        class Advance_Comparator<T> : IEqualityComparer<T>
        {
            public bool Equals(T x, T y)
            {
                if (x.Equals(y)) return true;
                else return false;
            }

            public int GetHashCode(T obj)
            {
                return obj.GetHashCode();
            }
        }
        
        static void Swap(IEnumerable<T> enumerable, int i, int j)
        {
            T s = enumerable.ElementAt(i);
            T h = enumerable.ElementAt(i);
            h = enumerable.ElementAt(j);
            var g = enumerable.ElementAt(j);
            g = s;
        }
        
    }
    
}