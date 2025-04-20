#include <iostream>

class T
{

private:

    void copy(
        T const &from)
    {
        _array_size = from._array_size;
        _array = (int *)malloc(sizeof(int) * _array_size);
        if (_array == nullptr)
        {
            // TODO: throw an exception
        }

        memcpy(_array, from._array, sizeof(int) * _array_size);
    }

    void dispose()
    {
        std::cout << "Destructor called" << std::endl;
        free(_array);
        _array = nullptr;
    }

private:

    int *_array;
    size_t _array_size;

public:

    T(
        T const &obj)
    {
        copy(obj);
    }

    T(
        int const *values,
        size_t values_count):
            _array_size(values_count)
    {
        _array = (int *)malloc(sizeof(int) * values_count);
        if (_array == nullptr)
        {
            // TODO: throw an exception
        }

        memcpy(_array, values, sizeof(int) * values_count);
    }

    ~T()
    {
        dispose();
    }

    // a = b -> a.operator=(&b) -> operator=(&a, &b);
    // c = (a = b)

    T &operator=(
        T const &obj)
    {
        // 0. check equality of "this" pointer and param address
        // 1. dispose current object old state
        // 2. copy param state into current object
        // 3. return calling instance ref as retval - return *this;

        if (this == &obj)
        {
            return *this;
        }

        dispose();
        copy(obj);

        return *this;
    }

    T &foo()
    {
        std::cout << this << std::endl;
        int arr[10] = { 0 };
        T result(arr, 10);
        return result;
    }

};

class X
{

};

class Y
{
public:
    Y(X obj)
    {

    }
};

X foo(X obj)
{
    return obj;
}

class A
{

private:

    int *_a;

public:

    A():
        _a(new int[100])
    {
        std::cout << "A::A()" << std::endl;
    }

    virtual ~A()
    {
        std::cout << "A::~A()" << std::endl;
        delete[] _a;
        _a = nullptr;
    }

    A(
        A const &other):
            _a(new int[100])
    {
        std::cout << "A::A(A const &)" << std::endl;

        memcpy(_a, other._a, sizeof(int) * 100);
    }

    A &operator=(
        A const &other)
    {
        std::cout << "A &A::operator=(A const &)" << std::endl;

        if (this == &other)
        {
            std::cout << "Self assignment detected!!1!1" << std::endl;

            return *this;
        }

        memcpy(_a, other._a, sizeof(int) * 100);

        return *this;
    }

    A(
        A &&other) noexcept:
            _a(other._a)
    {
        std::cout << "A::A(A &&)" << std::endl;

        other._a = nullptr;
    }

    A &operator=(
        A &&other) noexcept
    {
        std::cout << "A &A::operator=(A &&)" << std::endl;

        if (this == &other)
        {
            std::cout << "Self assignment detected!!1!1" << std::endl;

            return *this;
        }

        delete [] _a;
        _a = other._a;
        other._a = nullptr;

        return *this;
    }

public:

    virtual void foo()
    {
        std::cout << "A::foo()" << std::endl;
    }

};

class B:
    public A
{
private:
    int *_b;
public:
    B(): _b(new int[100]) { std::cout << "B::ctor" << std::endl; }
    ~B() { delete[] _b; _b = nullptr; std::cout << "B::dtor" << std::endl; }
    B(B const &other) {  }
    B &operator=(B const &other) { return *this; }
    B(B &&other) noexcept {  }
    B &operator=(B &&other) noexcept { return *this; }
public:
    void foo() override { std::cout << "B::foo()" << std::endl; }
};

class C:
    public B
{
private:
    int *_c;
public:
    C(): _c(new int[100]) { std::cout << "C::ctor" << std::endl; }
    ~C() { delete[] _c; _c = nullptr; std::cout << "C::dtor" << std::endl; }
    C(C const &other) {  }
    C &operator=(C const &other) { return *this; }
    C(C &&other) noexcept {  }
    C &operator=(C &&other) noexcept { return *this; }
public:
    void foo() override { std::cout << "C::foo()" << std::endl; }
};

void foo(
    A *ptr)
{
    ptr->foo();
}

void punjk()
{
    B obj;
    foo(&obj);
}

class repeat
{

    ~repeat();

    repeat(
        repeat const &x);

    repeat &operator=(
        repeat const &puk);

};

void rule_of_5_demo()
{
    A obj;
    A copy = obj;
    A obj1 = std::move(copy);
}

int x = 10;

int &bar()
{
    return x;
}

int main()
{
    // x = x;
    // x = 10;
    // 10 = x;
    // bar() = 5;
    // rule_of_5_demo();

    // {
    //     A *obj_ptr = new C();
//
    //     delete obj_ptr;
    // }

    return 0;

    A* a = new A();
    a->foo();
    delete a;

    a = new B();
    a->foo();
    delete a;

    a = new C();
    a->foo();
    delete a;

    return 0;

    X obj;
    Y yObj = obj;
    X obj2 = obj;
    obj2 = obj;
    obj = obj2;

    int arr[10] = { 1, 2, 3, 7, 14, 23, -5, 6, 14, 23 };

    T x(arr + 4, 5);

    {
        T y = x;
    }

    x.foo();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
