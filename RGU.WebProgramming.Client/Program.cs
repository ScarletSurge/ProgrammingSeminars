using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Microsoft.Extensions.Options;
using RGU.WebProgramming.Client.Grpc;
using RGU.WebProgramming.Client.Grpc.Settings;
using RGU.WebProgramming.Grpc;

var grpcChannelFactory = new GrpcChannelFactory(Options.Create(new GrpcClientSettings
{
    TargetAddress = "127.0.0.1:5055"
}));

var clientService = new MyFirstService.MyFirstServiceClient(grpcChannelFactory.Create());

var result = await clientService.MyFirstRPCAsync(new Empty());
Console.WriteLine($"Value == {result.Value}, Abrakadabra == {result.Abrakadabra}");