namespace Practice.Launcher.App
{
    
    // Э. Троельсен "C# 9.0 и платформа .NET 5"
    // Д. Рихтер "CLR via C#" (4 изд)
    // Дж. (?) Скит "C# для профессионалов"
    // GoF - Приёмы ООП, паттерны ООП
    
    public class OOPeDemo
    {
        
        private int _myField;
        private string _myString;

        public OOPeDemo(
            int myField)
        {
            _myField = myField;
        }

        public void Foo()
        {
            Console.WriteLine("где лабы");
        }

        public int MyField1
        {
            get;
            protected set;
        }

        public string Prop =>
            "123";

        public string PropSet
        {
            set =>
                _myString = value;
        }

        public int MyField
        {
            get
            {
                MyField1 = 123;
                return _myField;
            }

            set
            {
                _myField = value;
            }
        }

    }
}