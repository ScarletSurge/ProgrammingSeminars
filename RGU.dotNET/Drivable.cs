namespace RGU.dotNET;

public abstract class Drivable
{

    protected string _baranka;

    public static void SomeStaticFunction()
    {
        Console.WriteLine("Hello! SomeStaticFunction is called!");
    }

    public Drivable(
        string baranka)
    {
        if (baranka == null)
        {
            throw new ArgumentNullException(nameof(baranka));
        }
        
        _baranka = baranka;
    }
    
    public string GetBaranka()
    {
        return _baranka;
    }

    protected void SetBaranka(
        string newValue)
    {
        _baranka = newValue;
    }

    // protected string Smth
    // {
    //     get;
    //     private set;
    // }

    public string Baranka
    {
        get =>
            "Baranka: \"" + _baranka + "\"";

        set =>
            _baranka = value;
    }

    public abstract void Drive();

}