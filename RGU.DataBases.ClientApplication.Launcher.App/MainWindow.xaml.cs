using System;
using System.Collections.Generic;
using System.Windows;

using Npgsql;

namespace RGU.DataBases.ClientApplication.Launcher.App
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly DatabaseRequester _requester = new DatabaseRequester();
        
        public MainWindow()
        {
            InitializeComponent();
        }

        private async void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            var students = await _requester.GetAllStudentsAsync(nameSubstring: "im");
            // TODO: work with data;
            var x = 10;
        }
    }
}