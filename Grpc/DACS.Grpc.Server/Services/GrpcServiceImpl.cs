using DACS.Grpc.Domain;
using Grpc.Core;

namespace DACS.Grpc.Server.Services;

public class GrpcServiceImpl : GrpcService.GrpcServiceBase
{
    
    #region Fields
    
    private readonly ILogger<GrpcServiceImpl> _logger;
    private readonly ISquareEquationSolver _squareEquationSolver;
    
    #endregion
    
    #region Constructors
    
    public GrpcServiceImpl(
        ILogger<GrpcServiceImpl> logger,
        ISquareEquationSolver squareEquationSolver)
    {
        _logger = logger ?? throw new ArgumentNullException(nameof(logger));
        _squareEquationSolver = squareEquationSolver ?? throw new ArgumentNullException(nameof(squareEquationSolver));
    }
    
    #endregion
    
    #region GrpcService.GrpcServiceBase overrides

    public override Task<HelloResponse> SayHello(HelloRequest request, ServerCallContext context)
    {
        try
        {
            _logger.LogInformation($"{nameof(SayHello)} method called.");

            return Task.FromResult(new HelloResponse
            {
                Message = "Hello " + request.Name
            });
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, ex.Message);
            return Task.FromResult(new HelloResponse());
        }
    }

    public override Task<QuadraticEquationResponse> SolveQuadraticEquation(QuadraticEquationRequest request, ServerCallContext context)
    {
        try
        {
            _logger.LogInformation($"{nameof(SolveQuadraticEquation)} method called.");

            var solution = _squareEquationSolver.Solve(request.ACoeff, request.BCoeff, request.CCoeff);

            return Task.FromResult(new QuadraticEquationResponse
            {
                X1 = solution.Item1,
                X2 = solution.Item2
            });
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, ex.Message);
            return Task.FromResult(new QuadraticEquationResponse
            {
                X1 = double.NaN,
                X2 = double.NaN,
                
            });
        }
    }

    #endregion
    
}