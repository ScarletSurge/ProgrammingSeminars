using System;

namespace Practice.Core
{
    
    public interface ISomeInterface : IDisposable
    {

        void SomeAction();

        int SomeProperty
        {
            get;
        }

        event Action SomeEvent;

    }

    public interface ISomeOtherInterface
    {
        void Foo();
    }

    public class SomeInterfaceImplementation : ISomeInterface, ISomeOtherInterface
    {
        public event Action SomeEvent;
        
        public void SomeAction()
        {
            Console.Write("SomeAction() called from SomeInterfaceImplementation");
        }

        public int SomeProperty
        {
            get;

            private set;
        }

        public void Foo()
        {
            
        }

        public void Dispose()
        {
            
        }
    }
    
    public class SomeOtherInterfaceImplementation : ISomeInterface
    {
        private int _field;
        public event Action SomeEvent;
        
        public void SomeAction()
        {
            Console.Write("SomeAction() called from SomeOtherInterfaceImplementation");
        }

        public int SomeProperty
        {
            get =>
                _field;

            protected set =>
                _field = value;
        }

        public void Dispose()
        {
            
        }
    }
    
}