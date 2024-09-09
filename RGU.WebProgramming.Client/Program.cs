using Google.Protobuf.WellKnownTypes;
using Grpc.Core;

using RGU.WebProgramming.Grpc;

var service = new MyFirstService.MyFirstServiceClient(new Channel("127.0.0.1:5055", ChannelCredentials.Insecure));

var result = await service.MyFirstRPCAsync(new Empty());
Console.WriteLine($"Value == {result.Value}, Abrakadabra == {result.Abrakadabra}");