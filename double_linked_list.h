#ifndef PROGRAMMING_LANGUAGES_AND_METHODS_DOUBLE_LINKED_LIST_H
#define PROGRAMMING_LANGUAGES_AND_METHODS_DOUBLE_LINKED_LIST_H

#include <iostream>

class double_linked_list
{

private:

    struct node
    {
        int value;
        node *previous;
        node *next;
    };

public:

    struct node_info
    {
        int value;
        size_t position;
    };

private:

    node *_head;
    node *_tail;

public:

    double_linked_list();

public:

    virtual ~double_linked_list();

    double_linked_list(
        double_linked_list const &other);

    double_linked_list &operator=(
        double_linked_list const &other);

private:

    void copy(
        double_linked_list const &obj);

    void clear();

    // move constructor - if You want :)

    // move assignment operator - if You want :)

public:

    void insert_value(
        int value,
        size_t position);

    void printf();

    int remove_value(
        size_t position);

    int &get_value(
        size_t position);

public:

    double_linked_list &operator+=(
        node_info const &value);

    int operator-=(
        node_info const &value);

    int &operator[](
        size_t position);

public:

    friend std::ostream &operator<<(
        std::ostream& stream,
        double_linked_list const &to_print);

};

#endif //PROGRAMMING_LANGUAGES_AND_METHODS_DOUBLE_LINKED_LIST_H
