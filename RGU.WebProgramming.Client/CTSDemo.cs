namespace RGU.WebProgramming.Domain.Converters;

/// <summary>
/// 
/// </summary>
internal sealed class CTSDemo:
    IDisposable
{
    
    /// <summary>
    /// 
    /// </summary>
    private CancellationTokenSource? _cts;

    public CTSDemo()
    {
        
    }

    public int Request()
    {
        _cts = new CancellationTokenSource();

        try
        {
            return InnerRequestAsync<int>(_cts.Token).GetAwaiter().GetResult();
        }
        catch (OperationCanceledException ex)
        {
            _cts.Dispose();
            _cts = null;
            // _cts = new CancellationTokenSource();
            return -1;
        }
        finally
        {
            
        }
    }

    public void Cancel()
    {
        _cts.Cancel();
        // _cts.Dispose();
        // _cts = new CancellationTokenSource();
    }

    private async Task<T> InnerRequestAsync<T>(
        CancellationToken cancellationToken = default)
            where T: new()
    {
        await Task.Delay(TimeSpan.FromSeconds(5), cancellationToken);
        cancellationToken.ThrowIfCancellationRequested();
        return new T();
    }

    /// <inheritdoc cref="IDisposable.Dispose" />
    public void Dispose()
    {
        _cts.Dispose();
        
        GC.SuppressFinalize(this);
    }
    
    /// <summary>
    /// 
    /// </summary>
    ~CTSDemo()
    {
        _cts.Dispose();
    }

}