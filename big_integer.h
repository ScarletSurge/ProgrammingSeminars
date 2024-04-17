#ifndef PROGRAMMING_LANGUAGES_AND_METHODS_BIG_INTEGER_H
#define PROGRAMMING_LANGUAGES_AND_METHODS_BIG_INTEGER_H

#include <corecrt.h>
#include <string>
#include <vector>
#include <iostream>

class big_integer final
{

private:

    static void print_byte(
        unsigned char byte_value)
    {
        for (int i = 0; i < 8; i++)
        {
            std::cout << ((byte_value >> (7 - i)) & 1);
        }
    }

    static void dump_int_value(
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

private:

    int _oldest_digit;
    unsigned int *_other_digits;

private:

    big_integer &change_sign();

public:

    bool sign() const noexcept;

    bool is_equal_to_zero() const noexcept;

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

    big_integer operator-() const;

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

    friend std::ostream &operator<<(
        std::ostream &stream,
        big_integer const &value);

    friend std::istream &operator>>(
        std::istream &stream,
        big_integer &value);

};

#endif //PROGRAMMING_LANGUAGES_AND_METHODS_BIG_INTEGER_H
