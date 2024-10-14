using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Microsoft.Extensions.Options;
using RGU.WebProgramming.Client.API;
using RGU.WebProgramming.Client.Grpc;
using RGU.WebProgramming.Client.Grpc.Settings;
using RGU.WebProgramming.Grpc;

var hostMediator = new HostMediator(new GrpcChannelFactory(Options.Create(new GrpcClientSettings
{
    TargetAddress = "127.0.0.1:5055"
})), Options.Create(new HostMediatorSettings
{

}), null);

CancellationTokenSource obj = new CancellationTokenSource();
await FooAsync();
await FooAsync(obj.Token);
obj.Dispose();
    
//var clientService = hostMediator.;

//var result = await clientService.MyFirstRPCAsync(new Empty());
//Console.WriteLine($"Value == {result.Value}, Abrakadabra == {result.Abrakadabra}");

async Task<int> FooAsync(
    CancellationToken cancellationToken = default)
{
    return await BarAsync(cancellationToken);
}

async Task<int> BarAsync(
    CancellationToken cancellationToken = default)
{
    while (true)
    {
        if (cancellationToken.IsCancellationRequested)
        {
            // TODO: some logic here...
            throw new TaskCanceledException();
        }
        // OperationCanceledException
        cancellationToken.ThrowIfCancellationRequested();
        // TODO: main actions
    }
}