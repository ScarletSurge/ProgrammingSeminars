namespace RGU.dotNET.SecondTerm.DelegatesAndEventsDemo;

public class EventDemo
{
    public Action _delegate;
    public event Action _event;

    // public void AddSubscriber(
    //     Action action)
    // {
    //     _action += action;
    // }
    // 
    // public void RemoveSubscriber(
    //     Action action)
    // {
    //     _action -= action;
    // }
}