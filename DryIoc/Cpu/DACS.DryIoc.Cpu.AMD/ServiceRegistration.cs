using System;
using DryIoc;
using Microsoft.Extensions.Configuration;

using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Cpu.AMD
{
    
    public sealed class ServiceRegistration : IServiceRegistrator
    {
        
        public void Register(IRegistrator registrator,
            IConfiguration configuration)
        {
            var osSection = configuration
                .GetSection(nameof(OperatingSystemSettings));
            var version = osSection.GetSection("Version").Value;
            var bitDepth = Enum.Parse<BitDepth>(osSection.GetSection("BitDepth").Value);

            registrator.Register<ICpu, AMDCpu>(Reuse.Transient);
            registrator.RegisterInstance(new OperatingSystemSettings
            {
                Version = version,
                BitDepth = bitDepth
            });
        }
        
    }
    
}