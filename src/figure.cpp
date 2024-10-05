#include "..\include\figure.h"

#include <iostream>

std::ostream &operator<<(
    std::ostream &stream,
    figure const *obj)
{
    return obj->print(stream);
}

std::istream &operator>>(
    std::istream &stream,
    figure *obj)
{
    return obj->read(stream);
}