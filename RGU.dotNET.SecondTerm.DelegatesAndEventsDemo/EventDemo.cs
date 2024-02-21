namespace RGU.dotNET.SecondTerm.DelegatesAndEventsDemo;

// Джеффри Рихтер "CLR via C#"

public class EventDemo
{
    
    private Action _delegate;

    private int _value;
    public int Value
    {
        get =>
            _value;

        set =>
            _value = value;
    }
    
    public event Action SelfMadeSubUnsub
    {
        add
        {
            _delegate += value;
            _delegate += value;
        }

        remove =>
            //_delegate = (Action)Delegate.Remove(_delegate, value);
            _delegate -= value;
    }

    void Foo()
    {
        var value = 10;
    }

    public event Action _event;
    // TRANSFORMS TO:
    //private Action _event;
    //public void AddSubscriber(
    //    Action action)
    //{
    //    _event += action;
    //}
    //
    //public void RemoveSubscriber(
    //    Action action)
    //{
    //    _event -= action;
    //}
    

    // // ILSpy
    // public EventDemo()
    // {
    //     
    // }
    // 
    // EventDemo.__<>0ctor
}