#include <stdexcept>
#include <vector>

#include "big_integer.h"

// #define max(x, y) ((x) > (y) ? (x) : (y))

void big_integer::clear()
{
    delete[] _other_digits;
    _other_digits = nullptr;
}

void big_integer::copy(
    big_integer const &other)
{
    _oldest_digit = other._oldest_digit;
    _other_digits = nullptr;
    if (other._other_digits == nullptr)
    {
        return;
    }

    _other_digits = new unsigned int[*other._other_digits];
    memcpy(_other_digits, other._other_digits, sizeof(unsigned int) * (*other._other_digits));
}

void big_integer::print_byte(
    unsigned char byte_value)
{
    for (int i = 0; i < 8; i++)
    {
        std::cout << ((byte_value >> (7 - i)) & 1);
    }
}

void big_integer::dump_int_value(
    int value)
{
    unsigned char *p = (unsigned char *)&value;
    // printf("0x%p, 0x%p\n", p, &value);
    // printf("%d %d", sizeof(p), sizeof(&value));

    for (int i = 0; i < sizeof(int); i++)
    {
        print_byte(*p++);
        std::cout << ' ';
    }
}

big_integer &big_integer::change_sign()
{
    _oldest_digit ^= (1 << ((sizeof(int) << 3) - 1));

    return *this;
}

inline int big_integer::get_digits_count() const noexcept
{
    return static_cast<int>(1 + (_other_digits == nullptr
         ? 0
         : *_other_digits - 1));
}

inline bool big_integer::sign() const noexcept
{
    return (*reinterpret_cast<unsigned int const *>(&_oldest_digit) >> ((sizeof(int) << 3) - 1)) == 1;
}

inline bool big_integer::is_equal_to_zero() const noexcept
{
    return _oldest_digit == 0 && _other_digits == nullptr;
}

inline unsigned int big_integer::get_digit(
    int position) const noexcept
{
    if (_other_digits == nullptr)
    {
        return position == 0
            ? _oldest_digit
            : 0;
    }

    int const digits_count = get_digits_count();
    if (position < digits_count - 1)
    {
        return _other_digits[position + 1];
    }

    if (position == digits_count - 1)
    {
        return _oldest_digit;
    }

    return 0;
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
    big_integer const &other)
{
    copy(other);
}

big_integer &big_integer::operator=(
    big_integer const &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

big_integer::~big_integer()
{
    clear();
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

    auto const first_value_digits_count = get_digits_count();
    auto const second_value_digits_count = other.get_digits_count();
    auto const digits_count = std::max(first_value_digits_count, second_value_digits_count);

    unsigned int operation_result = 0;

    constexpr int shift = sizeof(unsigned int) << 2;
    constexpr int mask = (1 << shift) - 1;

    auto *result_digits = new unsigned int[digits_count];

    for (int i = 0; i < digits_count; ++i)
    {
        unsigned int first_value_digit = get_digit(i);
        unsigned int second_value_digit = other.get_digit(i);
        result_digits[i] = 0;

        for (int j = 0; j < 2; ++j)
        {
            operation_result += (first_value_digit & mask) + (second_value_digit & mask);
            first_value_digit >>= shift;
            second_value_digit >>= shift;
            result_digits[i] |= (operation_result & mask) << (shift * j);
            operation_result >>= shift;
        }
    }

    int const result_digits_count = operation_result + digits_count;


    if (result_digits_count == get_digits_count())
    {
        _oldest_digit = result_digits[result_digits_count - 1];
        for (auto i = result_digits_count - 1; i > 0; --i)
        {
            result_digits[i] = result_digits[i - 1];
        }
        *result_digits = result_digits_count;
        clear();
        _other_digits = result_digits;
        return *this;
    }

    unsigned int *temp = new unsigned int[result_digits_count];
    memcpy(temp + 1, result_digits, sizeof(unsigned int) * digits_count);
    *temp = result_digits_count;
    _oldest_digit = operation_result;
    clear();
    _other_digits = temp;
    return *this;
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
    return !(*this == other);
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