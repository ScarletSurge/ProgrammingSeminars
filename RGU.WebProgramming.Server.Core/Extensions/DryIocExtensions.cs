using DryIoc;
using DryIoc.ImTools;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Options;

namespace RGU.WebProgramming.Server.Core.Extensions;

/// <summary>
/// 
/// </summary>
public static class DryIocExtensions
{

    /// <summary>
    /// 
    /// </summary>
    /// <param name="registrator"></param>
    /// <param name="serviceType"></param>
    /// <param name="registeredServiceType"></param>
    /// <param name="serviceKey"></param>
    /// <param name="registeredServiceKey"></param>
    /// <param name="factoryType"></param>
    public static void AddMapping(
        this IRegistrator registrator,
        Type serviceType,
        Type registeredServiceType,
        object serviceKey = null,
        object registeredServiceKey = null,
        FactoryType factoryType = FactoryType.Service)
    {
        var factories = registrator.GetRegisteredFactories(registeredServiceType, registeredServiceKey, factoryType);

        if (factories.IsNullOrEmpty())
        {
            Throw.It(Error.RegisterMappingNotFoundRegisteredService, registeredServiceType, registeredServiceKey);
        }

        if (factories.Length > 1)
        {
            Throw.It(Error.RegisterMappingUnableToSelectFromMultipleFactories, serviceType, serviceKey, factories);
        }

        registrator.Register(factories[0], serviceType, serviceKey, IfAlreadyRegistered.AppendNewImplementation, false);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="config"></param>
    /// <param name="ifAlreadyRegistered"></param>
    /// <returns></returns>
    public static IRegistrator Configure<TOptions>(
        this IRegistrator services,
        IConfiguration config,
        IfAlreadyRegistered? ifAlreadyRegistered = null)
            where TOptions: class =>
                services.Configure<TOptions>(string.Empty, config, ifAlreadyRegistered);

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="name"></param>
    /// <param name="config"></param>
    /// <param name="ifAlreadyRegistered"></param>
    /// <returns></returns>
    public static IRegistrator Configure<TOptions>(
        this IRegistrator services,
        string name,
        IConfiguration config,
        IfAlreadyRegistered? ifAlreadyRegistered = null)
            where TOptions: class =>
                services.Configure<TOptions>(name, config, _ => { }, ifAlreadyRegistered);

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="config"></param>
    /// <param name="configureBinder"></param>
    /// <param name="ifAlreadyRegistered"></param>
    /// <returns></returns>
    public static IRegistrator Configure<TOptions>(
        this IRegistrator services,
        IConfiguration config,
        Action<BinderOptions> configureBinder,
        IfAlreadyRegistered? ifAlreadyRegistered = null)
            where TOptions: class =>
                services.Configure<TOptions>(string.Empty, config, configureBinder, ifAlreadyRegistered);

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="name"></param>
    /// <param name="config"></param>
    /// <param name="configureBinder"></param>
    /// <param name="ifAlreadyRegistered"></param>
    /// <returns></returns>
    /// <exception cref="ArgumentNullException"></exception>
    public static IRegistrator Configure<TOptions>(
        this IRegistrator services,
        string name,
        IConfiguration config,
        Action<BinderOptions> configureBinder,
        IfAlreadyRegistered? ifAlreadyRegistered = null)
            where TOptions: class
    {
        ArgumentNullException.ThrowIfNull(services, nameof(services));
        ArgumentNullException.ThrowIfNull(config, nameof(config));

        services.RegisterInstance<IOptionsChangeTokenSource<TOptions>>(
            new ConfigurationChangeTokenSource<TOptions>(name, config), ifAlreadyRegistered);
        services.RegisterInstance<IConfigureOptions<TOptions>>(
            new NamedConfigureFromConfigurationOptions<TOptions>(name, config, configureBinder), ifAlreadyRegistered);

        return services;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="configureOptions"></param>
    /// <returns></returns>
    public static IRegistrator Configure<TOptions>(
        this IRegistrator services,
        Action<TOptions> configureOptions)
            where TOptions: class =>
                services.Configure(string.Empty, configureOptions);

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="name"></param>
    /// <param name="configureOptions"></param>
    /// <returns></returns>
    /// <exception cref="ArgumentNullException"></exception>
    public static IRegistrator Configure<TOptions>(
        this IRegistrator services,
        string name,
        Action<TOptions> configureOptions)
            where TOptions: class
    {
        ArgumentNullException.ThrowIfNull(services, nameof(services));
        ArgumentNullException.ThrowIfNull(configureOptions, nameof(configureOptions));

        services.RegisterInstance<IConfigureOptions<TOptions>>(
            new ConfigureNamedOptions<TOptions>(name, configureOptions));

        return services;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="configureOptions"></param>
    /// <returns></returns>
    public static IRegistrator PostConfigure<TOptions>(
        this IRegistrator services,
        Action<TOptions> configureOptions)
            where TOptions: class =>
                services.PostConfigure(string.Empty, configureOptions);

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TOptions"></typeparam>
    /// <param name="services"></param>
    /// <param name="name"></param>
    /// <param name="configureOptions"></param>
    /// <returns></returns>
    public static IRegistrator PostConfigure<TOptions>(
        this IRegistrator services,
        string name,
        Action<TOptions> configureOptions)
            where TOptions: class
    {
        ArgumentNullException.ThrowIfNull(services, nameof(services));
        ArgumentNullException.ThrowIfNull(configureOptions, nameof(configureOptions));

        services.RegisterInstance<IPostConfigureOptions<TOptions>>(
            new PostConfigureOptions<TOptions>(name, configureOptions));
        return services;
    }

}