#include "../include/hex.h"

hex::hex()
{

}

hex::hex(const std::string &string_representation)
{

}

hex::~hex() noexcept
{

}

hex::hex(hex const &other)
{

}

hex &hex::operator=(hex const &other)
{

}

hex::hex(hex &&other) noexcept
{

}

hex &hex::operator=(hex &&other) noexcept
{
    int x = 10, z = 10;
    auto y = z = (x += 15);
}

// a += b
hex& hex::operator+=(hex const &summand)
{
    // TODO: logic here o_O

    return *this;
}

// a + b
hex hex::operator+(hex const &summand) const
{
    return hex(*this) += summand;
}

hex hex::operator+(hex summand) const
{
    return summand += *this;
}