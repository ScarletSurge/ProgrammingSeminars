using DryIoc;
using DryIoc.Microsoft.DependencyInjection;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Serilog;
using System.Reflection;

using RGU.WebProgramming.Server.Deployment;

namespace RGU.WebProgramming.Server;

/// <summary>
/// 
/// </summary>
public class Program
{
    
    #region Public methods

    /// <summary>
    /// 
    /// </summary>
    /// <param name="args"></param>
    public static void Main(
        string[] args)
    {
        // obtain confgurations from appsettings.json and its transformations
        var configuration = BuildConfiguration();
        
        // set GAP logger
        Log.Logger = BuildLogger(configuration);

        try
        {
            // create host and obtain DI container from it
            var host = Startup.CreateHostBuilder().Build();
            var container = host.Services.GetService<IContainer>()
                .WithCompositionRoot<ServicesRegistration>();

            // get application and start
            var app = container.Resolve<App>();
            app.Start();
        }
        catch (Exception ex)
        {
            Log.Logger?.Fatal("Application start up failed");
            throw;
        }
        finally
        {
            Log.CloseAndFlush();
        }
    }
    
    #endregion
    
    #region Private methods
    
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    private static IConfiguration BuildConfiguration()
    {
        var rootPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
        Environment.SetEnvironmentVariable("BASEDIR", rootPath);
        var environmentVar = Environment.GetEnvironmentVariable("ENVIRONMENT");

        return new ConfigurationBuilder()
            .SetBasePath(rootPath)
            .AddJsonFile("appsettings.json", false, true)
            .AddJsonFile($"appsettings.{environmentVar}.json", true)
            .AddJsonFile($"appsettings.{environmentVar}.User.json", true)
            .Build();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="configuration"></param>
    /// <returns></returns>
    private static ILogger BuildLogger(
        IConfiguration configuration)
    {
        return new LoggerConfiguration()
            .ReadFrom.Configuration(configuration)
            .CreateLogger();
    }
    
    #endregion

}