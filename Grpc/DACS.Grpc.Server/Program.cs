using System.Reflection;

using DACS.Grpc.Domain;
using DACS.Grpc.Server.Services;

var builder = WebApplication.CreateBuilder(args);

// Additional configuration is required to successfully run gRPC on macOS.
// For instructions on how to configure Kestrel and gRPC clients on macOS, visit https://go.microsoft.com/fwlink/?linkid=2099682

// Add services to the container.
builder.Services.AddGrpc();

RegisterDependencies(builder.Services);
builder.Services.AddSingleton<GrpcServiceImpl>();

var app = builder.Build();

// Configure the HTTP request pipeline.
app.MapGrpcService<GrpcServiceImpl>();
app.MapGet("/",
    () =>
        "Communication with gRPC endpoints must be made through a gRPC client. To learn how to create a client, visit: https://go.microsoft.com/fwlink/?linkid=2086909");

app.Run();

static void RegisterDependencies(IServiceCollection serviceCollection)
{
    var configuration = new ConfigurationBuilder()
        .SetBasePath(Environment.CurrentDirectory)
        .AddJsonFile("appsettings.json", false)
        .AddJsonFile("appsettings.Development.json", true)
        .Build() as IConfiguration;

    foreach (var moduleSettings in configuration.GetSection("Modules").Get<ModuleSettings[]>())
    {
        if (!moduleSettings.Used)
        {
            continue;
        }

        var assemblyName = new AssemblyName(moduleSettings.Assembly);
        var assembly = Assembly.Load(assemblyName);

        var targetType = assembly
            .GetTypes()
            .SingleOrDefault(type => type.GetInterfaces().Contains(typeof(IServiceRegistrator)));

        if (targetType is null)
        {
            // TODO: logs & exception
            continue;
        }
                
        ((IServiceRegistrator)Activator.CreateInstance(targetType))
            .Register(serviceCollection, configuration);
    }
}