using System.Globalization;

namespace RGU.DistributedSystems.WPF.MVVM;

public sealed class ArithmeticConverter:
    MultiValueConverterBase<ArithmeticConverter>
{
    
    #region Nested
    
    /// <summary>
    /// 
    /// </summary>
    public enum Operators
    {
        /// <summary>
        /// 
        /// </summary>
        Plus,
        /// <summary>
        /// 
        /// </summary>
        Minus,
        /// <summary>
        /// 
        /// </summary>
        Multiply,
        /// <summary>
        /// 
        /// </summary>
        Divide,
        /// <summary>
        /// 
        /// </summary>
        RemainderDivide
    }
    
    #endregion
    
    #region RGU.DistributedSystems.WPF.MVVM.MultiValueConverterBase<ArithmeticConverter> overrides
    
    /// <inheritdoc cref="MultiValueConverterBase{TMultiValueConverter}.Convert" />
    public override object? Convert(
        object?[] values,
        Type targetType,
        object? parameter,
        CultureInfo culture)
    {
        if (values.Length != 2)
        {
            throw new ArgumentException("Invalid count of values!");
        }
        
        ArgumentNullException.ThrowIfNull(parameter);

        if (!Enum.IsDefined(typeof(Operators), parameter))
        {
            // TODO: throw an exception
        }

        var @operator = (Operators)parameter;
        dynamic leftOperand = values[0];
        dynamic rightOperand = values[1];

        switch (@operator)
        {
            case Operators.Plus:
                return leftOperand + rightOperand;
            case Operators.Minus:
                return leftOperand - rightOperand;
            case Operators.Multiply:
                return leftOperand * rightOperand;
            case Operators.Divide:
                return leftOperand / rightOperand;
            case Operators.RemainderDivide:
                return leftOperand % rightOperand;
            default:
                throw new ArgumentOutOfRangeException(nameof(parameter));
        }
    }
    
    #endregion
    
}