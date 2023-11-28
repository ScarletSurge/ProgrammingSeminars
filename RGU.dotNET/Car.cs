namespace RGU.dotNET;

using System.Text;

public sealed class Car : Drivable
{
    // virtual abstract override sealed
    private string _clutchPedal;
    private string _gasPedal;
    private string _brakePedal;
    private string _wheels;
    private string _korobka;

    public Car(
        string baranka = "123456",
        string clutchPedal = "123456",
        string gasPedal = "123456",
        string brakePedal = "123456",
        string wheels = "123456",
        string korobka = "123456")
        : base(baranka)
    {
        Console.WriteLine("Called constructor of Car instance");
        _clutchPedal = clutchPedal ?? throw new ArgumentNullException(nameof(clutchPedal));
        _gasPedal = gasPedal ?? throw new ArgumentNullException(nameof(gasPedal));
        _brakePedal = brakePedal ?? throw new ArgumentNullException(nameof(brakePedal));
        _wheels = wheels ?? throw new ArgumentNullException(nameof(wheels));
        _korobka = korobka ?? throw new ArgumentNullException(nameof(korobka));
    }

    public override void Drive()
    {
        Console.WriteLine("Driving car...");
    }

    public static Car operator +(Car car1, Car car2)
    {
        return new Car(car1._baranka + car2._baranka,
            car1._clutchPedal + car2._clutchPedal,
            car1._gasPedal + car2._gasPedal,
            car1._brakePedal + car2._brakePedal, car1._wheels + car2._wheels,
            car1._korobka + car2._korobka);
    }

    public override string ToString()
    {
        const string prefix = "Car: { \"baranka\": \"";
        const string clutch = "\", \"clutchPedal\": \"";
        const string gas = "\", \"gasPedal\": \"";
        const string brake = "\", \"brakePedal\": \"";
        const string wheels = "\", \"wheels\": \"";
        const string korobka = "\", \"korobka\": \"";
        const string postfix = "\" }";
        //return prefix + _baranka + clutch + _clutchPedal + gas + _gasPedal + brake + _brakePedal + wheels + _wheels + korobka + _korobka + postfix;

        return new StringBuilder(prefix.Length + clutch.Length + gas.Length + brake.Length + wheels.Length + korobka.Length + postfix.Length + _baranka.Length + _clutchPedal.Length + _gasPedal.Length + _brakePedal.Length + _wheels.Length + _korobka.Length)
            .Append(prefix)
            .Append(_baranka)
            .Append(clutch)
            .Append(_clutchPedal)
            .Append(gas)
            .Append(_gasPedal)
            .Append(brake)
            .Append(_brakePedal)
            .Append(wheels)
            .Append(_wheels)
            .Append(korobka)
            .Append(_korobka)
            .Append(postfix)
            .ToString();

        // string interpolation
    }
    
}