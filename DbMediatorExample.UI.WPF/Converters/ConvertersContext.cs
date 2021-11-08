using System.Windows;

using DbMediatorExample.Database.Models.Enums;

namespace DbMediatorExample.UI.WPF.Converters
{

    internal static class ConvertersContext
    {

        public static EqualityConverter<Visibility> TrueToVisibleFalseToCollapsed { get; }
            = new EqualityConverter<Visibility>(Visibility.Visible, Visibility.Collapsed);

        public static EqualityConverter<Visibility> TrueToVisibleFalseToHidden { get; }
            = new EqualityConverter<Visibility>(Visibility.Visible, Visibility.Hidden);

        public static RoleToBoolConverter AdminToTrueUserToFalse { get; }
            = new RoleToBoolConverter(Role.User, Role.Admin);

        public static RoleToBoolConverter UserToTrueAdminToFalse { get; }
            = new RoleToBoolConverter(Role.Admin, Role.User);

    }

}