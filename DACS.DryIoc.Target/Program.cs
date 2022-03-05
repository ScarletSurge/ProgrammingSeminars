using System;
using System.Linq;
using System.Reflection;
using System.Threading;
using DACS.DryIoc.Domain;
using DryIoc;
using Microsoft.Extensions.Configuration;

namespace DACS.DryIoc.Target
{
    
    class Program
    {
        
        private static readonly Container Container;

        static Program()
        {
            Container = new Container();
        }
        
        static void Main(string[] args)
        {
            
            Container.Register<IAnimal, Cat.Cat>(Reuse.Singleton);
            Container.Register<Zoo>(Reuse.Transient);

            //var cat1 = Container.Resolve<IAnimal>();
            //var cat2 = Container.Resolve<IAnimal>();
            
            //Console.WriteLine(ReferenceEquals(cat1, cat2));

            var zoo1 = Container.Resolve<Zoo>();
            var zoo2 = Container.Resolve<Zoo>();
            
            zoo1.Voice();

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
                    .Register(Container, configuration);
            }
            
            Container.RegisterInstance(
                new OperatingSystemSettings
                {
                    Version = "10",
                    BitDepth = BitDepth.x64
                });
            
            Container.RegisterInstance(
                new CpuSettings
                {
                    Hz = 10000,
                    Producer = "-___-",
                    ThreadsCount = 8
                });

            var compudahter = Container.Resolve<ICompudahter>();
            Console.WriteLine($"OS: {compudahter.OperatingSystem.Name}");
            compudahter.PowerOn();
            Thread.Sleep(2000);
            compudahter.PowerOff();

        }
        
    }
    
}