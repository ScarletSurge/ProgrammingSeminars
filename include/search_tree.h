#ifndef COURSE1_CPP_RGU_SEARCH_TREE_H
#define COURSE1_CPP_RGU_SEARCH_TREE_H

#include <iostream>
#include <functional>
#include <stack>
#include <vector>

#include "allocator.h"
#include "allocator_guardant.h"
#include "associative_container.h"
#include "logger.h"
#include "logger_guardant.h"
#include "not_implemented.h"

template<
    typename tkey,
    typename tvalue>
class search_tree:
    public associative_container<tkey, tvalue>,
    protected allocator_guardant,
    protected logger_guardant
{

protected:

    std::function<int(tkey const &, tkey const &)> _keys_comparer;

protected:

    logger *_logger;

    allocator *_allocator;

protected:

    explicit search_tree(
        std::function<int(tkey const &, tkey const &)> keys_comparer = std::less<tkey>(),
        logger *logger = nullptr,
        allocator *allocator = nullptr);

public:

    virtual std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive) = 0;

protected:

    [[nodiscard]] inline allocator *get_allocator() const final;

    [[nodiscard]] inline logger *get_logger() const final;

};

template<
    typename tkey,
    typename tvalue>
search_tree<tkey, tvalue>::search_tree(
    std::function<int(tkey const &, tkey const &)> keys_comparer,
    logger *logger,
    allocator *allocator):
    _keys_comparer(std::move(keys_comparer)),
    _logger(logger),
    _allocator(allocator)
{
    debug_with_guard("Called search_tree<tkey, tvalue>::search_tree(std::function<int(tkey const &, tkey const &)>, logger *, allocator *)");
}

template<
    typename tkey,
    typename tvalue>
[[nodiscard]] inline allocator *search_tree<tkey, tvalue>::get_allocator() const
{
    return _allocator;
}

template<
    typename tkey,
    typename tvalue>
[[nodiscard]] inline logger *search_tree<tkey, tvalue>::get_logger() const
{
    return _logger;
}

#endif //COURSE1_CPP_RGU_SEARCH_TREE_H
