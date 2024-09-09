using DryIoc;
using DryIoc.Microsoft.DependencyInjection;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Serilog;
using System.Reflection;

using RGU.WebProgramming.Server.Core;
using RGU.WebProgramming.Server.Settings;

namespace RGU.WebProgramming.Server.Deployment;

/// <summary>
/// 
/// </summary>
internal static class Startup
{
    
    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private static string _rootPath;
    
    /// <summary>
    /// 
    /// </summary>
    private static Dictionary<string, ModuleInfo> _modules;
    
    #endregion
    
    #region Methods

    /// <summary>
    /// 
    /// </summary>
    /// <param name="rootPath"></param>
    /// <param name="additionalConfigureServices"></param>
    /// <returns></returns>
    /// <exception cref="InvalidOperationException"></exception>
    public static IHostBuilder CreateHostBuilder(
        string rootPath = null,
        Action<HostBuilderContext, IServiceCollection> additionalConfigureServices = null)
    {
        Directory.SetCurrentDirectory(_rootPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));

        return new HostBuilder()
            .UseSerilog()
            .ConfigureWebHostDefaults(webHostBuilder =>
            {
                webHostBuilder
                    .ConfigureAppConfiguration((context, configurationBuilder) =>
                    {
                        configurationBuilder
                            .SetBasePath(_rootPath)
                            .AddJsonFile("appsettings.json", false, true)
                            .AddJsonFile($"appsettings.{context.HostingEnvironment.EnvironmentName}.json", true, true);

                        if (context.HostingEnvironment.IsDevelopment())
                        {
                            configurationBuilder.AddJsonFile(
                                $"appsettings.{context.HostingEnvironment.EnvironmentName}.User.json", true);
                        }

                        configurationBuilder
                            .AddEnvironmentVariables()
                            .Build()
                            .Bind("Modules", _modules = new Dictionary<string, ModuleInfo>());

                        foreach (var enabledModuleInfo in _modules.Where(module => module.Value.Enabled))
                        {
                            Log.Logger?.Information("Adding module \"{moduleKey}\" from assembly \"{moduleAssembly}\"",
                                enabledModuleInfo.Key, enabledModuleInfo.Value.AssemblyName);
                            Assembly.LoadFrom(enabledModuleInfo.Value.AssemblyName);
                        }

                        var webHostConfigurators = AppDomain.CurrentDomain.GetAssemblies()
                            .Distinct()
                            .SelectMany(assembly => assembly.DefinedTypes)
                            .Where(assemblyDefinedType => assemblyDefinedType.ImplementsServiceType<IWebHostConfigurator>())
                            .Select(webHostConfiguratorType => (IWebHostConfigurator)Activator.CreateInstance(webHostConfiguratorType)!)
                            .ToList();

                        foreach (var webHostConfigurator in webHostConfigurators)
                        {
                            webHostConfigurator.Configure(webHostBuilder);
                        }
                    })
                    .Configure((_, applicationBuilder) =>
                    {
                        var applicationConfigurators = AppDomain.CurrentDomain.GetAssemblies()
                            .Distinct()
                            .SelectMany(assembly => assembly.DefinedTypes)
                            .Where(assemblyDefinedType => assemblyDefinedType.ImplementsServiceType<IApplicationConfigurator>())
                            .Select(applicationConfiguratorType => (IApplicationConfigurator)Activator.CreateInstance(applicationConfiguratorType)!)
                            .ToList();
                        
                        if (applicationConfigurators.Count > 1)
                        {
                            throw new InvalidOperationException("Only one IApplicationConfigurator instance is supported");
                        }
                        
                        foreach (var applicationConfigurator in applicationConfigurators)
                        {
                            applicationConfigurator.Configure(applicationBuilder);
                        }
                    });
            })
            .ConfigureHostConfiguration(hostBuilder =>
            {
                hostBuilder.AddEnvironmentVariables();
            })
            .UseServiceProviderFactory(hostBuilderContext =>
                new DryIocServiceProviderFactory(hostBuilderContext.Properties["DryIocContainer"] as IContainer))
            .ConfigureServices((hostBuilderContext, serviceCollection) =>
            {
                ConfigureServices(hostBuilderContext, serviceCollection);
                additionalConfigureServices?.Invoke(hostBuilderContext, serviceCollection);
                IContainer container = new Container();
                container.RegisterInstance(_modules);
                container.RegisterInstance(hostBuilderContext.Configuration);
                container = container
                    .WithCompositionRoot<ServicesRegistration>()
                    .WithCompositionRoot<ServiceRegistratorsCompositionRoot>();
                
                var startups = container.ResolveMany<Core.IStartup>();
                foreach (var startup in startups ?? Enumerable.Empty<Core.IStartup>())
                {
                    startup.ConfigureServices(hostBuilderContext, serviceCollection);
                }

                hostBuilderContext.Properties["DryIocContainer"] = container;
            });
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="ctx"></param>
    /// <param name="services"></param>
    private static void ConfigureServices(
        HostBuilderContext ctx,
        IServiceCollection services)
    {
        CatchUnhandledExceptions();
        
        services
            .AddOptions()
            .Configure<ModuleInfo[]>(ctx.Configuration.GetSection("Modules"));
    }
    
    /// <summary>
    /// 
    /// </summary>
    private static void CatchUnhandledExceptions()
    {
        // log all unhandled exceptions messages into console
        AppDomain.CurrentDomain.UnhandledException += (sender, e) =>
        {
            Log.Logger?.Fatal($"Unhandled exception occured: {(e.ExceptionObject as Exception)?.Message}");
        };
    }
    
    #endregion
    
}