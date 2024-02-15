#include <iostream>

class ul_class
{

private:

    int _value;

public:

    explicit ul_class(
        int value = 0)
    {
        _value = value;
    }

    ul_class(
        ul_class const &obj)
    {

    }

    ul_class operator=(
        ul_class const &obj)
    {

    }

    ~ul_class()
    {

    }

public:

    // getter, accessor
    int get_value() const
    {
        return this->_value;
    }

private:

    // setter, mutator
    void set_value(
        int new_value)
    {
        _value = new_value;
    }

};

typedef struct ul_item
{
    int value;
    struct ul_item *next;
} ul_item, *p_ul_item;

typedef struct ul
{
private:
    p_ul_item head;
};

int insert_at_beginning(
    ul_item **head,
    int value_to_insert)
{
    ul_item *new_head = (ul_item *)malloc(sizeof(ul_item));
    if (new_head == NULL)
    {
        return 1;
    }

    new_head->value = value_to_insert;
    new_head->next = *head;
    *head = new_head;

    return 0;
}

// Г. Шилдт "Самоучитель C++" (3 издание)
// Липпманн "C++. Базовый курс"
// cppreference.com

#include <math.h>

int main()
{
    int x, y, z;
    ul_class object;

    std::cout << "Input 3 integral values: ";
    std::cin >> x >> y >> z;
    std::cout << x << ' ' << y << ' ' << z << std::endl;

    std::cout << object.get_value() << std::endl; // Fluent API

    return 0;
    // (a = (b = c));
    // ((a + b) + c);

    // ul u;
    // u.head = NULL;

    ul_item *head = NULL;
    printf("%p\n", head);
    switch (insert_at_beginning(&head, 10))
    {
        case 0:
            printf("%p", head);
            free(head);
            break;
        case 1:
            fprintf(stderr, "Memory allocation error occured!\n");
            return 1;
    }
    head = NULL;

    return 0;
}
