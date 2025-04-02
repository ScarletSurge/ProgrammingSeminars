#ifndef COURSE1_CPP_RGU_BIGINT_H
#define COURSE1_CPP_RGU_BIGINT_H

#include <corecrt.h>
#include <iostream>

class bigint final
{

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
        bigint &summand,
        int *words_multiplication_result_digits,
        unsigned int this_half_digit,
        unsigned int multiplier_half_digit,
        unsigned int shift_in_half_digits)
    {
        unsigned int words_multiplication_result_digit = this_half_digit * multiplier_half_digit;
        *words_multiplication_result_digits = *reinterpret_cast<int *>(&words_multiplication_result_digit);
        summand += (bigint(words_multiplication_result_digits, 2) << (HALF_DIGIT_SHIFT * shift_in_half_digits));
    }

private:

    int _oldest_digit;
    int *_other_digits;

public:

    ~bigint() noexcept;

    bigint(
        bigint const &other);

    bigint(
        bigint &&other) noexcept;

    bigint &operator=(
        bigint const &other);

    bigint &operator=(
        bigint &&other) noexcept;

public:

    bigint(
        int const *digits,
        size_t digits_count);

    bigint(
        char const *string_representation,
        size_t base);

private:

    inline int get_sign() const noexcept;

    inline size_t get_digits_count() const noexcept;

    unsigned int operator[](
        size_t index) const noexcept;

    int &operator[](
        size_t index);

    bigint &negate() &;

    bigint& invert() &;

public:

    bigint operator-() const;

    bigint &operator+=(
        bigint const &summand) &;

    bigint operator+(
        bigint const &summand) const;

    bigint &operator++();

    bigint const operator++(
        int);

    bigint &operator-=(
        bigint const &minuend) &;

    bigint operator-(
        bigint const &minuend) const;

    bigint &operator--();

    bigint const operator--(
        int);

    bigint &operator*=(
        bigint const &multiplier) &;

    bigint operator*(
        bigint const &multiplier) const;

    bigint &operator/=(
        bigint const &divisor) &;

    bigint operator/(
        bigint const &divisor) const;

    bigint &operator%=(
        bigint const &divisor) &;

    bigint operator%(
        bigint const &divisor) const;

    struct division_result
    {

        //bigint german;
        //bigint remainder;
//
        //division_result(
        //    bigint const &german,
        //    bigint const &remainder):
        //    german(german),
        //    remainder(remainder)
        //{
//
        //}

    };

    division_result division(
        bigint const &divisor) const;

public:

    bool operator==(
        bigint const &other) const;

    bool operator!=(
        bigint const &other) const;

public:

    bool operator<(
        bigint const &other) const;

    bool operator<=(
        bigint const &other) const;

    bool operator>(
        bigint const &other) const;

    bool operator>=(
        bigint const &other) const;

public:

    bigint operator~() const;

    bigint &operator&=(
        bigint const &other) &;

    bigint operator&(
        bigint const &other) const;

    bigint &operator|=(
        bigint const &other) &;

    bigint operator|(
        bigint const &other) const;

    bigint &operator^=(
        bigint const &other) &;

    bigint operator^(
        bigint const &other) const;

    bigint &operator<<=(
        size_t shift) &;

    bigint operator<<(
        size_t shift) const;

    bigint &operator>>=(
        size_t shift) &;

    bigint operator>>(
        size_t shift) const;

public:

    friend std::ostream &operator<<(
        std::ostream &stream,
        bigint const &value);

    friend std::istream &operator>>(
        std::istream &stream,
        bigint &value);

};

// big_integer("1234", 10) += 10;

// big_integer x;
// std::cout << x;
// x[2] = 10;

#endif //COURSE1_CPP_RGU_BIGINT_H