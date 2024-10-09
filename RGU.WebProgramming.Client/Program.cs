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

//var clientService = hostMediator.;

//var result = await clientService.MyFirstRPCAsync(new Empty());
//Console.WriteLine($"Value == {result.Value}, Abrakadabra == {result.Abrakadabra}");