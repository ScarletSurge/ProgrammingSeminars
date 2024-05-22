#include <iostream>

// class ul_class
// {
//
// private:
//
//     int _value;
//
// public:
//
//     explicit ul_class(
//         int value = 0)
//     {
//         _value = value;
//     }
//
//     ul_class(
//         ul_class const &obj)
//     {
//
//     }
//
//     ul_class operator=(
//         ul_class const &obj)
//     {
//
//     }
//
//     ~ul_class()
//     {
//
//     }
//
// public:
//
//     // getter, accessor
//     int get_value() const
//     {
//         return this->_value;
//     }
//
// private:
//
//     // setter, mutator
//     void set_value(
//         int new_value)
//     {
//         _value = new_value;
//     }
//
// };
//
// typedef struct ul_item
// {
//     int value;
//     struct ul_item *next;
// } ul_item, *p_ul_item;
//
// typedef struct ul
// {
// private:
//     p_ul_item head;
// };
//
// int insert_at_beginning(
//     ul_item **head,
//     int value_to_insert)
// {
//     ul_item *new_head = (ul_item *)malloc(sizeof(ul_item));
//     if (new_head == NULL)
//     {
//         return 1;
//     }
//
//     new_head->value = value_to_insert;
//     new_head->next = *head;
//     *head = new_head;
//
//     return 0;
// }

// Г. Шилдт "Самоучитель C++" (3 издание)
// Липпманн "C++. Базовый курс"
// cppreference.com

#include <math.h>

class sample
{
private:
    int value;
public:
    sample(
        int value)
    {
        this->value = value;
    }

    ~sample()
    {
        std::cout << "Destructor of sample called" << std::endl;
    }

};

inline sample foo()
{
    return sample(10);
}

#include <cstring>

class another_sample
{

private:

    char *_string_value;

public:

    another_sample(
        char const *string_value)
    {
        _string_value = new char[strlen(string_value) + 1];
        strcpy(_string_value, string_value);
    }

    another_sample(
        another_sample const &obj)
    {
        _string_value = new char[strlen(obj._string_value) + 1];
        strcpy(_string_value, obj._string_value);
    }

    another_sample &operator=(
        another_sample const &obj)
    {
        if (this != &obj)
        {
            delete[] _string_value;
            _string_value = new char[strlen(obj._string_value) + 1];
            strcpy(_string_value, obj._string_value);
        }

        return *this;
    }

    ~another_sample()
    {
        delete[] _string_value;
    }

};

#include <cstring>
#include <iomanip>
#include "double_linked_list.h"

void print_byte(
    unsigned char byte_value)
{
    for (int i = 0; i < 8; i++)
    {
        std::cout << ((byte_value >> (7 - i)) & 1);
    }
}

