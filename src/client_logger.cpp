#include "../include/client_logger.h"

std::map<std::string, std::pair<std::ostream *, size_t>> client_logger::_all_streams = std::map<std::string, std::pair<std::ostream *, size_t>>();

