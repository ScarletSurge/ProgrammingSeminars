#ifndef INTERPRETERS_SEARCH_TREE_H
#define INTERPRETERS_SEARCH_TREE_H

#include <iostream>
#include <functional>
#include <stack>
#include <vector>

#include "../allocator/allocator.h"
#include "../allocator/allocator_guardant.h"
#include "../associative_container/associative_container.h"
#include "../logger/logger.h"
#include "../logger/logger_guardant.h"
#include "../common/not_implemented.h"

template<
    typename tkey,
    typename tvalue>
class search_tree:
    public associative_container<tkey, tvalue>,
    protected allocator_guardant,
    protected logger_guardant
{

protected:

    struct common_node
    {

    public:

        typename associative_container<tkey, tvalue>::key_value_pair *keys_and_values;

        common_node **subtrees;

        size_t virtual_size;

    public:

        explicit common_node(
            typename associative_container<tkey, tvalue>::key_value_pair *keys_and_values,
            common_node **subtrees,
            size_t t);

        virtual ~common_node() noexcept;

    };

protected:

    std::function<int(tkey const &, tkey const &)> _keys_comparer;
    logger *_logger;
    allocator *_allocator;
    common_node *_root;

protected:

    common_node *create_node(
        size_t t) const
    {
        auto *keys_and_values = reinterpret_cast<typename associative_container<tkey, tvalue>::key_value_pair *>(allocate_with_guard(
            sizeof(typename associative_container<tkey, tvalue>::key_value_pair), 2 * t - 1));

        auto *subtrees = reinterpret_cast<typename search_tree<tkey, tvalue>::common_node **>(allocate_with_guard(
            sizeof(typename search_tree<tkey, tvalue>::common_node *), 2 * t));

        auto *node = reinterpret_cast<typename search_tree<tkey, tvalue>::common_node *>(allocate_with_guard(
            sizeof(typename search_tree<tkey, tvalue>::common_node), 1));
        allocator::construct(node, keys_and_values, subtrees, t);

        return node;
    }

    void destroy_node(
        common_node *to_destroy)
    {
        for (size_t i = 0; i < to_destroy->virtual_size; ++i)
        {
            allocator::destruct(to_destroy->keys_and_values + i);
        }

        deallocate_with_guard(to_destroy->keys_and_values);
        deallocate_with_guard(to_destroy->subtrees);
        allocator::destruct(to_destroy);
        deallocate_with_guard(to_destroy);
    }

    int node_find_path(
        typename search_tree<tkey, tvalue>::common_node const *node,
        tkey const &key,
        size_t left_bound_inclusive,
        size_t right_bound_inclusive);

    void node_insert(
        typename search_tree<tkey, tvalue>::common_node *node,
        typename associative_container<tkey, tvalue>::key_value_pair &&kvp,
        size_t subtree_index,
        typename search_tree<tkey, tvalue>::common_node *right_subtree);

    std::pair<typename search_tree<tkey, tvalue>::common_node *, typename associative_container<tkey, tvalue>::key_value_pair> node_split(
        typename search_tree<tkey, tvalue>::common_node *node,
        typename associative_container<tkey, tvalue>::key_value_pair &&kvp,
        size_t subtree_index,
        typename search_tree<tkey, tvalue>::common_node *right_subtree);

    void merge_nodes(
        typename search_tree<tkey, tvalue>::common_node *parent,
        size_t left_subtree_index);

protected:

    template<
        typename T>
    inline void swap(
        T &&one,
        T &&another)
    {
        T temp = std::move(one);
        one = std::move(another);
        another = std::move(temp);
    }

protected:

    std::stack<std::pair<typename search_tree<tkey, tvalue>::common_node **, int>> find_path(
        tkey const &key);

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

//region search_tree<tkey, tvalue>::node implementation

template<
    typename tkey,
    typename tvalue>
search_tree<tkey, tvalue>::common_node::common_node(
    typename associative_container<tkey, tvalue>::key_value_pair *keys_and_values,
    common_node **subtrees,
    size_t t):
    keys_and_values(keys_and_values),
    subtrees(subtrees),
    virtual_size(0)
{
    for (size_t i = 0; i < 2 * t; ++i)
    {
        subtrees[i] = nullptr;
    }
}

template<
    typename tkey,
    typename tvalue>
search_tree<tkey, tvalue>::common_node::~common_node() noexcept
{
    virtual_size = 0;
}

template<
    typename tkey,
    typename tvalue>
int search_tree<tkey, tvalue>::node_find_path(
    typename search_tree<tkey, tvalue>::common_node const *node,
    tkey const &key,
    size_t left_bound_inclusive,
    size_t right_bound_inclusive)
{
    int index;
    while (true)
    {
        index = (left_bound_inclusive + right_bound_inclusive) / 2;
        auto comparison_result = _keys_comparer(key, node->keys_and_values[index].key);
        if (comparison_result == 0)
        {
            return index;
        }

        if (left_bound_inclusive == right_bound_inclusive)
        {
            return -(index + (comparison_result < 0
                              ? 0
                              : 1) + 1);
        }

        if (comparison_result < 0)
        {
            right_bound_inclusive = index;
        }
        else
        {
            left_bound_inclusive = index + 1;
        }
    }
}

template<
    typename tkey,
    typename tvalue>
void search_tree<tkey, tvalue>::node_insert(
    typename search_tree<tkey, tvalue>::common_node *node,
    typename associative_container<tkey, tvalue>::key_value_pair &&kvp,
    size_t subtree_index,
    typename search_tree<tkey, tvalue>::common_node *right_subtree)
{
    allocator::construct(node->keys_and_values + node->virtual_size, std::move(kvp));
    node->subtrees[node->virtual_size + 1] = right_subtree;

    for (size_t i = 0; i < node->virtual_size - subtree_index; i++)
    {
        swap(std::move(node->keys_and_values[node->virtual_size - i]),
             std::move(node->keys_and_values[node->virtual_size - i - 1]));
        swap(std::move(node->subtrees[node->virtual_size + 1 - i]), std::move(node->subtrees[node->virtual_size - i]));
    }

    ++node->virtual_size;
}

template<
    typename tkey,
    typename tvalue>
std::pair<typename search_tree<tkey, tvalue>::common_node *, typename associative_container<tkey, tvalue>::key_value_pair> search_tree<tkey, tvalue>::node_split(
    typename search_tree<tkey, tvalue>::common_node *node,
    typename associative_container<tkey, tvalue>::key_value_pair &&kvp,
    size_t subtree_index,
    typename search_tree<tkey, tvalue>::common_node *right_subtree)
{
    size_t const t = (node->virtual_size + 1) / 2;
    size_t const mediant_index = t;

    if (subtree_index != mediant_index)
    {
        swap(std::move(kvp), std::move(node->keys_and_values[mediant_index - (subtree_index < mediant_index
                                                                              ? 1
                                                                              : 0)]));

        swap(std::move(right_subtree), std::move(node->subtrees[mediant_index + (subtree_index < mediant_index
                                                                                 ? 0
                                                                                 : 1)]));
    }

    auto index = mediant_index;
    int index_increment = index < subtree_index
                          ? 1
                          : -1;
    // TODO: kostyl o_O
    if (index_increment == -1)
    {
        --index;
    }

    if (index < subtree_index)
    {
        while (index + 1 != subtree_index)
        {
            swap(std::move(node->keys_and_values[index]), std::move(node->keys_and_values[index + 1]));

            swap(std::move(node->subtrees[index + 1]), std::move(node->subtrees[index + 2]));

            ++index;
        }
    }
    else
    {
        while (index != subtree_index)
        {
            swap(std::move(node->keys_and_values[index]), std::move(node->keys_and_values[index - 1]));

            swap(std::move(node->subtrees[index + 1]), std::move(node->subtrees[index]));

            --index;
        }
    }

    common_node *new_node = create_node(t);
    for (size_t i = 0; i < t - 1; i++)
    {
        allocator::construct(new_node->keys_and_values + i, std::move(node->keys_and_values[t + i]));
        allocator::destruct(node->keys_and_values + t + i);

        swap(std::move(new_node->subtrees[1 + i]), std::move(node->subtrees[t + 1 + i]));
    }

    new_node->subtrees[0] = right_subtree;

    new_node->virtual_size = t - 1;
    node->virtual_size = t;

    return std::make_pair(new_node, std::move(kvp));
}

template<
    typename tkey,
    typename tvalue>
void search_tree<tkey, tvalue>::merge_nodes(
    typename search_tree<tkey, tvalue>::common_node *parent,
    size_t left_subtree_index)
{
    // TODO: validations
    auto *left_subtree = parent->subtrees[left_subtree_index];
    auto *right_subtree = parent->subtrees[left_subtree_index + 1];

    allocator::construct(left_subtree->keys_and_values + left_subtree->virtual_size++, std::move(parent->keys_and_values[left_subtree_index]));
    for (size_t i = left_subtree_index; i < parent->virtual_size - 1; ++i)
    {
        search_tree<tkey, tvalue>::swap(std::move(parent->keys_and_values[i]), std::move(parent->keys_and_values[i + 1]));

        search_tree<tkey, tvalue>::swap(std::move(parent->subtrees[i + 1]), std::move(parent->subtrees[i + 2]));
    }

    allocator::destruct(parent->keys_and_values + --parent->virtual_size);

    for (size_t i = 0; i < right_subtree->virtual_size; i++)
    {
        allocator::construct(left_subtree->keys_and_values + left_subtree->virtual_size, std::move(right_subtree->keys_and_values[i]));
        left_subtree->subtrees[left_subtree->virtual_size++] = right_subtree->subtrees[i];
    }
    left_subtree->subtrees[left_subtree->virtual_size] = right_subtree->subtrees[right_subtree->virtual_size];

    destroy_node(right_subtree);
}

// endregion search_tree<tkey, tvalue>::node implementation

template<
    typename tkey,
    typename tvalue>
std::stack<std::pair<typename search_tree<tkey, tvalue>::common_node **, int>> search_tree<tkey, tvalue>::find_path(
    tkey const &key)
{
    std::stack<std::pair<typename search_tree<tkey, tvalue>::common_node **, int>> result;

    int index = -1;
    if (_root == nullptr)
    {
        result.push(std::make_pair(&_root, index));

        return result;
    }

    common_node **iterator = &_root;
    while (*iterator != nullptr && index < 0)
    {
        index = node_find_path(*iterator, key, 0, (*iterator)->virtual_size - 1);

        result.push(std::make_pair(iterator, index));

        if (index < 0)
        {
            iterator = (*iterator)->subtrees - index - 1;
        }
    }

    return result;
}

template<
    typename tkey,
    typename tvalue>
search_tree<tkey, tvalue>::search_tree(
    std::function<int(tkey const &, tkey const &)> keys_comparer,
    logger *logger,
    allocator *allocator):
    _keys_comparer(keys_comparer),
    _logger(logger),
    _allocator(allocator),
    _root(nullptr)
{

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

#endif //INTERPRETERS_SEARCH_TREE_H