#ifndef PROGRAMMING_LANGUAGES_AND_METHODS_BIG_INTEGER_H
#define PROGRAMMING_LANGUAGES_AND_METHODS_BIG_INTEGER_H

#include <corecrt.h>
#include <string>
#include <vector>

class big_integer final
{

private:

    int _oldest_digit;
    unsigned int *_other_digits;

public:

    big_integer(
        int *digits,
        size_t digits_count);

    big_integer(
        std::vector<int> const &digits);

    big_integer(
        std::string const &value,
        size_t base);

public:

    big_integer(
        big_integer const &other);

    big_integer &operator=(
        big_integer const &other);

    ~big_integer();

public:

    big_integer &operator+=(
        big_integer const &other);

    big_integer operator+(
        big_integer const &other) const;

    big_integer &operator-=(
        big_integer const &other);

    big_integer operator-(
        big_integer const &other) const;

    big_integer &operator*=(
        big_integer const &other);

    big_integer operator*(
        big_integer const &other) const;

    big_integer &operator/=(
        big_integer const &other);

    big_integer operator/(
        big_integer const &other) const;

    big_integer &operator%=(
        big_integer const &other);

    big_integer operator%(
        big_integer const &other) const;

    bool operator==(
        big_integer const &other) const;

    bool operator!=(
        big_integer const &other) const;

    bool operator<(
        big_integer const &other) const;

    bool operator<=(
        big_integer const &other) const;

    bool operator>(
        big_integer const &other) const;

    bool operator>=(
        big_integer const &other) const;

    big_integer operator~() const;

    big_integer operator&(
        big_integer const &other) const;

    big_integer operator|(
        big_integer const &other) const;

    big_integer operator^(
        big_integer const &other) const;

    big_integer operator<<(
        size_t shift_value) const;

    big_integer operator>>(
        size_t shift_value) const;

    friend std::ostream  &operator<<(
        std::ostream &stream,
        big_integer const &value);

    friend std::istream &operator>>(
        std::istream &stream,
        big_integer &value);

};

#endif //PROGRAMMING_LANGUAGES_AND_METHODS_BIG_INTEGER_H
