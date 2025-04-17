//#include "include/bugint.h"
#include "include/template_demo.h"

/*int bugint_demo(
    int argc,
    char *argv[])
{
    int value[10] = { INT_MIN, INT_MAX, 3, 4, 5, 6, INT_MIN };
    bugint test(value, 1);
    // test.~bugint();
    // new (&test) bugint(value, 1);

    std::cout << test << std::endl;
    //std::cout << ++test << std::endl;
    std::cout << -test << std::endl;

    return 0;
}*/

class int_wrapper final
{

private:

    int _value;

public:

    explicit int_wrapper(
        int value):
            _value(value)
    {

    }

public:

    int &get_value()
    {
        return _value;
    }

};

int stack_template_demo(
    int argc,
    char *argv[])
{
    stack<char> pukpuk;
    pukpuk.push((char)1);
    pukpuk.push((char)6);
    pukpuk.push((char)14);
    pukpuk.push((char)-8);

    while (!pukpuk.is_empty())
    {
        std::cout << pukpuk.pop() << std::endl;
    }

    return 0;
}

#include <vector>

int main(
    int argc,
    char *argv[])
{
    int_wrapper *obj_ptr = new int_wrapper(10);

    // 1. memory allocation
    // 2. constructor call
    int_wrapper *obj_ptr2 = reinterpret_cast<int_wrapper *>(::operator new(sizeof(int_wrapper)));
    new (obj_ptr2) int_wrapper(52);

    std::cout << obj_ptr << obj_ptr2;

    stack<int> int_values;
    stack<int> char_values;

    std::cout << typeid(int_values).hash_code() << std::endl;
    std::cout << typeid(char_values).hash_code() << std::endl;

    // return bugint_demo(argc, argv);
    return stack_template_demo(argc, argv);
}