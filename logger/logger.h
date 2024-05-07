#ifndef INTERPRETERS_LOGGER_H
#define INTERPRETERS_LOGGER_H

#include <iostream>

class logger
{

public:

    enum class severity
    {
        trace,
        debug,
        information,
        warning,
        error,
        critical
    };

public:

    virtual ~logger() noexcept = default;

public:

    virtual logger const *log(
        std::string const &message,
        logger::severity severity) const noexcept = 0;

public:

    logger const *trace(
        std::string const &message) const noexcept;

    logger const *debug(
        std::string const &message) const noexcept;

    logger const *information(
        std::string const &message) const noexcept;

    logger const *warning(
        std::string const &message) const noexcept;

    logger const *error(
        std::string const &message) const noexcept;

    logger const *critical(
        std::string const &message) const noexcept;

protected:

    static std::string severity_to_string(
        logger::severity severity);

    static std::string current_datetime_to_string() noexcept;

};

#include <iomanip>

logger const *logger::trace(
    std::string const &message) const noexcept
{
    return log(message, logger::severity::trace);
}

logger const *logger::debug(
    std::string const &message) const noexcept
{
    return log(message, logger::severity::debug);
}

logger const *logger::information(
    std::string const &message) const noexcept
{
    return log(message, logger::severity::information);
}

logger const *logger::warning(
    std::string const &message) const noexcept
{
    return log(message, logger::severity::warning);
}

logger const *logger::error(
    std::string const &message) const noexcept
{
    return log(message, logger::severity::error);
}

logger const *logger::critical(
    std::string const &message) const noexcept
{
    return log(message, logger::severity::critical);
}

std::string logger::severity_to_string(
    logger::severity severity)
{
    switch (severity)
    {
        case logger::severity::trace:
            return "TRACE";
        case logger::severity::debug:
            return "DEBUG";
        case logger::severity::information:
            return "INFORMATION";
        case logger::severity::warning:
            return "WARNING";
        case logger::severity::error:
            return "ERROR";
        case logger::severity::critical:
            return "CRITICAL";
    }

    throw std::out_of_range("Invalid severity value");
}

std::string logger::current_datetime_to_string() noexcept
{
    auto time = std::time(nullptr);

    std::ostringstream result_stream;
    result_stream << std::put_time(std::localtime(&time), "%d.%m.%Y %H:%M:%S");

    return result_stream.str();
}

#endif //INTERPRETERS_LOGGER_H