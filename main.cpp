#include <iostream>
#include <cstring>
#include <fstream>

// TODO: this is not good
// using namespace std;

// Fluent API

// public, protected, private

#define NULL ((void *)0)
#define NULL (0)

class x
{
private:
    char *_x;
public:

    //x(char const *p)
    //{
    //    std::cout << "Constructor is working..." << std::endl;
    //    _x = (char *)malloc(sizeof(char) * (strlen(p) + 1));
    //    // TODO: validation
    //    strcpy(_x, p);
    //}

    ~x()
    {

        std::cout << "Destructor working..." << std::endl;
        free(_x);
        _x = nullptr;
        // this->_x = nullptr;
    }

    //void foo()
    //{
    //    if (_x == nullptr)
    //    {
    //        _x = (char *)malloc(sizeof(char) * 100);
    //    }
    //}
};

// struct my_struct
// {
// //public:
//     void *a;
// };

class my_class
{

private:

    char *_str;

public:

    my_class(
        char const *str)
    {
        std::cout << "Constructor working..." << std::endl;
        //if ((_str = (char *)malloc(sizeof(char) * (strlen(str) + 1))) == nullptr)
        {
            throw 52;
        }
        strcpy(_str, str);
    }

    ~my_class()
    {
        std::cout << "Destructor working..." << std::endl;
        free(_str);
        _str = nullptr;
    }

public:

    my_class(
        my_class const &obj)
    {
        std::cout << "Copy constructor working..." << std::endl;

        // my_class x = y;
        _str = (char *)malloc(sizeof(char) * (strlen(obj._str) + 1));
        strcpy(_str, obj._str);
    }

    my_class &operator=(
        my_class const &obj)
    {
        if (this == &obj)
        {
            return *this;
        }

        free(_str);
        _str = (char *)malloc(sizeof(char) * (strlen(obj._str) + 1));
        strcpy(_str, obj._str);

        return *this;
    }

};

//void foo(
//    int &x)
//{
//
//}

void bar(int *& ptr_ref)
{
    *ptr_ref = 10;
}

void ref()
{
    int a = 10;
    int b = 20;
    int *p = &a;
    int &r = a;
    r = b;

    int *p1 = (int *)realloc(p, sizeof(int) * 10);

    *p = 20;
    r = 20;

    //foo(*p);
    //foo(r);
    //a = b = c;
    // int *p
    *p = 20;
}

int &f()
{

}

class X{};

my_class copy_constructor(
    my_class obj)
{
    my_class obj2("98765432");
    obj = obj2;
    return my_class(obj);
}

// my_class::my_class(char const *) x
// int puksrenjk() x
// int main(int, char *[]) <- вы находитесь здесь

int puksrenjk()
{
    int *p = (int *)malloc(sizeof(char) * 100);

    try
    {
        my_class a("12345");
    }
    catch (int value)
    {
        std::cout << "Handling of exception of type `int` in context of puksrenjk() function" << std::endl;
        free(p);
        // throw value; - is the same as below
        throw (double)value; // aggregate_exception
    }

    free(p);
    return 0;
}

class pukpuk
{
public:
    void func(
        int value,
        int value2 = 52)
    {
        std::cout << value << ' ' << value2 << std::endl;
    }
};

// f(a, b, c): a + b + c
// f(a, b, c) -> f'(a, b) + c -> f''(a) + b + c
// Haskell Curry

void default_parameters_demo()
{
    pukpuk().func(52); // func(52);
}

void interaction_with_files_demo()
{
    std::ifstream in("in.txt");
    std::ifstream in2;

    std::ofstream out("out.txt");
    std::ofstream out2;

    if (!out.is_open())
    {
        // TODO: raise an exception instance
    }
    out << "interaction_with_files_demo" << std::endl;
}

void rule_of_3_demo()
{
    class T
    {
    public:
        T(int = 10909){}
    };

    T obj(1);
    T obj2 = obj;

    // malloc, calloc, realloc - free
    void *dyn = new T(150); delete dyn;
    T **dyn_arr = new T*[10]; delete[] dyn_arr;

    T *mem = reinterpret_cast<T *>(::operator new(sizeof(T)));
    new (mem) T(150);
    // TODO: work with object under mem pointer

    mem->~T();
    ::operator delete(reinterpret_cast<void *>(mem));
}

