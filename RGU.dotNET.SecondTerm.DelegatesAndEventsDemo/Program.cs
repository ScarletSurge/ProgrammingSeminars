using RGU.dotNET.SecondTerm.DelegatesAndEventsDemo;

bool Foo1(int value1, int value2)
{
    Console.WriteLine("Foo1 called");
    return value1 == value2;
}

bool Foo2(int value1, int value2)
{
    Console.WriteLine("Foo2 called");
    return value1 != value2;
}

Foo @delegate = Foo2;
@delegate += Foo1;
@delegate -= Foo1;
@delegate -= Foo1;
@delegate += Foo2;
@delegate -= Foo2;
@delegate -= Foo2;
// WRONG: @delegate(1, 2);
// CORRECT:
@delegate?.Invoke(1, 2);

if (@delegate != null)
{
    @delegate(1, 2);
}

void Foo111(int value1, string value2)
{
    
}

Action<int, string>? f = null;
f += Foo111;

int Foo3(int value1, int value2)
{
    return value1 + value2;
}

int Foo4(int value1, int value2)
{
    return value1 - value2;
}

Func<int, int, int>? dlg = null;
dlg += Foo3;
dlg += Foo4;

int? res = dlg?.Invoke(10, 5);
Console.WriteLine(res);

var results = new List<int ?>();

foreach (var invocationItem in dlg?.GetInvocationList() ?? Enumerable.Empty<Delegate>())
{
    var valueToInsert = (int ?)invocationItem?.DynamicInvoke(10, "");
    results.Add(valueToInsert);
}

foreach (var result in results)
{
    Console.Write("{0} ", result);
}

void Foo123()
{
    
}

int MultiplyByTwo(
    int valueToMultiply)
{
    return valueToMultiply * 2;
}

var values = new int[10];

var newValues = values
    //.Select(MultiplyByTwo)
    //.Select(x => x * 2)
    .Select(delegate(int value) { return value * 2; })
    .ToArray();

EventDemo obj = new EventDemo();
obj.Value = 10;
Console.WriteLine(obj.Value + 10);
obj.SelfMadeSubUnsub += Foo123;
obj.SelfMadeSubUnsub -= Foo123;
//obj._delegate += Foo123;
//obj._delegate -= Foo123;
//obj._delegate?.Invoke();
//
//obj._event += Foo123;
//obj._event -= Foo123;
////CAN'T BE INVOKED
//
//obj._event();

//Action
//    Func

// Comparison<int>: Func<int, int, int>
// EventHandler: Action<object, EventArgs>
// EventHandler<TEventArgs>: Action<object, TEventArgs> where TEventArgs: EventArgs
// ThreadStart
// ParameterizedThreadStart
// Predicate<T>: Func<T, bool>

delegate bool Foo(int value1, int value2);