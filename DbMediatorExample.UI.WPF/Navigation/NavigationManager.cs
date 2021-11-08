using System;
using System.Windows;
using System.Windows.Navigation;

using DbMediatorExample.UI.WPF.ViewModels;

namespace DbMediatorExample.UI.WPF.Navigation
{

    internal static class NavigationManager
    {

        private static NavigationService _navigationService;

        public static NavigationService NavigationService
        {
            private get =>
                _navigationService;

            set
            {
                if (NavigationService is object)
                {
                    throw new ApplicationException("NavigationService instance is already initialized!");
                }
                _navigationService = value;
            }
        }

        public static bool Navigate(FrameworkElement to)
        {
            try
            {
                NavigationService?.Navigate(to);
                return true;
            }
            catch
            {
                return false;
            }
        }

        public static bool Navigate<TView>(BaseViewModel viewModel)
            where TView : FrameworkElement, new()
        {
            try
            {
                NavigationService?.Navigate(new TView { DataContext = viewModel });
                return true;
            }
            catch
            {
                return false;
            }
        }

        public static bool CanGoBack =>
            NavigationService?.CanGoBack ?? false;

        public static bool GoBack()
        {
            try
            {
                if (!CanGoBack)
                {
                    return false;
                }
                NavigationService?.GoBack();
                return true;
            }
            catch
            {
                return false;
            }
        }

    }

}