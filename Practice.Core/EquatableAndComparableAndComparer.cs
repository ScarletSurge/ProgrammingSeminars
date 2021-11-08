using System;
using System.Collections.Generic;
using System.Text;

namespace Practice.Core
{
    // == !=
    // > < >= <=
    public class EquatableImplementation : IEquatable<int>, IEquatable<EquatableImplementation>
    {
        private int _field;
        
        public bool Equals(int other)
        {
            return _field.Equals(other);
        }

        public bool Equals(EquatableImplementation other)
        {
            if (other is null)
            {
                return false;
            }

            return _field.Equals(other._field);
        }

        #region object
        
        public override bool Equals(object obj)
        {
            if (obj is null)
            {
                return false;
            }

            if (ReferenceEquals(this, obj))
            {
                return true;
            }

            if (obj is int @int)
            {
                return Equals(@int);
            }

            if (obj is EquatableImplementation eq)
            {
                return Equals(eq);
            }

            return false;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        
        public override string ToString()
        {
            return $"[ _field = {_field} ]";
        }
        
        #endregion
        
    }

    public class ComparableImplementation : IComparable, IComparable<int>, IComparable<ComparableImplementation>
    {

        private int _field;
        
        public int CompareTo(object obj)
        {
            if (obj is null)
            {
                throw new ArgumentNullException(nameof(obj));
            }

            if (ReferenceEquals(this, obj))
            {
                return 0;
            }

            if (obj is int @int)
            {
                return CompareTo(@int);
            }

            if (obj is ComparableImplementation ci)
            {
                return CompareTo(ci);
            }

            throw new ArgumentException($"typeof(obj) in incompatible with " +
                                        $"{typeof(ComparableImplementation).Name} for comparison",
                nameof(obj));
        }

        public int CompareTo(int other)
        {
            return _field.CompareTo(other);
        }

        public int CompareTo(ComparableImplementation other)
        {
            if (other is null)
            {
                throw new ArgumentNullException(nameof(other));
            }
            
            return _field.CompareTo(other._field);
        }
        
    }

    public class SomeClass<T> where T : class, IEquatable<T>, new()
    {

        public int Value1;

        public string Value2;

        public T Value3;

        public SomeClass(int value1, string value2, T value3)
        {
            Value1 = value1;
            Value2 = value2;
            Value3 = value3;
        }

        public override string ToString()
        {
            return $"[ value1 = {Value1}, value2 = {Value2}, value3 = {Value3} ]";
        }
    }

    public class SomeClassEqualityComparer<T> : IEqualityComparer<SomeClass<T>>
        where T : class, IEquatable<T>, new()
    {
        public bool Equals(SomeClass<T> x, SomeClass<T> y)
        {
            if (ReferenceEquals(x, y)) return true;
            if (ReferenceEquals(x, null)) return false;
            if (ReferenceEquals(y, null)) return false;
            if (x.GetType() != y.GetType()) return false;
            return x.Value2 == y.Value2 && Equals(x.Value3, y.Value3);
        }

        public int GetHashCode(SomeClass<T> obj)
        {
            return HashCode.Combine(obj.Value2, obj.Value3);
        }
    }
    
    public class SomeOtherClassEqualityComparer<T> : IEqualityComparer<SomeClass<T>>
        where T : class, IEquatable<T>, new()
    {
        public bool Equals(SomeClass<T> x, SomeClass<T> y)
        {
            if (ReferenceEquals(x, y)) return true;
            if (ReferenceEquals(x, null)) return false;
            if (ReferenceEquals(y, null)) return false;
            if (x.GetType() != y.GetType()) return false;
            return Equals(x.Value1, y.Value1);
        }

        public int GetHashCode(SomeClass<T> obj)
        {
            
            return obj.Value1.GetHashCode();
        }
    }

    public class SomeClassComparer<T> : IComparer<SomeClass<T>>
        where T : class, IEquatable<T>, new()
    {
        public int Compare(SomeClass<T> x, SomeClass<T> y)
        {
            if (ReferenceEquals(x, y)) return 0;
            if (ReferenceEquals(null, y)) return 1;
            if (ReferenceEquals(null, x)) return -1;
            var value1Comparison = x.Value1.CompareTo(y.Value1);
            if (value1Comparison != 0) return value1Comparison;
            return string.Compare(x.Value2, y.Value2, StringComparison.Ordinal);
        }
    }

    public sealed class TImpl : IEquatable<TImpl>
    {

        private int _i;

        public TImpl()
        {
            _i = 0;
        }
        
        public TImpl(int i = 0)
        {
            _i = i;
        }
        
        public bool Equals(TImpl other)
        {
            if (other is null)
            {
                return false;
            }

            return _i.Equals(other._i);
        }

        public override bool Equals(object obj)
        {
            return ReferenceEquals(this, obj) || obj is TImpl other && Equals(other);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public override string ToString()
        {
            return $"[ _i = {_i} ]";
        }

    }

}