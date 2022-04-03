using Grpc.Core;

namespace DACS.Grpc.Server.Services;

public class GrpcServiceImpl : GrpcService.GrpcServiceBase
{
    
    #region Fields
    
    private readonly ILogger<GrpcServiceImpl> _logger;
    
    #endregion
    
    #region Constructors
    
    public GrpcServiceImpl(ILogger<GrpcServiceImpl> logger)
    {
        _logger = logger;
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
        const double Epsilon = 1e-8;
        
        try
        {
            _logger.LogInformation($"{nameof(SolveQuadraticEquation)} method called.");

            var discr = Math.Pow(request.BCoeff, 2) - 4d * request.ACoeff * request.CCoeff;

            var response = new QuadraticEquationResponse();
            
            if (Math.Abs(discr) < Epsilon)
            {
                response.X1 = -request.BCoeff / (2 * request.ACoeff);
                response.X2 = double.NaN;
            }
            else if (discr > Epsilon)
            {
                response.X1 = (-request.BCoeff + Math.Sqrt(discr)) / (2 * request.ACoeff);
                response.X2 = (-request.BCoeff - Math.Sqrt(discr)) / (2 * request.ACoeff);
            }
            else
            {
                response.X1 = double.NaN;
                response.X2 = double.NaN;
            }

            return Task.FromResult(response);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, ex.Message);
            return Task.FromResult(new QuadraticEquationResponse
            {
                X1 = double.NaN,
                X2 = double.NaN
            });
        }
    }

    #endregion
    
}