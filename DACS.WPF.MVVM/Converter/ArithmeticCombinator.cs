using System;
using System.Globalization;
using System.Windows;

namespace DACS.WPF.MVVM.Converter
{

    public sealed class ArithmeticCombinator : MultiConverterBase<ArithmeticCombinator>
    {

        public enum Operators
        {
            Addition,
            Subtraction,
            Multiplication,
            Division,
            DivisionRemainder
        }

        public override object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {
            if (values.Length != 2)
            {
                // TODO
            }

            if (values[0] == DependencyProperty.UnsetValue ||
                values[1] == DependencyProperty.UnsetValue)
            {
                return DependencyProperty.UnsetValue;
            }

            var leftParameter = (dynamic)values[0];
            var rightParameter = (dynamic)values[1];
            
            // TODO: check if parameter is not Operators
            switch ((Operators)parameter)
            {
                case Operators.Addition:
                    return leftParameter + rightParameter;
                case Operators.Subtraction:
                    return leftParameter - rightParameter;
                case Operators.Multiplication:
                    return leftParameter * rightParameter;
                case Operators.Division:
                    return leftParameter / rightParameter;
                case Operators.DivisionRemainder:
                    return leftParameter % rightParameter;
                default:
                    // TODO: parameters
                    throw new ArgumentOutOfRangeException();
            }
        }
        
    }

}