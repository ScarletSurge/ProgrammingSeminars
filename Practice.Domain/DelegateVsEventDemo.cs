namespace Practice.Domain;

public class DelegateVsEventDemo
{

    public event Action<int, string> Action;

    // public void AddSubscriber(
    //     Action<int, string> subscriber)
    // {
    //     Action += subscriber;
    // }
    //
    // public void RemoveSubscriber(
    //     Action<int, string> subscriber)
    // {
    //     Action -= subscriber;
    // }

    public void Foo(int value1, string value2)
    {
        Action?.Invoke(value1, value2);
    }

}