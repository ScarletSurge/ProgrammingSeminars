#ifndef INTERPRETERS_LOGGER_GUARDANT_H
#define INTERPRETERS_LOGGER_GUARDANT_H

#include "logger.h"

class logger_guardant
{

public:

    virtual ~logger_guardant() noexcept = default;

public:

    logger_guardant const *log_with_guard(
        std::string const &message,
        logger::severity severity) const;

    logger_guardant const *trace_with_guard(
        std::string const &message) const;

    logger_guardant const *debug_with_guard(
        std::string const &message) const;

    logger_guardant const *information_with_guard(
        std::string const &message) const;

    logger_guardant const *warning_with_guard(
        std::string const &message) const;

    logger_guardant const *error_with_guard(
        std::string const &message) const;

    logger_guardant const *critical_with_guard(
        std::string const &message) const;

protected:

    inline virtual logger *get_logger() const = 0;

};

logger_guardant const *logger_guardant::log_with_guard(
    std::string const &message,
    logger::severity severity) const
{
    logger *got_logger = get_logger();
    if (got_logger != nullptr)
    {
        got_logger->log(message, severity);
    }

    return this;
}

logger_guardant const *logger_guardant::trace_with_guard(
    std::string const &message) const
{
    return log_with_guard(message, logger::severity::trace);
}

logger_guardant const *logger_guardant::debug_with_guard(
    std::string const &message) const
{
    return log_with_guard(message, logger::severity::debug);
}

logger_guardant const *logger_guardant::information_with_guard(
    std::string const &message) const
{
    return log_with_guard(message, logger::severity::information);
}

logger_guardant const *logger_guardant::warning_with_guard(
    std::string const &message) const
{
    return log_with_guard(message, logger::severity::warning);
}

logger_guardant const *logger_guardant::error_with_guard(
    std::string const &message) const
{
    return log_with_guard(message, logger::severity::error);
}

logger_guardant const *logger_guardant::critical_with_guard(
    std::string const &message) const
{
    return log_with_guard(message, logger::severity::critical);
}

#endif //INTERPRETERS_LOGGER_GUARDANT_H