#include "../include/client_logger_builder.h"
#include "../include/client_logger.h"

client_logger_builder::client_logger_builder()
{
    logger::severity severities[6] =
        {
            logger::severity::trace,
            logger::severity::debug,
            logger::severity::information,
            logger::severity::warning,
            logger::severity::error,
            logger::severity::critical
        };

    for (auto const &severity: severities)
    {
        _streams_info[severity] = std::set<std::string>();
    }

    _log_format = "[%d %t][%s] %m";
}

logger_builder *client_logger_builder::set_log_format(
    std::string const &format)
{
    // TODO: validate passed format string

    _log_format = format;

    return this;
}

logger_builder *client_logger_builder::add_file_stream(
    std::string const &stream_file_path,
    logger::severity severity)
{
    // TODO: validate stream_file_path

    _streams_info[severity].insert(convert_to_absolute(stream_file_path));

    return this;
}

logger_builder *client_logger_builder::add_console_stream(
    logger::severity severity)
{
    _streams_info[severity].insert("");

    return this;
}

logger_builder *client_logger_builder::transform_with_configuration(
    std::string const &configuration_file_path,
    std::string const &configuration_path)
{
    // TODO: You can do this :)

    return this;
}

logger_builder *client_logger_builder::clear()
{
    *this = client_logger_builder();

    return this;
}

logger *client_logger_builder::build() const
{
    return new client_logger(_streams_info, _log_format);
}

std::string client_logger_builder::convert_to_absolute(
    std::string const &path)
{
    // TODO: Your code here...

    return path;
}