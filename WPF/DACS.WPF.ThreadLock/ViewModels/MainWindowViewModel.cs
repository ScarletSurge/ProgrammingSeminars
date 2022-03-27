using System;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Threading;

using DACS.WPF.MVVM.Command;
using DACS.WPF.MVVM.ViewModel;

namespace DACS.WPF.ThreadLock.ViewModels
{
    
    internal sealed class MainWindowViewModel : ViewModelBase, IDisposable
    {
        
        #region Fields

        private ICommand _startThreadCommand;
        private ICommand _startTaskCommand;
        private ICommand _cancelTaskCommand;
        private CancellationTokenSource _canceller;
        
        #endregion
        
        #region Constructors

        public MainWindowViewModel()
        {
            _canceller = new CancellationTokenSource();
        }
        
        #endregion
        
        #region Properties

        public ICommand StartThreadCommand =>
            _startThreadCommand ??= new RelayCommand(_ => StartThread());

        public ICommand StartTaskCommand =>
            _startTaskCommand ??= new RelayCommand(async _ =>
            {
                //_canceller.CancelAfter(7500);
                await StartTaskAsync(_canceller.Token);
            });

        public ICommand CancelTaskCommand =>
            _cancelTaskCommand ??= new RelayCommand(_ => CancelTask());
        
        #endregion

        #region Methods

        private void StartThread()
        {
            var thread = new Thread(() => Thread.Sleep(5000));
            thread.Start();

            thread.Join();
            //var x = 5;
        }

        private Task StartTaskAsync(CancellationToken token = default)
        {
            var randomSource = new Random();
            var tasks = new Task[randomSource.Next(5, 26)];
            for (var i = 0; i < tasks.Length; i++)
            {
                tasks[i] = Task.Delay(new Random().Next(1000, 5000), token);
                // tasks[i] = await Task.Factory.StartNew(async () =>
                // {
                //     await Task.Delay(new Random().Next(1000, 5000), token);
                // }, token);
            }

            //var x = 5;
            
            return Task.CompletedTask;

            // await Task.WhenAll(tasks);
            // await Task.Delay(1000, token);
            
            //Task.WaitAll(tasks, token);
            /*return Task.WhenAll(tasks)
                .ContinueWith(async (t, param) =>
                {
                    await t;
                    await Task.Delay(3000, token);
                }, new object(), token);

            MessageBox.Show("finished");

            // var success = await ContinuationAsync(token);
            //
            // var message = success
            //     ? "Method executed successfully."
            //     : "Method executed with an error";
            //
            // MessageBox.Show(message);
            //
            if (token.IsCancellationRequested)
            {
                _canceller.Dispose();
                _canceller = new CancellationTokenSource();
            }*/
        }

        private Task<bool> ContinuationAsync(int delay, CancellationToken token = default)
        {
            try
            {
                Task.Delay(delay, token)
                    .GetAwaiter().GetResult(); //.ConfigureAwait(false);
            }
            catch (OperationCanceledException)
            {
                // TODO: log
            }

            if (token.IsCancellationRequested)
            {
                return Task.FromCanceled<bool>(token);
            }
            
            // thr2
            Dispatcher.CurrentDispatcher.Invoke(() => {  });

            try
            {
                Task.Delay(delay, token)
                    ; //.ConfigureAwait(false);
            }
            catch (OperationCanceledException)
            {
                // TODO: log
            }

            if (token.IsCancellationRequested)
            {
                return Task.FromCanceled<bool>(token);
            }
            
            // thr2
            //var x = 5;

            return Task.Factory.StartNew(() => true, token);
            //return Task.FromResult(true);
        }

        private void CancelTask()
        {
            _canceller.Cancel(false);
        }
        
        #endregion
        
        #region IDisposable implementation

        public void Dispose()
        {
            _canceller?.Dispose();
            
            GC.SuppressFinalize(this);
        }

        ~MainWindowViewModel()
        {
            _canceller?.Dispose();
        }
        
        #endregion

    }
    
}