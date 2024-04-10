using System.Collections;

namespace RGU.dotNET.SecondTerm.ThreadSafeContainer;

public sealed class ThreadSafeContainer<T>:
    IEnumerable<T>
{
    
    #region Fields

    private readonly List<T> _items;
    private readonly object _sync = new ();

    #endregion
    
    #region Constructors

    public ThreadSafeContainer()
    {
        _items = new List<T>();
    }

    #endregion
    
    #region Methods

    public void Add(
        T obj)
    {
        lock (_sync)
        {
            _items.Add(obj);
        }
    }

    public int Length =>
        _items.Count;
    
    #endregion
    
    #region System.Collections.Generic.IEnumerable<T> implementation
    
    public IEnumerator<T> GetEnumerator()
    {
        return _items.GetEnumerator();
    }
    
    #endregion
    
    #region System.Collections.IEnumerable implementation

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
    
    #endregion
    
}