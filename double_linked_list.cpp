#include "double_linked_list.h"

double_linked_list::double_linked_list():
    _head(nullptr),
    _tail(nullptr)
{

}

double_linked_list::~double_linked_list()
{
    clear();
}

double_linked_list::double_linked_list(
    double_linked_list const &other)
{
    copy(other);
}

double_linked_list &double_linked_list::operator=(
    double_linked_list const &other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}

void double_linked_list::copy(
    double_linked_list const &obj)
{
    _head = _tail = nullptr;
    node *iterator = obj._head;
    node *last_inserted = nullptr;
    while (iterator != nullptr)
    {
        node *new_item = new node;
        new_item->next = nullptr;
        new_item->value = iterator->value;
        if (_head == nullptr)
        {
            _head = new_item;
            _head->previous = nullptr;
        }
        else
        {
            if (last_inserted != nullptr)
            {
                last_inserted->next = new_item;
            }
            new_item->previous = last_inserted;
        }
        last_inserted = new_item;
        iterator = iterator->next;
    }
    _tail = last_inserted;
}

void double_linked_list::clear()
{
    node *iterator = _head;
    while (iterator != nullptr)
    {
        _head = _head->next;
        delete iterator;
        iterator = _head;
    }
    _tail = nullptr;
}

void double_linked_list::insert_value(
    int value,
    size_t position)
{
    node *new_node = new node;
    new_node->value = value;

    node *iterator = _head;
    for (int i = 0; i < position - 1; i++)
    {
        if (iterator == nullptr)
        {
            // raise an error
        }
        iterator = iterator->next;
    }

    if (iterator == nullptr)
    {
        new_node->next = nullptr;
        new_node->previous = _tail;
        if (_tail != nullptr)
        {
            _tail->next = new_node;
            _tail = new_node;
        }
        else
        {
            _head = _tail = new_node;
        }
    }
    else
    {
        node *next_node = iterator->next;
        new_node->next = next_node;
        new_node->previous = iterator;
        iterator->next = new_node;
        if (next_node != nullptr)
        {
            next_node->previous = new_node;
        }
    }
}

void double_linked_list::printf()
{
    node *iterator = _head;
    while (iterator != nullptr)
    {
        std::cout << iterator->value << ' ';
        iterator = iterator->next;
    }
    std::cout << std::endl;
}

int double_linked_list::remove_value(
    size_t position)
{

}

int &double_linked_list::get_value(
    size_t position)
{

}

double_linked_list &double_linked_list::operator+=(
    node_info const &value)
{

}

int double_linked_list::operator-=(
    node_info const &value)
{

}

int &double_linked_list::operator[](
    size_t position)
{

}

std::ostream &operator<<(
    std::ostream& stream,
    double_linked_list const &to_print)
{
    stream << to_print._head->value;
}