class T
{
public:
    T(int = 0)
    {

    }
};

class base
{

protected:

    T _field;

public:

    base(base const &) = delete;

public:

    explicit base(
        T const &field):
        _field(field)
    {
        _field = field;
        std::cout << "base::base() called..." << std::endl;
    }

    virtual ~base() noexcept = default;

public:

    virtual void foo()
    {
        std::cout << "base::foo() called..." << std::endl;
    }

};

class X1{};

class derived:
    public base
{

public:

    derived();

    void bar()
    {
        std::cout << "derived::bar() called..." << std::endl;
        foo();
        _field = T();
    }

    void foo() override
    {
        std::cout << "derived::foo() called..." << std::endl;
    }

    ~derived() noexcept;

};

derived::derived():
    base(T())
{
    std::cout << "derived::derived() called..." << std::endl;
}

derived::~derived() noexcept
{
    std::cout << "derived::~derived() called..." << std::endl;
}

void inheritance_demo()
{
    //std::cout << sizeof(X1) << std::endl;
    base *x = new derived();
    x->foo();
    delete x;

    derived d1;

    //void funct(base const &obj)
    //{
    //    int const cnst = 10;
    //    //const_cast<base *>(&obj)->foo() ;//.foo();
    //    *const_cast<int *>(&cnst) = 20;//.foo();
    //}
}

class number final
{

private:

    int _number;

public:

    explicit number(
        int value):
        _number(value)
    {

    }

public:

    number &operator+=(
        number const &value);

    // RVO/NRVO
    number operator+(
        number value) const;

    //friend number operator*(
    //    double value,
    //    number const &my_value);
    //
    //number operator*(
    //    double value) const; // n1 * 10; // 10 * n1;

    //[[nodiscard]] inline void *foo() { std::cout << "puk srenjk"; return ::operator new(100); } // Tango tree

};

number &number::operator+=(
    number const &value)
{
    _number += value._number;
    return *this;
}

// RVO/NRVO
//number number::operator+(
//    number const &value) const
//{
//    //number copy = *this;
//    //copy += value;
//    //return copy;
//
//    return number(*this) += value;
//}

number number::operator+(
    number value) const
{
    return value += *this;
}

void operators_overloading_demo()
{
    // n1.operator+=(n2)
    number n1(20), n2(32);
    auto a = n1 += n2;
    auto sum = n1 + n2;

    //number *n = new number(10);
    //auto *p = n->foo();
//
    //matrix m1, m2;
    //m1 + m2; // m1.add(m2); // add(m1, m2);
    //stream << m1;
    //stream2 >> m2;
    //++m1
    //m1(i, j);
}

int main(
    int argc,
    char *argv[])
{

    // default_parameters_demo();
    // interaction_with_files_demo();
    // rule_of_3_demo();
    inheritance_demo();
    operators_overloading_demo();
    return 0;

    try
    {
        std::cout << puksrenjk() << std::endl;
        //my_class a("12345");
//
        //my_class b = a;
        //my_class c(a);
//
        //a = b;
        //b = b;
        //obj3 = obj2;
        //X obj4(obj2);

        std::cout << "inside try/catch block..." << std::endl;
    }
    catch (int srenjk)
    {
        std::cout << "Handling of exception of type `int` in context of main() function" << std::endl;
    }
    catch (double puk)
    {
        std::cout << "Handling of exception of type `double` in context of main() function" << std::endl;
    }
    std::cout << "after try/catch block..." << std::endl;

    //ref();
    //{
    //    x obj;
    //    // TODO: working with obj...
    //}

    int a = 10;
    a = 20;

    std::cout << "Hello, world!" << std::endl;

    return 0;
}

void foo()
{
    FILE *f = fopen("123.txt", "r");
    char c = fgetc(f);
    fclose(f);
}