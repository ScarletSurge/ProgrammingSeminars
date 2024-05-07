#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_TYPENAME_HOLDER_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_TYPENAME_HOLDER_H

#include <string>

class typename_holder
{

public:
    
    virtual ~typename_holder() noexcept = default;

protected:
    
    virtual inline std::string get_typename() const noexcept = 0;
    
};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_COMMON_TYPENAME_HOLDER_H