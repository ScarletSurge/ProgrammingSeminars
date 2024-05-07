#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_OPERATION_NOT_SUPPORTED_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_OPERATION_NOT_SUPPORTED_H

#include <stdexcept>

class operation_not_supported final:
    public std::logic_error
{

public:
    
    explicit operation_not_supported();
    
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_OPERATION_NOT_SUPPORTED_H