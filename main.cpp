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
#include "double_linked_list.h"

int main()
{
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
