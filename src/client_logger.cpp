#include "../include/client_logger.h"

#include <fstream>
#include <set>

std::map<std::string, std::pair<std::ostream *, size_t>> client_logger::_all_streams = std::map<std::string, std::pair<std::ostream *, size_t>>();

client_logger::client_logger(
    std::map<logger::severity, std::set<std::string>> const &streams,
    std::string log_format):
        _log_format(std::move(log_format))
{
    std::set<std::string> registered_paths;

    for (auto const &severity_path: streams)
    {
        _streams[severity_path.first] = std::vector<std::pair<std::ostream *, std::string>>(severity_path.second.size());
        int i = 0;

        for (auto const &path: severity_path.second)
        {
            auto it = _all_streams.find(path);

            if (it == _all_streams.cend())
            {
                _all_streams[path] = std::make_pair(path.empty()
                    ? &std::cout
                    : new std::ofstream(path), 1);

                it = _all_streams.find(path);

                registered_paths.insert(path);
            }
            else if (!registered_paths.contains(it->first))
            {
                ++(it->second.second);

                registered_paths.insert(path);
            }

            _streams[severity_path.first][i++] = std::make_pair(it->second.first, path);
        }
    }
}

client_logger::~client_logger()
{
    std::set<std::string> unregistered_paths;

    for (auto const &severity_stream_path: _streams)
    {
        for (auto const &stream_path: severity_stream_path.second)
        {
            if (!unregistered_paths.contains(stream_path.second))
            {
                unregistered_paths.insert(stream_path.second);

                auto it = _all_streams.find(stream_path.second);

                if (--(it->second.second) == 0)
                {
                    if (it->second.first != &std::cout)
                    {
                        it->second.first->flush();
                        delete it->second.first;
                    }

                    _all_streams.erase(it);
                }
            }
        }
    }
}

client_logger::client_logger(
    client_logger const &other)
{
    // TODO: Your code should be placed here...
}

client_logger &client_logger::operator=(
    client_logger const &other)
{
    // TODO: Your code should be placed here...

    return *this;
}

client_logger::client_logger(
    client_logger &&other) noexcept
{
    // TODO: Your code should be placed here...
}

client_logger &client_logger::operator=(
    client_logger &&other) noexcept
{
    // TODO: Your code should be placed here...

    return *this;
}

logger const *client_logger::log(
    std::string const &message,
    logger::severity severity) const noexcept
{
    auto it = _streams.find(severity);

    if (it == _streams.cend())
    {
        return this;
    }

    time_t log_time;
    time(&log_time);
    auto formatted_message = format_log(message, severity, log_time);

    for (auto const &stream_path: it->second)
    {
        *stream_path.first << formatted_message << std::endl;
    }

    return this;
}

std::string client_logger::format_log(
    std::string const &message,
    logger::severity severity,
    time_t current_date_time)
{
    // TODO: format log using _log_format field
    // TODO: implement me plz ._.

    return message;
}