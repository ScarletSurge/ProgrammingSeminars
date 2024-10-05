#ifndef PROGRAMMINGSEMINARS_HEX_H
#define PROGRAMMINGSEMINARS_HEX_H

#include <iostream>

class X final
{

};

class hex final
{

private:

    unsigned char *_data;
    size_t _digits_count;

public:

    hex();
    hex(const std::string &string_representation);

public:

    // rule of 5
    // destructor
    ~hex() noexcept;
    // copy constructor
    hex(hex const &other);
    // assignment operator
    hex &operator=(hex const &other);
    // move constructor
    hex(hex &&other) noexcept;
    // move assignment
    hex &operator=(hex &&other) noexcept;

public:

    // a += b
    hex& operator+=(hex const &summand);

    friend hex operator+(hex const &initial, int value);
    friend hex operator+(int value, hex const &initial);



// initial += value
// initial.operator+=(value)
// operator+=(initial, value)
    // a + b
    hex operator+(hex const &summand) const;

    hex operator+(hex summand) const; //

    hex operator+(int value) const;

    friend hex operator+(int value, hex const &value2);

    // return value optimization (RVO)

};

#endif //PROGRAMMINGSEMINARS_HEX_H
