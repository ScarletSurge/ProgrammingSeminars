#include "../include/bigint.h"

bigint::~bigint() noexcept
{
    delete[] _other_digits;
}

bigint::bigint(
    bigint const &other):
        _oldest_digit(other._oldest_digit),
        _other_digits(nullptr)
{
   if(other._other_digits != nullptr)
   {
       _other_digits = new int[*other._other_digits];
       memcpy(_other_digits, other._other_digits, *other._other_digits * sizeof(int));
   }
}

bigint &bigint::operator=(
    bigint const &other)
{
    if (this != &other)
    {

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

unsigned int bigint::operator[](
    size_t index) const noexcept
{
    auto const digits_count = get_digits_count();

    if (index >= digits_count)
    {
        return 0;
    }

    return *reinterpret_cast<unsigned int const *>(index == digits_count - 1
        ? &_oldest_digit
        : _other_digits + 1 + index);
}

bigint &bigint::negate() &
{
    // TODO: logic



    return *this;
}

bigint bigint::operator-() const
{
    bigint negative(*this);

    return negative.negate();
}

bigint &bigint::operator+=(
    bigint const &summand) &
{
    unsigned int max_digits_count = get_max(get_digits_count(), summand.get_digits_count()) + 1;

    int *result_space = new int[max_digits_count];
    unsigned int extra_digit = 0;

    for (size_t i = 0; i < max_digits_count; ++i)
    {
        result_space[i] = 0;

        auto this_digit = this->operator[](i);
        auto other_digit = summand[i];

        // TODO: make functional refactoring

        for (size_t j = 0; j < 2; ++j)
        {
            auto this_half_digit = j == 0
                ? get_loword(this_digit)
                : get_hiword(this_digit);

            auto other_half_digit = j == 0
                ? get_loword(other_digit)
                : get_hiword(other_digit);

            auto digits_sum = this_half_digit + other_half_digit + extra_digit;

            extra_digit = digits_sum >> SHIFT;

            result_space[i] += (digits_sum & MASK) << (j * SHIFT);
        }
    }

    // TODO: set calculeted state to current object

    return *this;
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

bigint const bigint::operator++(
    int)
{

}

bigint &bigint::operator-=(
    bigint const &minuend) &
{
    return *this += -minuend;
}

bigint bigint::operator-(
    bigint const &minuend) const
{
    bigint result(*this);

    return result -= minuend;
}

bigint &bigint::operator--()
{

}

bigint const bigint::operator--(
    int)
{

}

bigint &bigint::operator*=(
    bigint const &multiplier) &
{
    if (get_sign() == 0)
    {
        return *this;
    }

    if (multiplier.get_sign() == 0)
    {
        return *this = multiplier;
    }

    // TODO: German should handle multiplication of two negative values o_O

    if (multiplier.get_sign() == -1)
    {
        return (*this *= -multiplier).negate();
    }

    if (get_sign() == -1)
    {
        return (negate() *= multiplier).negate();
    }

    // TODO: Egor Letov should handle multiplying by 1/-1

    int words_multiplication_result_digits[2] = { 0 };
    int digit = 0;
    unsigned int words_multiplication_result_digit = 0;
    bigint const zero(&digit, 1);
    bigint result = zero;

    auto this_digits_count = get_digits_count();
    auto multiplier_digits_count = multiplier.get_digits_count();

    for (size_t i = 0; i < this_digits_count; ++i)
    {
        auto this_digit = (*this)[i];
        auto this_digit_loword = get_loword(this_digit);
        auto this_digit_hiword = get_hiword(this_digit);

        for (size_t j = 0; j < multiplier_digits_count; ++j)
        {
            auto multiplier_digit = multiplier[j];
            auto multiplier_digit_loword = get_loword(multiplier_digit);
            auto multiplier_digit_hiword = get_hiword(multiplier_digit);

            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_loword, multiplier_digit_loword, (i + j) << 1);
            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_loword, multiplier_digit_hiword, (i + j + 1) << 1);
            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_hiword, multiplier_digit_loword, (i + j + 1) << 1);
            addition_for_multiplication(result, words_multiplication_result_digits, this_digit_hiword, multiplier_digit_hiword, (i + j + 2) << 1);
        }
    }

    delete[] _other_digits;
    _other_digits = result._other_digits;
    result._other_digits = nullptr;
    _oldest_digit = result._oldest_digit;

    return *this;
}

bigint bigint::operator*(
    bigint const &multiplier) const
{
    bigint result = *this;

    return result *= multiplier;
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
    size_t shift) &
{

}

bigint bigint::operator<<(
    size_t shift) const
{

}

bigint &bigint::operator>>=(
    size_t shift) &
{

}

bigint bigint::operator>>(
    size_t shift) const
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