using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using DACS.Grpc.Server;
using Grpc.Core;
using Grpc.Net.Client;

//await new MyAwaiter<int>();

var unsafeHandler = new HttpClientHandler();
unsafeHandler.ServerCertificateCustomValidationCallback = HttpClientHandler.DangerousAcceptAnyServerCertificateValidator;

//AppContext.SetSwitch("", false);

// The port number must match the port of the gRPC server.
using var channel = GrpcChannel.ForAddress("https://localhost:7215", new GrpcChannelOptions
{
    HttpHandler = unsafeHandler
});
var client = new GrpcService.GrpcServiceClient(channel);
/*var response = await client.SayHelloAsync(
    new HelloRequest
    {
        Name = "GreeterClient"
    });
Console.WriteLine("Greeting: " + response.Message);
Console.WriteLine("Press any key to exit...");
Console.ReadKey();*/

var cts = new CancellationTokenSource();
while (true)
{
    Console.WriteLine("Input coefficients of quadratic equation ax^2 + bx + c = 0");
    Console.Write("a: ");
    
    if (!double.TryParse(Console.ReadLine(), out var a))
    {
        Console.WriteLine($"Invalid input! Try again...{Environment.NewLine}");
        continue;
    }
    
    Console.Write("b: ");
    if (!double.TryParse(Console.ReadLine(), out var b))
    {
        Console.WriteLine($"Invalid input! Try again...{Environment.NewLine}");
        continue;
    }
    
    Console.Write("c: ");
    if (!double.TryParse(Console.ReadLine(), out var c))
    {
        Console.WriteLine($"Invalid input! Try again...{Environment.NewLine}");
        continue;
    }

    var request = new QuadraticEquationRequest
    {
        ACoeff = a,
        BCoeff = b,
        CCoeff = c
    };
    
    // TODO: test cancellation
    //var responseSync = client.SolveQuadraticEquation(request, cancellationToken: cts.Token);
    var responseAsync = await client.SolveQuadraticEquationAsync(request, cancellationToken: cts.Token);
    

    if (double.IsNaN(responseAsync.X1))
    {
        Console.WriteLine("No solutions found.");
    }
    else if (double.IsNaN(responseAsync.X2))
    {
        Console.WriteLine($"One solution found: x = {responseAsync.X1}.");
    }
    else
    {
        Console.WriteLine($"Two solutions found: x1 = {responseAsync.X1} and x2 = {responseAsync.X2}.");
    }

    Console.WriteLine();
}

/*class MyAwaiter<T>
{
    public System.Runtime.CompilerServices.TaskAwaiter<T> GetAwaiter()
    {
        throw new NotImplementedException();
    }
}*/