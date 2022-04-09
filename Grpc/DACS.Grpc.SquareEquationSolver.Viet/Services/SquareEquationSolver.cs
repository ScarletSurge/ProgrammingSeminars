using DACS.Grpc.Domain;

namespace DACS.Grpc.SquareEquationSolver.Viet.Services;

public class SquareEquationSolver : ISquareEquationSolver
{
    
    /// <inheritdoc />
    public (double, double) Solve(double a, double b, double c)
    {
        b /= a;
        c /= a;
        a = 1;
        
        // TODO: implementation...

        return (double.NaN, double.NaN);
    }
    
}