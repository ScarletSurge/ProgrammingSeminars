namespace RGU.DistributedSystems.WPF.MVVM.Navigation;

/// <summary>
/// 
/// </summary>
public sealed class NavigationContext
{

    #region Nested

    /// <summary>
    /// 
    /// </summary>
    public sealed class Builder
    {

        #region Fields

        /// <summary>
        /// 
        /// </summary>
        private Type? _from;

        /// <summary>
        /// 
        /// </summary>
        private Type? _to;

        /// <summary>
        /// 
        /// </summary>
        private readonly Dictionary<string, object?> _parameters;

        #endregion

        #region Constructors

        /// <summary>
        /// 
        /// </summary>
        private Builder()
        {
            _parameters = new Dictionary<string, object?>();
        }

        #endregion

        #region Methods

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public static Builder Create()
        {
            return new Builder();
        }

        /// <summary>
        /// TODO: выглядит как полная хуйня конечно
        /// </summary>
        /// <param name="fromType"></param>
        /// <returns></returns>
        public Builder From(
            Type fromType)
        {
            if (!fromType.GetInterfaces().Contains(typeof(INavigatable)))
            {
                throw new InvalidOperationException("Can't navigate from instance, which type not implement INavigatable");
            }

            _from = fromType;

            return this;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="from"></param>
        /// <returns></returns>
        public Builder From<TNavigationSource>()
            where TNavigationSource: INavigatable
        {
            _from = typeof(TNavigationSource);

            return this;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="to"></param>
        /// <returns></returns>
        public Builder To<TNavigationTarget>()
            where TNavigationTarget: INavigatable
        {
            _to = typeof(TNavigationTarget);

            return this;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="parameterName"></param>
        /// <param name="parameterValue"></param>
        /// <returns></returns>
        public Builder WithParameter(
            string parameterName,
            object? parameterValue)
        {
            _parameters.Add(parameterName, parameterValue);

            return this;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public NavigationContext Build()
        {
            return new NavigationContext(
                _from ?? throw new ArgumentNullException(nameof(_from), "Navigation source not set"),
                _to ?? throw new ArgumentNullException(nameof(_to), "Navigation target not set"),
                _parameters);
        }

        #endregion

    }

    #endregion

    #region Constructors

    /// <summary>
    /// 
    /// </summary>
    /// <param name="from"></param>
    /// <param name="to"></param>
    /// <param name="parameters"></param>
    private NavigationContext(
        Type from,
        Type to,
        Dictionary<string, object?> parameters)
    {
        From = from;
        To = to;
        Parameters = parameters;
    }

    #endregion

    #region Properties

    /// <summary>
    /// 
    /// </summary>
    public Type From
    {
        get;
    }

    /// <summary>
    /// 
    /// </summary>
    public Type To
    {
        get;
    }

    /// <summary>
    /// 
    /// </summary>
    private Dictionary<string, object?> Parameters
    {
        get;
    }

    /// <summary>
    /// 
    /// </summary>
    public bool Cancelled
    {
        get;

        private set;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="parameterName"></param>
    /// <returns></returns>
    public object? this[
        string parameterName] =>
            GetParameter(parameterName);

    #endregion

    #region Methods

    /// <summary>
    /// 
    /// </summary>
    /// <param name="parameterName"></param>
    /// <returns></returns>
    public object? GetParameter(
        string parameterName)
    {
        return Parameters[parameterName];
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="parameterName"></param>
    /// <param name="parameterValue"></param>
    /// <returns></returns>
    public bool TryGetParameter(
        string parameterName,
        out object? parameterValue)
    {
        return Parameters.TryGetValue(parameterName, out parameterValue);
    }

    /// <summary>
    /// 
    /// </summary>
    public void Cancel()
    {
        Cancelled = true;
    }

    #endregion

}