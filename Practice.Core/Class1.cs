using System;
using System.Collections;
using System.Text;

namespace Practice.Core
{
    
    public class Class1 : object
    {

        private int _a;

        public void Foo()
        {
            
        }

        public int A
        {
            get
            {
                return _a;
            }

            protected set =>
                _a = value;
        }

        public void Foo1()
        {
            int a1 = 5;
            var a = new Class1();
            var value = a.A;
            a.A = 10;
        }
        
        // int uint long ulong short ushort bool float double decimal char byte sbyte
        // enum struct ...
        // class interface delegate event string object ...
        
        // stackalloc

    }

    public abstract class A
    {

        private object _o;
        
        public virtual void Foo()
        {
            Console.WriteLine("Foo() from A called");
        }

        public abstract string Bar();

        public void ByIn(in object a)
        {
            // TODO
        }
        
        public void ByNothing(object a)
        {
            a = 10;
        }
        
        public void ByRef(ref object a)
        {
            a = new object();
        }

        public void ByOut(out object a)
        {
            a = new Exception("12345 message of this exception -_-");
        }

    }

    public sealed class B : A
    {

        private string _stringField;
        private int _i;

        public B()
        {
            // TODO: some initialization here...
        }

        public IEnumerator GetEnumerator()
        {
            return new System.Collections.Generic.List<int>.Enumerator();
        }

        public B(string stringFieldValue)
            : this()
        {
            _stringField = stringFieldValue;
        }

        public B(int i, string stringFieldValue)
            : this(stringFieldValue)
        {
            _i = i;
        }
        
        public override void Foo()
        {
            Console.WriteLine("Foo() from B called");
        }

        public override string Bar()
        {
            return "Bar from B";
        }
        
    }
    
    public class B1 : A
    {
        public override string Bar()
        {
            return "abc";
        }

        public override string ToString()
        {
            return "B1 class instance";
        }
    }

    public class C : A
    {
        
        public override string Bar()
        {
            return "Bar from C";
        }
        
    }

}