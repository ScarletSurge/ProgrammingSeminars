using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Practice.Core
{
    
    public sealed class EnumerableMatrix : IEnumerable<double>, ICloneable
    {

        private readonly double[,] _innerArray;

        public EnumerableMatrix(double[,] innerArray)
        {
            _innerArray = (double[,])innerArray.Clone();
        }
        
        public IEnumerator<double> GetEnumerator()
        {
            return EnumerateRowsThenColumns().GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return _innerArray.GetEnumerator();
        }

        public IEnumerable<double> EnumerateRowsThenColumns()
        {
            for (int i = 0; i < _innerArray.GetLength(0); i++)
            {
                for (int j = 0; j < _innerArray.GetLength(1); j++)
                {
                    yield return _innerArray[i, j];
                }
            }
        }
        
        public IEnumerable<double> EnumerateColumnsThenRows()
        {
            for (int i = 0; i < _innerArray.GetLength(1); i++)
            {
                for (int j = 0; j < _innerArray.GetLength(0); j++)
                {
                    yield return _innerArray[j, i];
                }
            }
        }

        public object Clone()
        {
            return new EnumerableMatrix(_innerArray);
        }

        public double this[int row, int column]
        {
            get
            {
                if (row < 0 || row >= _innerArray.GetLength(0) ||
                    column < 0 || column >= _innerArray.GetLength(1))
                {
                    throw new ArgumentOutOfRangeException();
                }

                return _innerArray[row, column];
            }

            set
            {
                if (row < 0 || row >= _innerArray.GetLength(0) ||
                    column < 0 || column >= _innerArray.GetLength(1))
                {
                    throw new ArgumentOutOfRangeException();
                }

                _innerArray[row, column] = value;
            }
        }

        public EnumerableMatrix Add(EnumerableMatrix other)
        {
            if (other is null)
            {
                throw new ArgumentNullException(nameof(other));
            }

            if (_innerArray.GetLength(0) != other._innerArray.GetLength(0) ||
                _innerArray.GetLength(1) != other._innerArray.GetLength(1))
            {
                throw new InvalidOperationException("Can't obtain sum of matrices");
            }
            
            for (int i = 0; i < _innerArray.GetLength(0); i++)
            {
                for (int j = 0; j < _innerArray.GetLength(1); j++)
                {
                    this[i, j] += other[i, j];
                }
            }

            return this;
        }

        public static EnumerableMatrix Addition(EnumerableMatrix left, EnumerableMatrix right)
        {
            return ((EnumerableMatrix)left.Clone()).Add(right);
        }

        public static EnumerableMatrix operator +(EnumerableMatrix left, EnumerableMatrix right)
        {
            return Addition(left, right);
        }

        public override string ToString()
        {
            var sb = new StringBuilder("[ ");
            for (var i = 0; i < _innerArray.GetLength(0); i++)
            {
                sb.Append("[ ");
                for (var j = 0; j < _innerArray.GetLength(1); j++)
                {
                    sb.Append(this[i, j])
                        .Append(' ');
                }
                sb.Append("] ");
            }
            return sb.Append("]").ToString();
        }
    }
    
}