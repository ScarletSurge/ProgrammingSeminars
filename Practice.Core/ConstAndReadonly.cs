namespace Practice.Core
{
    
    public sealed class ConstAndReadonly
    {
        
        public const int Const = 123;
        //public const object obj = new object(); - incorrect
        public static readonly object obj = new object();

        static ConstAndReadonly()
        {
            obj = new object();
        }

        public ConstAndReadonly(object o)
        {
            int a = 5;
        }

        void foo()
        {
            
        }

    }
    
}