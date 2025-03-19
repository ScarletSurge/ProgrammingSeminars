#ifndef COURSE1_CPP_RGU_BIGINT_H
#define COURSE1_CPP_RGU_BIGINT_H

#include <corecrt.h>
#include <iostream>

class bigint final
{

private:

    int _oldest_digit;
    int *_other_digits;

public:

    ~bigint() noexcept;

    bigint(
        bigint const &other);

    bigint &operator=(
        bigint const &other);

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

    int &operator[](
        size_t index);

public:

    bigint &operator+=(
        bigint const &summand) &;

    bigint operator+(
        bigint const &summand) const;

    bigint &operator++();

    bigint operator++(
        int);

    bigint &operator-=(
        bigint const &minuend) &;

    bigint operator-(
        bigint const &minuend) const;

    bigint &operator--();

    bigint operator--(
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

        bigint german;
        bigint remainder;

        division_result(
            bigint const &german,
            bigint const &remainder):
            german(german),
            remainder(remainder)
        {

        }

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
        bigint const &other) &;

    bigint operator<<(
        bigint const &other) const;

    bigint &operator>>=(
        bigint const &other) &;

    bigint operator>>(
        bigint const &other) const;

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