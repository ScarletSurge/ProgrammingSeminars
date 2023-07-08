using System.Collections;

namespace Practice.Domain;

public class OwnArray<T>:
    IEnumerable<T>,
    ICloneable,
    IDisposable
    //where T: List<T>, IComparable, IComparable<T>, new()
{

    #region Nested
    
    public enum SortingMode
    {
        Ascending,
        Descending
    }
    
    #endregion
    
    private List<T> _array;

    public OwnArray()
    {
        _array = new List<T>();
    }
    
    private OwnArray(
        List<T> array)
    {
        _array = new List<T>(array);
    }

    public T this[
        int index]
    {
        get =>
            _array[index];
        
        set =>
            _array[index] = value;
    }
    
    //OwnArray<T> operator+(
    //    OwnArray<T> const &obj) const;

    public static OwnArray<T> Concat(
        OwnArray<T>? leftSummand,
        OwnArray<T>? rightSummand)
    {
        if (leftSummand is null)
        {
            throw new ArgumentNullException(nameof(leftSummand));
        }

        if (rightSummand is null)
        {
            throw new ArgumentNullException(nameof(rightSummand));
        }

        var arrayLength = leftSummand._array.Count + rightSummand._array.Count;
        var array = new List<T>(arrayLength);
        var i = 0;
        for (; i < leftSummand._array.Count; i++)
        {
            array.Add(leftSummand[i]);
        }

        for (; i < leftSummand._array.Count + rightSummand._array.Count; i++)
        {
            array.Add(rightSummand[i - leftSummand._array.Count]);
        }

        return new OwnArray<T>(array);
    }
    
    public static OwnArray<T> Sum(
        OwnArray<T>? leftSummand,
        OwnArray<T>? rightSummand)
    {
        if (leftSummand is null)
        {
            throw new ArgumentNullException(nameof(leftSummand));
        }

        if (rightSummand is null)
        {
            throw new ArgumentNullException(nameof(rightSummand));
        }

        var arrayLength = leftSummand._array.Count < rightSummand._array.Count
            ? leftSummand._array.Count
            : rightSummand._array.Count;
        var array = new List<T>(arrayLength);

        for (var i = 0; i < arrayLength; i++)
        {
            array.Add((dynamic?)leftSummand[i] + (dynamic?)rightSummand[i]);
        }

        return new OwnArray<T>(array);
    }
    
    public static OwnArray<T> operator +(
        OwnArray<T>? leftSummand,
        OwnArray<T>? rightSummand)
    {
        return Sum(leftSummand, rightSummand);
    }

    public T this[
        int index1, int index2]
    {
        get =>
            _array[index1 + index2];

        set =>
            _array[index1 + index2] = value;
    }

    public OwnArray<T> Insert(
        T value,
        int index)
    {
        _array.Insert(index, value);
        return this;
    }
    
    public OwnArray<T> FindByIndex(
        int index,
        out T foundValue)
    {
        foundValue = _array[index];
        return this;
    }

    public OwnArray<T> RemoveByIndex(
        int index,
        out T removedValue)
    {
        FindByIndex(index, out removedValue);
        _array.RemoveAt(index);
        return this;
    }

    public OwnArray<T> Sort()
    {
        _array.Sort();
        return this;
    }

    public OwnArray<T> Sort(
        IComparer<T> comparer)
    {
        _array.Sort(comparer);
        return this;
    }

    public void ForEach(
        Action<T> action)
    {
        foreach (var item in _array)
        {
            action(item);
        }
    }

    public IEnumerator<T> GetEnumerator()
    {
        foreach (var arrayItem in _array)
        {
            yield return arrayItem;
        }
        
        //for (int i = 0; i < _array.Count; i++)
        //{
        //    yield return _array[i];
        //    //if (i == 5)
        //    //{
        //    //    yield break;
        //    //}
        //}
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public override string ToString()
    {
        return $"[{string.Join(", ", _array)}]";
    }

    private StreamReader _reader;

    public void Dispose()
    {
        _reader?.Dispose();
        //_reader = null;
        GC.SuppressFinalize(this);
    }

    ~OwnArray()
    {
        _reader?.Dispose();
    }

    public object Clone()
    {
        return new OwnArray<T>(_array);
    }
}