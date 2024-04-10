#include <stdexcept>
#include "big_integer.h"

big_integer::big_integer(
    int *digits,
    size_t digits_count)
{
    if (digits == nullptr)
    {
        throw std::logic_error("pointer to digits array must not be nullptr");
    }

    if (digits_count == 0)
    {
        throw std::logic_error("digits array length must  be GT 0");
    }

    _oldest_digit = digits[digits_count - 1];
    _other_digits = (digits_count == 1
        ? nullptr
        : new unsigned int[digits_count - 1]);

    memcpy(_other_digits, digits, sizeof(unsigned int) * (digits_count - 1));
}

big_integer::big_integer(
    std::vector<int> const &digits)
{
    
}

big_integer::big_integer(
    std::string const &value,
    size_t base)
{
    
}

big_integer::big_integer(
    big_integer const &other)
{
    
}

big_integer &big_integer::operator=(
    big_integer const &other)
{
    
}

big_integer::~big_integer()
{
    
}

big_integer &big_integer::operator+=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator+(
    big_integer const &other) const
{
    
}

big_integer &big_integer::operator-=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator-(
    big_integer const &other) const
{
    
}

big_integer &big_integer::operator*=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator*(
    big_integer const &other) const
{
    
}

big_integer &big_integer::operator/=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator/(
    big_integer const &other) const
{
    
}

big_integer &big_integer::operator%=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator%(
    big_integer const &other) const
{
    
}

bool big_integer::operator==(
    big_integer const &other) const
{
    
}

bool big_integer::operator!=(
    big_integer const &other) const
{
    
}

bool big_integer::operator<(
    big_integer const &other) const
{
    
}

bool big_integer::operator<=(
    big_integer const &other) const
{
    
}

bool big_integer::operator>(
    big_integer const &other) const
{
    
}

bool big_integer::operator>=(
    big_integer const &other) const
{
    
}

big_integer big_integer::operator~() const
{
    
}

big_integer big_integer::operator&(
    big_integer const &other) const
{
    
}

big_integer big_integer::operator|(
    big_integer const &other) const
{
    
}

big_integer big_integer::operator^(
    big_integer const &other) const
{
    
}

big_integer big_integer::operator<<(
    size_t shift_value) const
{
    
}

big_integer big_integer::operator>>(
    size_t shift_value) const
{
    
}

std::ostream &operator<<(
    std::ostream &stream,
    big_integer const &value)
{
    
}

std::istream &operator>>(
    std::istream &stream,
    big_integer &value)
{
    
}