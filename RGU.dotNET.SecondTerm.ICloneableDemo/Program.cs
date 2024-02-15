using RGU.dotNET.SecondTerm.ICloneableDemo;

var obj1 = new object();
var obj2 = obj1;
Console.WriteLine(ReferenceEquals(obj1, obj2));

var obj3 = new CloneableDemo();
var obj4 = ((ICloneable)obj3).Clone() as CloneableDemo;

Console.WriteLine(obj3.Equals(obj4));
Console.WriteLine(ReferenceEquals(obj3, obj4));