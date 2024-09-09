using Serilog.Events;
using Serilog.Formatting;
using Serilog.Formatting.Json;
using Serilog.Parsing;

namespace RGU.WebProgramming.Server.Core.Logging;

/// <summary>
/// An <see cref="ITextFormatter"/> that writes events in a compact JSON format.
/// </summary>
public sealed class CustomCompactJsonFormatter:
    ITextFormatter
{

    #region Fields

    /// <summary>
    /// 
    /// </summary>
    private readonly JsonValueFormatter _valueFormatter;
    
    /// <summary>
    /// 
    /// </summary>
    private readonly bool _useUtcTimezone;

    #endregion

    #region Constructors

    /// <summary>
    /// Construct a <see cref="CustomCompactJsonFormatter"/>, optionally supplying a formatter for
    /// <see cref="LogEventPropertyValue"/>s on the event.
    /// </summary>
    /// <param name="valueFormatter">A value formatter, or null.</param>
    /// <param name="useUtcTimezone">If value true then use UTC timezone otherwise use local timezone</param>
    public CustomCompactJsonFormatter(
        JsonValueFormatter valueFormatter = null,
        bool useUtcTimezone = false)
    {
        _valueFormatter = valueFormatter ?? new JsonValueFormatter("$type");
        _useUtcTimezone = useUtcTimezone;
    }

    #endregion

    #region Methods

    /// <summary>
    /// Format the log event into the output.
    /// </summary>
    /// <param name="logEvent">The event to format.</param>
    /// <param name="output">The output.</param>
    /// <param name="valueFormatter">A value formatter for <see cref="LogEventPropertyValue"/>s on the event.</param>
    /// <param name="useUtcTimezone">If value true then use UTC timezone otherwise use local timezone</param>
    private static void FormatEvent(
        LogEvent logEvent,
        TextWriter output,
        JsonValueFormatter valueFormatter,
        bool useUtcTimezone = true)
    {
        ArgumentNullException.ThrowIfNull(logEvent);
        ArgumentNullException.ThrowIfNull(output);
        ArgumentNullException.ThrowIfNull(valueFormatter);

        output.Write("{\"@t\":\"");

        output.Write(useUtcTimezone
            ? logEvent.Timestamp.UtcDateTime.ToString("O")
            : logEvent.Timestamp.LocalDateTime.ToString("O"));

        output.Write("\",\"@mt\":");
        JsonValueFormatter.WriteQuotedJsonString(logEvent.MessageTemplate.Text, output);

        var tokensWithFormat = logEvent.MessageTemplate.Tokens
            .OfType<PropertyToken>()
            .Where(pt => pt.Format != null);

        if (tokensWithFormat.Any())
        {
            output.Write(",\"@r\":[");
            var delimiter = "";
            
            foreach (var r in tokensWithFormat)
            {
                output.Write(delimiter);
                delimiter = ",";
                var space = new StringWriter();
                r.Render(logEvent.Properties, space);
                JsonValueFormatter.WriteQuotedJsonString(space.ToString(), output);
            }
            output.Write(']');
        }

        if (logEvent.Level != LogEventLevel.Information)
        {
            output.Write(",\"@l\":\"");
            output.Write(logEvent.Level);
            output.Write('\"');
        }

        if (logEvent.Exception != null)
        {
            output.Write(",\"@x\":");
            JsonValueFormatter.WriteQuotedJsonString(logEvent.Exception.ToString(), output);
        }

        foreach (var property in logEvent.Properties)
        {
            var name = property.Key;
            if (name.Length > 0 && name[0] == '@')
            {
                // Escape first '@' by doubling
                name = '@' + name;
            }

            output.Write(',');
            JsonValueFormatter.WriteQuotedJsonString(name, output);
            output.Write(':');
            valueFormatter.Format(property.Value, output);
        }

        output.Write('}');
    }

    #endregion

    #region Serilog.Formatting.ITextFormatter implementation

    /// <summary>
    /// Format the log event into the output. Subsequent events will be newline-delimited.
    /// </summary>
    /// <param name="logEvent">The event to format.</param>
    /// <param name="output">The output.</param>
    public void Format(
        LogEvent logEvent,
        TextWriter output)
    {
        FormatEvent(logEvent, output, _valueFormatter, _useUtcTimezone);
        output.WriteLine();
    }

    #endregion

}