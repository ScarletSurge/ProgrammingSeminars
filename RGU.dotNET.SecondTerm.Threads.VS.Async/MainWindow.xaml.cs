using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RGU.dotNET.SecondTerm.Threads.VS.Async
{
    
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
        }

        private void ThreadButton_OnClick(
            object sender,
            RoutedEventArgs e)
        {
            // Thread thr = new Thread(() =>
            // {
            //     Thread.Sleep(5000);
            // });
            // thr.Start();
            // thr.Join();
            var randomSource = new Random();
            Parallel.For(0, 10, i =>
            {
                Thread.Sleep(1000);
                MessageBox.Show($"Thread with i == {i} finished");
            });
            MessageBox.Show("Thread button work finished");
        }

        private async void AsyncButton_OnClick(
            object sender,
            RoutedEventArgs e)
        {
            await Task.Delay(5000);
            MessageBox.Show("Async button work finished");
        }

    }
    
}