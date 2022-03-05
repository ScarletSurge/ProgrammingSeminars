using System;
using DACS.DryIoc.Domain;

namespace DACS.DryIoc.OperatingSystem.MintLinux
{
    
    public sealed class MintLinuxOS : IOperatingSystem
    {
        
        #region Fields

        private readonly OperatingSystemSettings _settings;
        
        #endregion
        
        #region Constructors

        public MintLinuxOS(OperatingSystemSettings settings)
        {
            _settings = settings
                ?? throw new ArgumentNullException(nameof(settings));
        }
        
        #endregion
        
        #region IOperatingSystem implementation

        public string Producer => "Linus Torwaljds";

        public string Name => "Mint Linux";

        public string Version => _settings.Version;

        public BitDepth BitDepth => _settings.BitDepth;

        #endregion
        
    }
    
}