#include <iostream>

class demo_class
{

private:

    int *_values;
    size_t _values_count;

public:

    demo_class(int *values, size_t values_count)
            : _values_count(values_count)
    {
        printf("constructor work...\n");

        _values = new int[_values_count];
        memcpy(this->_values, values, _values_count * sizeof(int));
    }

    demo_class(demo_class const & obj)
            : _values_count(obj._values_count)
    {
        printf("copy constructor work...\n");

        _values = new int[obj._values_count];
        memcpy(_values, obj._values, _values_count * sizeof(int));
    }

    demo_class& operator=(demo_class const & obj)
    {
        printf("operator= work...\n");

        // c = a = b
        // a.operator=(&b)
        // a::operator=(&a, &b);

        delete[] _values;
        _values_count = obj._values_count;
        _values = new int[_values_count];
        memcpy(_values, obj._values, _values_count * sizeof(int));
        return *this;
    }

    virtual ~demo_class()
    {
        printf("destructor work...\n");

        delete[] _values;
    }
/*public:
    int _public;
protected:
    int _protected;*/
};

/*class a
{
public:
    a(int value)
    {

    }
    a(int value, double by_def = 0.0)
    {

    }
};*/

/*class demo_class_inherited : protected demo_class
{
    void foo()
    {
        _public = 10;
        _protected = 20;
        _values = nullptr;
    }
};*/

int main(
        int argc,
        char *argv[])
{
    {
        int arr[5] = { 1, 2, 3, 4, 5 };
        demo_class demo(arr, 5);

        demo_class demo2 = demo;
        demo_class demo3(demo);

        demo = demo3 = demo2/* = ...*/;

        demo2 = demo;
    }

    int values[5] = { 1, 2, 3, 4, 5 };
    demo_class *demo_heap = new demo_class(values, 5);

    // TODO: work with demo_class instance

    delete demo_heap;
}