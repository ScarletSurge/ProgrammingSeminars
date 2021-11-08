 using DbMediatorExample.Database.Models;

namespace DbMediatorExample.UI.WPF.ViewModels
{

    internal sealed class LogViewModel : BaseViewModel
    {

        private Log _log;

        public LogViewModel(Log log)
        {
            Log = log;
        }

        public Log Log
        {
            get =>
                _log;

            private set
            {
                _log = value;
                OnPropertyChanged(nameof(Log));
            }
        }

    }

}