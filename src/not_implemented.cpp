#include "../include/not_implemented.h"

not_implemented::not_implemented(
    std::string const &method_name,
    std::string const &message):
    logic_error("method `" + method_name + "` not implemented: \"" + message + "\"")
{

}