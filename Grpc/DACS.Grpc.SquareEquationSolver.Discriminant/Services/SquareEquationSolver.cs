using DACS.Grpc.Domain;

namespace DACS.Grpc.SquareEquationSolver.Discriminant.Services;

public sealed class SquareEquationSolver : ISquareEquationSolver
{

    private const double Epsilon = 1e-8;
    
    /// <inheritdoc />
    public (double, double) Solve(double a, double b, double c)
    {
        var discriminant = Math.Pow(b, 2) - 4d * a * c;
            
        if (Math.Abs(discriminant) < Epsilon)
        {
            return (-b / (2 * a), double.NaN);
        }
        
        if (discriminant > Epsilon)
        {
            return (-b + Math.Sqrt(discriminant) / 2 / a, -b - Math.Sqrt(discriminant) / 2 / a);
        }

        return (double.NaN, double.NaN);
    }
    
}