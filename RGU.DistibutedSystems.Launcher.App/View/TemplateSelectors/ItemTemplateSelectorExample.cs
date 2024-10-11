using System.Windows;
using System.Windows.Controls;
using RGU.DistibutedSystems.Launcher.App.ViewModel.Pages;

namespace RGU.DistibutedSystems.Launcher.App.View.TemplateSelectors;

/// <summary>
/// 
/// </summary>
internal sealed class ItemTemplateSelectorExample:
    DataTemplateSelector
{
    
    #region System.Windows.Controls.DataTemplateSelector overrides
    
    /// <inheritdoc cref="DataTemplateSelector.SelectTemplate" />
    public override DataTemplate SelectTemplate(
        object item,
        DependencyObject container)
    {
        ArgumentNullException.ThrowIfNull(item);
        
        if (container is not FrameworkElement frameworkElement)
        {
            // TODO: maybe throw an exception?!
            return null;
        }

        if (item.GetType() == typeof(TargetToNavigatePageViewModel.StringWrapperViewModel))
        {
            return frameworkElement.FindResource("StringWrapperTemplate") as DataTemplate;
        }
        
        if (item.GetType() == typeof(TargetToNavigatePageViewModel.ModifiableIntViewModel))
        {
            return frameworkElement.FindResource("ModifiableIntTemplate") as DataTemplate;
        }

        throw new ArgumentException("Invalid item type.", nameof(item));
    }
    
    #endregion
    
}