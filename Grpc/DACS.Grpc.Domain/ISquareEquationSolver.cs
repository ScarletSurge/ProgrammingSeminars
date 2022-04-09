namespace DACS.Grpc.Domain;

/// <summary>
/// 
/// </summary>
public interface ISquareEquationSolver
{
    
    /// <summary>
    /// Solves an quadratic equation.
    /// </summary>
    /// <param name="a">x^2 coeff</param>
    /// <param name="b">x coeff</param>
    /// <param name="c">c coeff</param>
    /// <returns>two solutions</returns>
    (double, double) Solve(double a, double b, double c);

}