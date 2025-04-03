#ifndef COURSE1_CPP_RGU_BUGINT_H
#define COURSE1_CPP_RGU_BUGINT_H

#include <corecrt.h>
#include <iostream>

class bugint final
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

// big_integer("1234", 10) += 10;

// big_integer x;
// std::cout << x;
// x[2] = 10;

#endif //COURSE1_CPP_RGU_BUGINT_H