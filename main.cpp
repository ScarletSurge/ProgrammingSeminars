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

int main()
{
    X obj;
    X obj2 = obj;
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
