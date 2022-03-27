using System;
using System.Globalization;
using System.Windows;

using DACS.WPF.MVVM.Converter;

namespace DACS.WPF.HelloWorld.Converters
{
    
    internal sealed class ArithmeticCombinatorConverter : MultiConverterBase<ArithmeticCombinatorConverter>
    {
        
        public override object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(parameter is string operation))
            {
                throw new ArgumentException("parameter should be of type System.String", nameof(parameter));
            }
            
            if (values.Length != 2)
            {
                throw new ArgumentException("values count should be equal to 2", nameof(values));
            }

            if (values[0] == DependencyProperty.UnsetValue ||
                values[1] == DependencyProperty.UnsetValue)
            {
                return DependencyProperty.UnsetValue;
            }

            var leftOperand = (dynamic)values[0];
            var rightOperand = (dynamic)values[1];

            // leftOperand.NotExistingMethod();
            // leftOperand += new StreamGeometry();
            
            switch (operation)
            {
                case "+": return leftOperand + rightOperand;
                case "-": return leftOperand - rightOperand;
                case "*": return leftOperand * rightOperand;
                case "/": return leftOperand / rightOperand;
                case "%": return leftOperand % rightOperand;
                default: throw new ArgumentException("Invalid operation", nameof(operation));
            }
        }
        
    }
    
}