#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_NOT_IMPLEMENTED_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_NOT_IMPLEMENTED_H

#include <stdexcept>

class not_implemented final:
    public std::logic_error
{

public:
    
    explicit not_implemented(
        std::string const &method_name,
        std::string const &message);
    
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_NOT_IMPLEMENTED_H