#include <iostream>

#include "include\figure.h"

class Y
{
private:
    int *p;
public:
    Y(): p(new int[10])
    {
        std::cout << "Y .ctor called" << std::endl;
    }

    virtual ~Y()
    {
        delete[] p;
        std::cout << "Y destructor called" << std::endl;
    }
};

class Z: public Y
{
private:
    int *t;
public:
    Z(): t(new int[10])
    {
        std::cout << "Z .ctor called" << std::endl;
    }

    ~Z()
    {
        delete[] t;
        std::cout << "Z destructor called" << std::endl;
    }
};

#pragma region smth

class X final
{
public:
    void foo() {}
};

void print_byte_into_stream(
    FILE *output_stream,
    unsigned char const *to_dump)
{
    for (auto i = 7; i >= 0; --i)
    {
        fprintf(output_stream, "%d", ((*to_dump >> i) & 1));
    }
}

void foo(
    X&& to_move)
{
    foo(std::forward<X &&>(to_move));
    foo(std::move(to_move));
}

void const_not_exists(
    int const *const_value_ptr)
{
    *const_cast<int *>(const_value_ptr) = 20;
}

#pragma endregion smth

int main()
{
    Y *obj = new Z();
    //
    delete obj;
    return 0;

    //Y objy;
    //objy.foo();
//
    //Z obj;
    //obj.bar();
    //obj.foo();

    // figure f;
    // f.mass_center();

    int value1 = 10;
    const_not_exists(&value1);
    std::cout << value1 << std::endl;

    X y;
    // std::cin >> y;
    // std::cout << y;

    X x;
    // copy constructor called
    X x2 = x;
    // copy constructor called (2)
    X x3(x2);

    // assignment operator
    x2 = x;
    x = x;

    // move constructor called
    X x4 = reinterpret_cast<X &&>(x);
    X x5 = std::move(x);

    std::pair<double, X> point;

    // std::cin >> x5;

    // move assignment called
    x4 = x5;
    x4 = std::move(x5);
    x5.foo();

    // static_cast<T */&>(expr)
    // dynamic_cast<T */&>(expr)
    // const_cast<T */&>(expr)
    // reinterpret_cast<T */&>(expr)

    int value = -10;
    unsigned char const * const v = (unsigned char const *)&value;

    for (auto i = 0; i < sizeof(int); ++i)
    {
        print_byte_into_stream(stdout, v + i);
        printf(" ");
    }

    return 0;
}
