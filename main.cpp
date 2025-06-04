//#include "include/bugint.h"
#include "include/template_demo.h"
#include "include/allocator.h"
#include "include/allocator_sorted_list.h"
#include "include/logger_builder.h"
#include "include/client_logger_builder.h"
#include "include/logger.h"
#include "include/binary_search_tree.h"

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

#include "include/allocator_sorted_list.h"

void sorted_list_allocator_demo()
{
    allocator *alloc = new allocator_sorted_list(10000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::the_worst_fit);

    int *arr = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 15));

    allocator_sorted_list moved(std::move(*dynamic_cast<allocator_sorted_list *>(alloc)));

    moved.deallocate(arr);

    delete alloc;
}

int logger_demo(
    int argc,
    char *argv[])
{
    // /config/pukpuk/streams[0]/severities[1]
    logger *log = client_logger_builder()
        .transform_with_configuration("config.json", "config:pukpuk")
        ->add_file_stream("file1.txt", logger::severity::information)
        ->add_file_stream("file2.txt", logger::severity::warning)
        ->add_console_stream(logger::severity::information)
        ->add_console_stream(logger::severity::critical)
        ->build();

    log
        ->trace("trace log")
        ->debug("debug log")
        ->information("information log")
        ->warning("warning log")
        ->error("error log")
        ->critical("where are labs?!")
        ->critical("smoking?");

    delete log;

    return 0;
}

int binary_search_tree_demo(
    int argc,
    char *argv[])
{
    associative_container<int, int> *tree = new binary_search_tree<int, int>((std::less<>()));

    tree->insert(1, 2);

    auto moved_tree = std::move(*dynamic_cast<binary_search_tree<int, int> *>(tree));

    delete tree;

    return 0;
}

int main(
    int argc,
    char *argv[])
{
    // sorted_list_allocator_demo();
    //return logger_demo(argc, argv);
    return binary_search_tree_demo(argc, argv);

    return 0;

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