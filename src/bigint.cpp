#include "../include/bigint.h"

bigint::~bigint() noexcept
{
    delete[] _other_digits;
}

bigint::bigint(
    bigint const &other)
{
    // TODO:
}

bigint &bigint::operator=(
    bigint const &other)
{
    if (this != &other)
    {
        // TODO:
    }

    return *this;
}

bigint::bigint(
    int const *digits,
    size_t digits_count)
{
    if (digits == nullptr)
    {
        throw std::invalid_argument("Pointer to digits array can't be EQ to nullptr");
    }

    if (digits_count == 0)
    {
        throw std::invalid_argument("Digits count can't be EQ to 0");
    }

    if (digits_count == 1)
    {
        _other_digits = nullptr;
        _oldest_digit = *digits;

        return;
    }

    *(_other_digits = new int[digits_count]) = static_cast<int>(digits_count);
    memcpy(_other_digits + 1, digits, (digits_count - 1) * sizeof(int));
    _oldest_digit = digits[digits_count - 1];

    // TODO: Ernest must remove extra non-valuable digits
}

bigint::bigint(
    char const *string_representation,
    size_t base)
{
    // TODO: this requires implemented operator+= and operator*=
}

int bigint::get_sign() const noexcept
{
    if (_oldest_digit == 0 && _other_digits == nullptr)
    {
        return 0;
    }

    return (_oldest_digit >> ((sizeof(int) << 3) - 1)) == 0
        ? 1
        : -1;
}

size_t bigint::get_digits_count() const noexcept
{
    return _other_digits == nullptr
        ? 1
        : *_other_digits;
}

int &bigint::operator[](
    size_t index)
{
    auto const digits_count = get_digits_count();

    if (index >= digits_count)
    {
        throw std::out_of_range("index");
    }

    return index == digits_count - 1
        ? _oldest_digit
        : _other_digits[1 + index];
}

bigint &bigint::operator+=(
    bigint const &summand) &
{

}

bigint bigint::operator+(
    bigint const &summand) const
{
    bigint result(*this);

    return result += summand;
}

bigint &bigint::operator++()
{

}

bigint bigint::operator++(
    int)
{

}

bigint &bigint::operator-=(
    bigint const &minuend) &
{

}

bigint bigint::operator-(
    bigint const &minuend) const
{

}

bigint &bigint::operator--()
{

}

bigint bigint::operator--(
    int)
{

}

bigint &bigint::operator*=(
    bigint const &multiplier) &
{

}

bigint bigint::operator*(
    bigint const &multiplier) const
{

}

bigint &bigint::operator/=(
    bigint const &divisor) &
{

}

bigint bigint::operator/(
    bigint const &divisor) const
{

}

bigint &bigint::operator%=(
    bigint const &divisor) &
{

}

bigint bigint::operator%(
    bigint const &divisor) const
{

}

bigint::division_result bigint::division(
    bigint const &divisor) const
{

}

bool bigint::operator==(
    bigint const &other) const
{

}

bool bigint::operator!=(
    bigint const &other) const
{

}

bool bigint::operator<(
    bigint const &other) const
{

}

bool bigint::operator<=(
    bigint const &other) const
{

}

bool bigint::operator>(
    bigint const &other) const
{

}

bool bigint::operator>=(
    bigint const &other) const
{

}

bigint bigint::operator~() const
{

}

bigint &bigint::operator&=(
    bigint const &other) &
{

}

bigint bigint::operator&(
    bigint const &other) const
{

}

bigint &bigint::operator|=(
    bigint const &other) &
{

}

bigint bigint::operator|(
    bigint const &other) const
{

}

bigint &bigint::operator^=(
    bigint const &other) &
{

}

bigint bigint::operator^(
    bigint const &other) const
{

}

bigint &bigint::operator<<=(
    bigint const &other) &
{

}

bigint bigint::operator<<(
    bigint const &other) const
{

}

bigint &bigint::operator>>=(
    bigint const &other) &
{

}

bigint bigint::operator>>(
    bigint const &other) const
{

}

std::ostream &operator<<(
    std::ostream &stream,
    bigint const &value)
{

}

std::istream &operator>>(
    std::istream &stream,
    bigint &value)
{

}