void dump_int_value(
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

#include "big_integer.h"
#include <fstream>

int main()
{
    big_integer first(std::vector<int> { 65536 });
    big_integer second(std::vector<int> { 65535 });
    (first *= second).dump_value(std::cout); std::cout << std::endl;
    (first += big_integer(std::vector<int> { 65536 })).dump_value(std::cout);
    return 0;
}

int main1337()
{
    auto const iterations_count = 20;
    int digits[1] = { 1 };
    big_integer x(digits, 1);
    std::ostream *stream;
    std::ofstream out("logs.txt");
    stream = &out;

    for (auto i = 2; i <= 10000; ++i)
    {
        digits[0] = i;
        x *= big_integer(digits, 1);
        //(*stream) << i << "! == ";
        x.dump_value(*stream);
        //(*stream) << std::endl;
    }

    std::cout << x;

    return 0;
    int values[] = { 1, 2, 3 };
    try
    {
        big_integer obj(values, 3);
        std::cout << obj.sign() << std::endl;
        big_integer obj2 = -obj;
        std::cout << obj2.sign() << std::endl;
        std::cout << (-obj2).sign() << std::endl;
        int x = 5;
    }
    catch (std::logic_error const &ex)
    {
        std::cout << "OMG LOL: \"" << ex.what() << '\"' << std::endl;
    }
    catch (std::bad_alloc const &ex)
    {
        std::cout << "хозяин, память плохо :/";
    }
    catch (std::exception const &ex)
    {

    }
    catch (int x)
    {

    }
    catch (...)
    {

    }

    return 0;
    dump_int_value(10);

    return 0;
    int i = 0;
    int **p = new int *[100000];
    try
    {
        while (true)
        {
            p[i++] = new int[10000000];
        }
    }
    catch (std::logic_error ex)
    {
        
    }
    catch (char *ex)
    {

    }
    catch (std::bad_alloc ex)
    {
        for (int j = 0; j < i; j++)
        {
            delete [] p[i];
        }

        delete[] p;
        p = nullptr;
        throw;
    }
    catch (...)
    {

    }

    {
        double_linked_list obj;
        for (int i = 0; i < 10; i++)
        {
            obj.insert_value(i, 1);
            obj.printf();
        }
    }
    // another_sample obj("12345");
    // another_sample obj2 = obj; // another_sample obj2(obj);
    // obj = obj;
    // (obj = obj2);
    // obj.operator=(obj2);


    //another_sample *objj = new another_sample;
    //delete objj;
//
    //{
    //    another_sample *obj_dyn = reinterpret_cast<another_sample *>(::operator new(sizeof(another_sample)));
    //    memset(obj_dyn, 114, sizeof(another_sample));
    //    new (obj_dyn) another_sample();
//
    //    // TODO: work with object...
//
    //    obj_dyn->~another_sample();
    //    ::operator delete(obj_dyn);
//
    //    //another_sample obj;
    //    //obj.~another_sample();
    //}
//
    //sample s(foo());
    //if (1)
    //{
    //    sample object1(10);
    //}
    //sample object2(20);

    return 0;
}

int main1()
{
    int x, y, z;
    //ul_class object;

    std::cout << "Input 3 integral values: ";
    std::cin >> x >> y >> z;
    std::cout << x << ' ' << y << ' ' << z << std::endl;

    //std::cout << object.get_value() << std::endl; // Fluent API

    return 0;
    // (a = (b = c));
    // ((a + b) + c);

    // ul u;
    // u.head = NULL;

    //ul_item *head = NULL;
    //printf("%p\n", head);
    //switch (insert_at_beginning(&head, 10))
    //{
    //    case 0:
    //        printf("%p", head);
    //        free(head);
    //        break;
    //    case 1:
    //        fprintf(stderr, "Memory allocation error occured!\n");
    //        return 1;
    //}
    //head = NULL;

    return 0;
}

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include <cstdlib>
#include <ctime>

std::string getWord(const std::string& str, size_t index) {
    std::istringstream iss(str);
    std::string word;
    for (auto i = 0; i < index + 1; ++i)
    {
        iss >> word;
    }
    return word;
}

int main3()
{
    std::fstream instr("instruction.txt");
    std::string line;
    std::string word;
    std::vector<int> A;
    try
    {
        if (instr.is_open())
        {
            while (std::getline(instr, line))
            {
                if (getWord(line, 0) == "Load")
                {
                    auto filePath = getWord(line, 2);
                    filePath.pop_back();
                    std::ifstream file(filePath);


                    if (!file.is_open())
                    {
                        throw std::logic_error("File not open");
                    }

                    std::string num;
                    while (file >> num)
                    {
                        try
                        {
                            size_t idx;
                            auto value = std::stoi(num, &idx);
                            if (idx != num.length())
                            {
                                throw std::invalid_argument("invalid value string representation");
                            }
                            A.push_back(value);
                        }
                        catch (std::invalid_argument const& ex)
                        {
                            throw std::logic_error("Invalid value of integer from input file!");
                        }
                    }
                    file.close();

                    for (int i = 0; i < A.size(); ++i)
                    {
                        std::cout << A[i] << " ";
                    }
                }

                if (getWord(line, 0) == "Save")
                {
                    auto lexem = getWord(line, 2);
                    lexem.pop_back();

                    std::ofstream file_output(lexem);

                    if (!file_output.is_open())
                    {
                        throw std::logic_error("File not open");
                    }

                    for (int i = 0; i < A.size(); ++i)
                    {
                        file_output << A[i] << " ";
                    }
                }

                if (getWord(line, 0) == "Rand")
                {
                    A.clear();

                    auto count = getWord(line, 2);
                    auto lb = getWord(line, 3);
                    auto rb = getWord(line, 4);

                    count.pop_back();
                    lb.pop_back();
                    rb.pop_back();

                    auto count_ = std::stoi(count);
                    auto lb_ = std::stoi(lb);
                    auto rb_ = std::stoi(rb);

                    srand(static_cast<unsigned int>(time(nullptr)));

                    for (int i = 0; i < count_; ++i)
                    {
                        A[i] = rand() % rb_ + lb_;
                    }
                    for (int i = 0; i < count_; ++i)
                    {
                        std::cout << A[i] << " ";
                    }

                }
            }
        }
    }
    catch (std::logic_error const& ex)
    {
        std::cout << ex.what();
        return 1;
    }

    return 0;
}