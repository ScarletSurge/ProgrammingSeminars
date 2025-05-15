#ifndef COURSE1_CPP_RGU_CLIENT_LOGGER_H
#define COURSE1_CPP_RGU_CLIENT_LOGGER_H

#include <map>
#include <ostream>
#include <set>
#include <vector>

#include "logger.h"

class client_logger final:
    public logger
{

    friend class client_logger_builder;

private:

    static std::map<std::string, std::pair<std::ostream *, size_t>> _all_streams;

private:

    std::map<logger::severity, std::vector<std::pair<std::ostream *, std::string>>> _streams;
    std::string _log_format;

private:

    explicit client_logger(
        std::map<logger::severity, std::set<std::string>> const &streams,
        std::string log_format);

public:

    ~client_logger() override;

    client_logger(
        client_logger const &other);

    client_logger &operator=(
        client_logger const &other);

    client_logger(
        client_logger &&other) noexcept;

    client_logger &operator=(
        client_logger &&other) noexcept;

public:

    logger const *log(
        std::string const &message,
        logger::severity severity) const noexcept override;

private:

    static std::string format_log(
        std::string const &message,
        logger::severity severity,
        time_t current_date_time);

};

#endif //COURSE1_CPP_RGU_CLIENT_LOGGER_H