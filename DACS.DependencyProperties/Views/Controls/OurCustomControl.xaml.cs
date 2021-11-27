using System;
using System.Windows;
using System.Windows.Controls;

namespace DACS.DependencyProperties.Views.Controls
{
    public partial class OurCustomControl : UserControl
    {
        public OurCustomControl()
        {
            InitializeComponent();
            //DataContext = this;
        }

        public int SomeInt
        {
            get =>
                (int)GetValue(SomeIntProperty);
            
            private set =>
                SetValue(SomeIntProperty, value);
        }
        public static readonly DependencyProperty SomeIntProperty = DependencyProperty.Register(
            nameof(SomeInt), typeof(int), typeof(OurCustomControl),
            new PropertyMetadata(0));
        
        /// <summary>
        /// SomeString documentation
        /// </summary>
        public string SomeString
        {
            get =>
                (string)GetValue(SomeStringProperty);
            
            set =>
                SetValue(SomeStringProperty, value);
        }
        public static readonly DependencyProperty SomeStringProperty = DependencyProperty.Register(
            nameof(SomeString), typeof(string), typeof(OurCustomControl),
            new PropertyMetadata("defaultValue", (d, e) =>
            {
                if (!(d is OurCustomControl ourCustomControl))
                {
                    throw new ArgumentException($"Parameter \"{d}\" should be of type \"{typeof(OurCustomControl).FullName}\"", nameof(d));
                }

                ourCustomControl.SomeInt++;
            }, (d, value) =>
            {
                if (!(d is OurCustomControl ourCustomControl))
                {
                    throw new ArgumentException($"Parameter \"{d}\" should be of type \"{typeof(OurCustomControl).FullName}\"", nameof(d));
                }

                if (!(value is string stringValue))
                {
                    throw new ArgumentException($"{nameof(value)} should be of type {typeof(string).FullName}");
                }

                if (stringValue != "null")
                {
                    return stringValue;
                }

                return "null coerced";
            })/*, newValue => newValue is string @string && @string != "null"*/);
    }
}