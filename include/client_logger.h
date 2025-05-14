#ifndef COURSE1_CPP_RGU_CLIENT_LOGGER_H
#define COURSE1_CPP_RGU_CLIENT_LOGGER_H

#include <map>
#include <ostream>
#include <vector>

#include "logger.h"

class client_logger final:
    public logger
{

private:

    static std::map<std::string, std::pair<std::ostream *, size_t>> _all_streams;

private:

    std::map<logger::severity, std::vector<std::ostream *>> _streams;

    friend class client_logger_builder;

private:

    client_logger(std::map<logger::severity, std::vector<std::string>> const &streams)
    {
        //
    }


};

#endif //COURSE1_CPP_RGU_CLIENT_LOGGER_H