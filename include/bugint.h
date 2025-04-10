#ifndef COURSE1_CPP_RGU_BUGINT_H
#define COURSE1_CPP_RGU_BUGINT_H

#include <corecrt.h>
#include <iostream>

class bugint final
{

public:

    class mathematical_uncertainty_exception:
        std::exception
    {

    };

    class division_by_zero_exception:
        std::exception
    {

    };

private:

    static unsigned int get_max(
        unsigned int first,
        unsigned int second) noexcept
    {
        return first > second
            ? first
            : second;
    }

private:

    static constexpr unsigned int HALF_DIGIT_SHIFT = (sizeof(int) << 2);

    static constexpr unsigned int SHIFT = (sizeof(int) << 2);

    static constexpr unsigned int MASK = (1 << SHIFT) - 1;

private:

    static unsigned int get_loword(
        unsigned int value)
    {
        return value & MASK;
    }

    static unsigned int get_hiword(
        unsigned int value)
    {
        return value >> SHIFT;
    }

private:

    static void addition_for_multiplication(
        bugint &summand,
        int *words_multiplication_result_digits,
        unsigned int this_half_digit,
        unsigned int multiplier_half_digit,
        unsigned int shift_in_half_digits)
    {
        unsigned int words_multiplication_result_digit = this_half_digit * multiplier_half_digit;
        *words_multiplication_result_digits = *reinterpret_cast<int *>(&words_multiplication_result_digit);
        summand += (bugint(words_multiplication_result_digits, 2) << (HALF_DIGIT_SHIFT * shift_in_half_digits));
    }

    int get_oldest_positive_value_bit_index() const noexcept
    {
        auto digits_count = get_digits_count();

        auto oldest_digit = _oldest_digit;
        int oldest_digit_oldest_bit_index = 0;
        while (oldest_digit != 0)
        {
            oldest_digit >>= 1;
            ++oldest_digit_oldest_bit_index;
        }
        return oldest_digit_oldest_bit_index + ((int)digits_count - 1) * (int)(sizeof(int) << 3) - 1;
    }

private:

    int _oldest_digit;
    int *_other_digits;

private:

    void dispose();

    void copy_from(
        bugint const &other);

    void move_from(
        bugint &&other);

public:

    ~bugint() noexcept;

    bugint(
        bugint const &other);

    bugint(
        bugint &&other) noexcept;

    bugint &operator=(
        bugint const &other);

    bugint &operator=(
        bugint &&other) noexcept;

private:

    bugint &init_with(
        int const *digits_array,
        size_t digits_count);

public:

    bugint(
        int const *digits,
        size_t digits_count);

    bugint(
        char const *string_representation,
        size_t base);

private:

    inline int get_sign() const noexcept;

    inline size_t get_digits_count() const noexcept;

    unsigned int operator[](
        size_t index) const noexcept;

    int &operator[](
        size_t index);

    bugint &negate() &;

    bugint& invert() &;

public:

    bugint operator-() const;

    bugint &operator+=(
        bugint const &summand) &;

    bugint operator+(
        bugint const &summand) const;

    bugint &operator++();

    bugint const operator++(
        int);

    bugint &operator-=(
        bugint const &minuend) &;

    bugint operator-(
        bugint const &minuend) const;

    bugint &operator--();

    bugint const operator--(
        int);

    bugint &operator*=(
        bugint const &multiplier) &;

    bugint operator*(
        bugint const &multiplier) const;

    bugint &operator/=(
        bugint const &divisor) &;

    bugint operator/(
        bugint const &divisor) const;

    bugint &operator%=(
        bugint const &divisor) &;

    bugint operator%(
        bugint const &divisor) const;

    class division_result final
    {

    private:

        bugint *_german;
        bugint *_remainder;

    public:

        division_result(
            bugint const &german,
            bugint const &remainder):
                _german(new bugint(german)),
                _remainder(new bugint(remainder))
        {

        }

    public:

        // TODO: implement rule of 5

        ~division_result()
        {
            delete _german; _german = nullptr;
            delete _remainder; _remainder = nullptr;
        }

    public:

        bugint get_german() const
        {
            return *_german;
        }

        bugint get_remainder() const
        {
            return *_remainder;
        }

    };

    division_result division(
        bugint const &divisor) const;

public:

    bool operator==(
        bugint const &other) const;

    bool operator!=(
        bugint const &other) const;

public:

    bool operator<(
        bugint const &other) const;

    bool operator<=(
        bugint const &other) const;

    bool operator>(
        bugint const &other) const;

    bool operator>=(
        bugint const &other) const;

public:

    bugint operator~() const;

    bugint &operator&=(
        bugint const &other) &;

    bugint operator&(
        bugint const &other) const;

    bugint &operator|=(
        bugint const &other) &;

    bugint operator|(
        bugint const &other) const;

    bugint &operator^=(
        bugint const &other) &;

    bugint operator^(
        bugint const &other) const;

    bugint &operator<<=(
        size_t shift) &;

    bugint operator<<(
        size_t shift) const;

    bugint &operator>>=(
        size_t shift) &;

    bugint operator>>(
        size_t shift) const;

public:

    friend std::ostream &operator<<(
        std::ostream &stream,
        bugint const &value);

    friend std::istream &operator>>(
        std::istream &stream,
        bugint &value);

};

#endif //COURSE1_CPP_RGU_BUGINT_H