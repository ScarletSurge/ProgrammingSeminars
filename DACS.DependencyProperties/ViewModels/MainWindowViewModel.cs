using System.Collections.ObjectModel;
using DACS.WPF.MVVM.ViewModel;

namespace DACS.DependencyProperties.ViewModels
{
    
    internal sealed class MainWindowViewModel : ViewModelBase
    {
        
        #region Nested

        public struct LogInfo
        {
            public int Id { get; set; }

            public string Log { get; set; }
        }
        
        #endregion
        
        #region Fields

        private int _id = 0;
        private string _text;
        
        #endregion
        
        #region Properties

        public ObservableCollection<LogInfo> Logs { get; } = new ObservableCollection<LogInfo>();

        public string Text
        {
            get =>
                _text;

            set
            {
                _text = value;
                RaisePropertyChanged(nameof(Text));
            }
        }
        
        #endregion
        
        #region Methods

        public void AddLog(string log)
        {
            Logs.Add(new LogInfo
            {
                Id = ++_id,
                Log = log
            });
        }
        
        #endregion

    }
    
}