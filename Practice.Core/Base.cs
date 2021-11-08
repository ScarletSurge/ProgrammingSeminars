using System;

namespace Practice.Core
{
    
    public class Base1
    {

        private string _baseClassField;

        public Base1(string baseClassField)
        {
            _baseClassField = baseClassField;
        }
        
        public void Foo()
        {
            Console.WriteLine("Foo() from base");
        }
        
    }

    public class Derived : Base1
    {

        private int _derivedClassField;

        public Derived(int derivedClassField)
            : base("1234")
        {
            _derivedClassField = derivedClassField;
        }
        
        public new void Foo()
        {
            Console.WriteLine("Foo() from derived");
            base.Foo();
        }
        
    }
    
}