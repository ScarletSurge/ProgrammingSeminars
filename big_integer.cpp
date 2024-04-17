#include <stdexcept>
#include "big_integer.h"

big_integer &big_integer::change_sign()
{
    _oldest_digit ^= (1 << ((sizeof(int) << 3) - 1));

    return *this;
}

bool big_integer::sign() const noexcept
{
    return (*reinterpret_cast<unsigned int const *>(&_oldest_digit) >> ((sizeof(int) << 3) - 1)) == 1;
}

bool big_integer::is_equal_to_zero() const noexcept
{
    return _oldest_digit == 0 && _other_digits == nullptr;
}

big_integer::big_integer(
    int *digits,
    size_t digits_count)
{
    // TODO: remove additional zeros
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
        : new unsigned int[digits_count]);

    if (_other_digits == nullptr)
    {
        return;
    }

    *_other_digits = (unsigned int)digits_count;

    memcpy(_other_digits + 1, digits, sizeof(unsigned int) * (digits_count - 1));
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
    big_integer const &other):
        _oldest_digit(other._oldest_digit),
        _other_digits(nullptr)
{
    if (other._other_digits == nullptr)
    {
        return;
    }

    _other_digits = new unsigned int[*other._other_digits];
    memcpy(_other_digits, other._other_digits, sizeof(unsigned int) * (*other._other_digits));
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
    if (this->is_equal_to_zero() && this->is_equal_to_zero())
    {
        return *this;
    }

    if (this->is_equal_to_zero())
    {
        return *this = other;
    }

    if (other.is_equal_to_zero())
    {
        return *this;
    }

    if (!this->sign() && !other.sign())
    {
        change_sign();
        *this += -other;
        return change_sign();
    }
    else if (this->sign() && !other.sign())
    {
        return *this -= -other;
    }
    else if (!this->sign() && other.sign())
    {
        change_sign();
        *this += -other;
        return change_sign();
    }

    // TODO: sum of two positive values
}

big_integer big_integer::operator+(
    big_integer const &other) const
{
    return big_integer(*this) += other;
}

big_integer &big_integer::operator-=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator-(
    big_integer const &other) const
{
    return big_integer(*this) -= other;
}

big_integer big_integer::operator-() const
{
    return big_integer(*this).change_sign();
}

big_integer &big_integer::operator*=(
    big_integer const &other)
{

}

big_integer big_integer::operator*(
    big_integer const &other) const
{
    return big_integer(*this) *= other;
}

big_integer &big_integer::operator/=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator/(
    big_integer const &other) const
{
    return big_integer(*this) /= other;
}

big_integer &big_integer::operator%=(
    big_integer const &other)
{
    
}

big_integer big_integer::operator%(
    big_integer const &other) const
{
    return big_integer(*this) %= other;
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