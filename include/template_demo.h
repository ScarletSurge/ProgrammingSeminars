#ifndef COURSE1_CPP_RGU_TEMPLATE_DEMO_H
#define COURSE1_CPP_RGU_TEMPLATE_DEMO_H

#include <iostream>

// template<
//     typename T>
// concept DefaultConstructible = std::is_default_constructible<T>();

template<
    typename T>
class stack final
{

private:

    T *_values;
    size_t _size;
    size_t _capacity;

public:

    explicit stack(
        size_t capacity = 16);

public:

    ~stack();

    stack(
        stack<T> const &other);

    stack<T> &operator=(
        stack<T> const &other);

    stack(
        stack<T> &&other) noexcept;

    stack<T> &operator=(
        stack<T> &&other) noexcept;

public:

    void push(
        T const &value);

    T &top() const;

    T pop();

    bool is_empty() const noexcept;

private:

    void throw_if_stack_is_empty() const
    {
        if (_size == 0)
        {
            throw std::out_of_range("stack is empty");
        }
    }

};

template<
    typename T>
stack<T>::stack(
    size_t capacity):
        _capacity(capacity),
        _size(0)
{
    _values = new T[_capacity];
}

template<
    typename T>
stack<T>::~stack()
{
    delete [] _values;
    _values = nullptr;
}

template<
    typename T>
stack<T>::stack(
    stack<T> const &other)
{

}

template<
    typename T>
stack<T> &stack<T>::operator=(
    stack<T> const &other)
{

}

template<
    typename T>
stack<T>::stack(
    stack<T> &&other) noexcept
{

}

template<
    typename T>
stack<T> &stack<T>::operator=(
    stack<T> &&other) noexcept
{

}

template<
    typename T>
void stack<T>::push(
    T const &value)
{
    if (_size == _capacity)
    {
        auto new_capacity = _capacity << 1;
        auto *new_values = new T[new_capacity];

        for (auto i = 0; i < _size; ++i)
        {
            new_values[i] = std::move(_values[i]);
        }

        delete[] _values;
        _values = new_values;
        _capacity = new_capacity;
    }

    _values[_size++] = value;
}

template<
    typename T>
T &stack<T>::top() const
{
    throw_if_stack_is_empty();

    return _values[_size - 1];
}

template<
    typename T>
T stack<T>::pop()
{
    throw_if_stack_is_empty();

    return _values[--_size];
}

template<
    typename T>
bool stack<T>::is_empty() const noexcept
{
    return _size == 0;
}

#endif //COURSE1_CPP_RGU_TEMPLATE_DEMO_H