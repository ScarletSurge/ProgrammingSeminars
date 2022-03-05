using System;
using DACS.DryIoc.Domain;

namespace DACS.DryIoc.OperatingSystem.Windows
{
    
    /// <summary>
    /// 
    /// </summary>
    public sealed class WindowsOS : IOperatingSystem
    {
        
        #region Fields

        private readonly OperatingSystemSettings _settings;
        
        #endregion
        
        #region Constructors

        public WindowsOS(OperatingSystemSettings settings)
        {
            _settings = settings
                ?? throw new ArgumentNullException(nameof(settings));
        }
        
        #endregion
        
        #region IOperatingSystem implementation

        public string Producer => "Microsoft";
        
        public string Name => "Windows";

        public string Version => _settings.Version;

        public BitDepth BitDepth => _settings.BitDepth;

        #endregion

    }
}