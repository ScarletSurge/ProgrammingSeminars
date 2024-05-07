#ifndef INTERPRETERS_B_TREE_H
#define INTERPRETERS_B_TREE_H

#include "search_tree.h"

template<
    typename tkey,
    typename tvalue>
class b_tree final:
    public search_tree<tkey, tvalue>
{

private:

    void insert_inner(
        typename associative_container<tkey, tvalue>::key_value_pair &&kvp);

public:

    void insert(
        tkey const &key,
        tvalue const &value) override;

    void insert(
        tkey const &key,
        tvalue &&value) override;

    tvalue &obtain(
        tkey const &key) override;

    tvalue dispose(
        tkey const &key) override;

    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive) override;

public:

    class infix_iterator final
    {

    private:

        std::stack<std::pair<typename search_tree<tkey, tvalue>::common_node *, int>> _path;

    public:

        explicit infix_iterator(
            typename search_tree<tkey, tvalue>::common_node *subtree_root);

    public:

        bool operator==(
            infix_iterator const &other) const noexcept;

        bool operator!=(
            infix_iterator const &other) const noexcept;

        infix_iterator &operator++();

        infix_iterator operator++(
            int not_used);

        std::tuple<size_t, size_t, tkey const &, tvalue &> operator*() const;

    };

    class infix_const_iterator final
    {

    private:

        typename b_tree<tkey, tvalue>::infix_iterator _iterator;

    public:

        explicit infix_const_iterator(
            typename search_tree<tkey, tvalue>::common_node *subtree_root);

    public:

        bool operator==(
            infix_const_iterator const &other) const noexcept;

        bool operator!=(
            infix_const_iterator const &other) const noexcept;

        infix_const_iterator &operator++();

        infix_const_iterator operator++(
            int not_used);

        std::tuple<size_t, size_t, tkey const &, tvalue const &> operator*() const;

    };

private:

    size_t _t;

public:

    explicit b_tree(
        size_t t,
        std::function<int(tkey const &, tkey const &)> keys_comparer = std::less<tkey>(),
        allocator *allocator = nullptr,
        logger *logger = nullptr);

public:

    b_tree(
        b_tree<tkey, tvalue> const &other);

    b_tree<tkey, tvalue> &operator=(
        b_tree<tkey, tvalue> const &other);

    b_tree(
        b_tree<tkey, tvalue> &&other) noexcept;

    b_tree<tkey, tvalue> &operator=(
        b_tree<tkey, tvalue> &&other) noexcept;

    ~b_tree();

private:

    inline size_t get_min_keys_count() const noexcept;

    inline size_t get_max_keys_count() const noexcept;

public:

    infix_iterator begin_infix() const noexcept;

    infix_iterator end_infix() const noexcept;

    infix_const_iterator cbegin_infix() const noexcept;

    infix_const_iterator cend_infix() const noexcept;

private:

    typename search_tree<tkey, tvalue>::common_node *copy(
        typename search_tree<tkey, tvalue>::common_node *node);

    typename search_tree<tkey, tvalue>::common_node *copy();

    void clear(
        typename search_tree<tkey, tvalue>::common_node *node);

    void clear();

};

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue>::infix_iterator::infix_iterator(
    typename search_tree<tkey, tvalue>::common_node *subtree_root)
{
    while (subtree_root != nullptr)
    {
        _path.push(std::make_pair(subtree_root, 0));
        subtree_root = subtree_root->subtrees[0];
    }
}

template<
    typename tkey,
    typename tvalue>
bool b_tree<tkey, tvalue>::infix_iterator::operator!=(
    b_tree::infix_iterator const &other) const noexcept
{
    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue>
bool b_tree<tkey, tvalue>::infix_iterator::operator==(
    b_tree::infix_iterator const &other) const noexcept
{
    if (_path.empty() && other._path.empty())
    {
        return true;
    }

    if (_path.empty() ^ other._path.empty())
    {
        return false;
    }

    return _path.top() == other._path.top();
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_iterator &b_tree<tkey, tvalue>::infix_iterator::operator++()
{
    if (_path.empty())
    {
        // TODO: undefined behavior

        return *this;
    }

    auto *node = _path.top().first;
    auto index = _path.top().second;

    if (node->subtrees[0] != nullptr)
    {
        index = ++_path.top().second;
        while (node->subtrees[index] != nullptr)
        {
            node = node->subtrees[index];
            index = 0;
            _path.push(std::make_pair(node, 0));
        }

        return *this;
    }

    if (index != node->virtual_size - 1)
    {
        ++_path.top().second;

        return *this;
    }

    do
    {
        _path.pop();

        if (!_path.empty())
        {
            node = _path.top().first;
            index = _path.top().second;
        }
    }
    while (!_path.empty() && index == node->virtual_size - (node->subtrees[0] == nullptr
                                                            ? 1
                                                            : 0));

    return *this;
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_iterator b_tree<tkey, tvalue>::infix_iterator::operator++(
    int not_used)
{
    auto it = *this;
    ++*this;
    return it;
}

template<
    typename tkey,
    typename tvalue>
std::tuple<size_t, size_t, tkey const &, tvalue &> b_tree<tkey, tvalue>::infix_iterator::operator*() const
{
    auto &kvp = _path.top().first->keys_and_values[_path.top().second];
    return std::tuple<size_t, size_t, tkey const &, tvalue &>(_path.size() - 1, _path.top().second, std::cref(kvp.key), std::ref(kvp.value));
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue>::infix_const_iterator::infix_const_iterator(
    typename search_tree<tkey, tvalue>::common_node *subtree_root):
    _iterator(subtree_root)
{

}

template<
    typename tkey,
    typename tvalue>
bool b_tree<tkey, tvalue>::infix_const_iterator::operator==(
    b_tree::infix_const_iterator const &other) const noexcept
{
    return _iterator == other._iterator;
}

template<
    typename tkey,
    typename tvalue>
bool b_tree<tkey, tvalue>::infix_const_iterator::operator!=(
    b_tree::infix_const_iterator const &other) const noexcept
{
    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_const_iterator &b_tree<tkey, tvalue>::infix_const_iterator::operator++()
{
    ++_iterator;
    return *this;
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_const_iterator b_tree<tkey, tvalue>::infix_const_iterator::operator++(
    int not_used)
{
    auto it = *this;
    ++*this;
    return it;
}

template<
    typename tkey,
    typename tvalue>
std::tuple<size_t, size_t, tkey const &, tvalue const &> b_tree<tkey, tvalue>::infix_const_iterator::operator*() const
{
    auto data = *_iterator;
    return std::tuple<size_t, size_t, tkey const &, tvalue const &>(std::get<0>(data), std::get<1>(data), std::cref(std::get<2>(data)), std::cref(std::get<3>(data)));
}

template<
    typename tkey,
    typename tvalue>
void b_tree<tkey, tvalue>::insert_inner(
    typename associative_container<tkey, tvalue>::key_value_pair &&kvp)
{
    auto path = this->find_path(kvp.key);
    auto *node = *path.top().first;
    if (node == nullptr && path.size() == 1)
    {
        typename search_tree<tkey ,tvalue>::common_node *new_node;
        *path.top().first = new_node = this->create_node(_t);
        allocator::construct(new_node->keys_and_values, std::move(kvp));
        ++new_node->virtual_size;

        return;
    }

    if (path.top().second >= 0)
    {
        // TODO: update mechanics o_O
        throw std::logic_error("duplicate key");
    }

    size_t subtree_index = -path.top().second - 1;

    typename search_tree<tkey, tvalue>::common_node *right_subtree = nullptr;
    while (true)
    {
        if (node->virtual_size < get_max_keys_count())
        {
            this->node_insert(node, std::move(kvp), subtree_index, right_subtree);
            return;
        }

        auto res = this->node_split(node, std::move(kvp), subtree_index, right_subtree);
        right_subtree = res.first;
        kvp = std::move(res.second);

        if (path.size() == 1)
        {
            typename search_tree<tkey, tvalue>::common_node *new_root = this->create_node(_t);
            new_root->virtual_size = 1;
            allocator::construct(new_root->keys_and_values, std::move(kvp));
            new_root->subtrees[0] = node;
            new_root->subtrees[1] = right_subtree;
            *path.top().first = new_root;
            return;
        }

        path.pop();
        node = *path.top().first;
        subtree_index = -path.top().second - 1;
    }
}

template<
    typename tkey,
    typename tvalue>
void b_tree<tkey, tvalue>::insert(
    const tkey &key,
    const tvalue &value)
{
    insert_inner(std::move(typename associative_container<tkey, tvalue>::key_value_pair(key, value)));
}

template<
    typename tkey,
    typename tvalue>
void b_tree<tkey, tvalue>::insert(
    const tkey &key,
    tvalue &&value)
{
    insert_inner(std::move(typename associative_container<tkey, tvalue>::key_value_pair(key, std::move(value))));
}

template<
    typename tkey,
    typename tvalue>
tvalue &b_tree<tkey, tvalue>::obtain(
    const tkey &key)
{
    auto path = this->find_path(key);
    if (path.top().second < 0)
    {
        throw std::logic_error("key not found");
    }

    return (*path.top().first)->keys_and_values[path.top().second].value;
}

template<
    typename tkey,
    typename tvalue>
tvalue b_tree<tkey, tvalue>::dispose(
    const tkey &key)
{
    auto path = this->find_path(key);
    if (path.top().second < 0)
    {
        throw std::logic_error("key not found");
    }

    if ((*path.top().first)->subtrees[0] != nullptr)
    {
        auto non_terminal_node_with_key_found_info = path.top();
        path.pop();
        typename search_tree<tkey, tvalue>::common_node **iterator = non_terminal_node_with_key_found_info.first;

        // TODO: configure this for min of right subtree
        while (*iterator != nullptr)
        {
            auto index = *iterator == *non_terminal_node_with_key_found_info.first
                         ? non_terminal_node_with_key_found_info.second
                         : (*iterator)->virtual_size;

            path.push(std::make_pair(iterator, -index - 1));

            iterator = (*iterator)->subtrees + index;
        }

        search_tree<tkey, tvalue>::swap(std::move((*non_terminal_node_with_key_found_info.first)->keys_and_values[non_terminal_node_with_key_found_info.second]), std::move((*path.top().first)->keys_and_values[(*path.top().first)->virtual_size - 1]));
        path.top().second = -path.top().second - 2;
    }

    auto target_node = *path.top().first;
    auto kvp_to_dispose_index = path.top().second;
    path.pop();

    for (size_t i = kvp_to_dispose_index + 1; i < target_node->virtual_size; i++)
    {
        search_tree<tkey, tvalue>::swap(std::move(target_node->keys_and_values[i - 1]), std::move(target_node->keys_and_values[i]));
    }

    tvalue value = std::move(target_node->keys_and_values[--target_node->virtual_size].value);

    allocator::destruct(target_node->keys_and_values + target_node->virtual_size);

    while (true)
    {
        if (target_node->virtual_size >= get_min_keys_count())
        {
            return value;
        }

        if (path.size() == 0)
        {
            if (target_node->virtual_size == 0)
            {
                this->_root = target_node->subtrees[0];
                this->destroy_node(target_node);
            }

            return value;
        }

        typename search_tree<tkey, tvalue>::common_node *parent = *path.top().first;
        size_t position = -path.top().second - 1;
        path.pop();

        bool const left_brother_exists = position != 0;
        bool const can_take_from_left_brother =
            left_brother_exists &&
            parent->subtrees[position - 1]->virtual_size > get_min_keys_count();

        bool const right_brother_exists = position != parent->virtual_size;
        bool const can_take_from_right_brother =
            right_brother_exists &&
            parent->subtrees[position + 1]->virtual_size > get_min_keys_count();

        if (can_take_from_left_brother)
        {
            auto *left_brother = parent->subtrees[position - 1];
            search_tree<tkey, tvalue>::swap(std::move(parent->keys_and_values[position - 1]), std::move(left_brother->keys_and_values[left_brother->virtual_size - 1]));

            allocator::construct(target_node->keys_and_values + target_node->virtual_size, std::move(left_brother->keys_and_values[left_brother->virtual_size - 1]));
            search_tree<tkey, tvalue>::swap(std::move(left_brother->subtrees[left_brother->virtual_size]), std::move(target_node->subtrees[target_node->virtual_size]));
            target_node->subtrees[++target_node->virtual_size] = left_brother->subtrees[left_brother->virtual_size];

            for (auto i = target_node->virtual_size - 1; i > 0; --i)
            {
                search_tree<tkey, tvalue>::swap(std::move(target_node->keys_and_values[i]),
                                                std::move(target_node->keys_and_values[i - 1]));

                search_tree<tkey, tvalue>::swap(std::move(target_node->subtrees[i + 1]), std::move(target_node->subtrees[i]));
            }

            allocator::destruct(left_brother->keys_and_values + --left_brother->virtual_size);

            return value;
        }

        if (can_take_from_right_brother)
        {
            auto *right_brother = parent->subtrees[position + 1];
            search_tree<tkey, tvalue>::swap(std::move(parent->keys_and_values[position]), std::move(right_brother->keys_and_values[0]));

            allocator::construct(target_node->keys_and_values + target_node->virtual_size, std::move(right_brother->keys_and_values[0]));
            target_node->subtrees[++target_node->virtual_size] = right_brother->subtrees[0];

            for (size_t i = 0; i < right_brother->virtual_size - 1; ++i)
            {
                search_tree<tkey, tvalue>::swap(std::move(right_brother->keys_and_values[i]), std::move(right_brother->keys_and_values[i + 1]));

                search_tree<tkey, tvalue>::swap(std::move(right_brother->subtrees[i]), std::move(right_brother->subtrees[i + 1]));
            }

            right_brother->subtrees[right_brother->virtual_size - 1] = right_brother->subtrees[right_brother->virtual_size];

            allocator::destruct(right_brother->keys_and_values + --right_brother->virtual_size);

            return value;
        }

        this->merge_nodes(parent, position - (left_brother_exists
                                              ? 1
                                              : 0));

        target_node = parent;
    }
}

template<
    typename tkey,
    typename tvalue>
std::vector<typename associative_container<tkey, tvalue>::key_value_pair> b_tree<tkey, tvalue>::obtain_between(
    tkey const &lower_bound,
    tkey const &upper_bound,
    bool lower_bound_inclusive,
    bool upper_bound_inclusive)
{
    throw not_implemented("template<typename tkey, typename tvalue> std::vector<typename associative_container<tkey, tvalue>::key_value_pair> b_tree<tkey, tvalue>::obtain_between(tkey const &, tkey const &, bool, bool)", "your code should be here...");
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_iterator b_tree<tkey, tvalue>::begin_infix() const noexcept
{
    return b_tree<tkey, tvalue>::infix_iterator(this->_root);
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_iterator b_tree<tkey, tvalue>::end_infix() const noexcept
{
    return b_tree<tkey, tvalue>::infix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_const_iterator b_tree<tkey, tvalue>::cbegin_infix() const noexcept
{
    return b_tree<tkey, tvalue>::infix_const_iterator(this->_root);
}

template<
    typename tkey,
    typename tvalue>
typename b_tree<tkey, tvalue>::infix_const_iterator b_tree<tkey, tvalue>::cend_infix() const noexcept
{
    return b_tree<tkey, tvalue>::infix_const_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue>::b_tree(
    size_t t,
    std::function<int(tkey const &, tkey const &)> keys_comparer,
    allocator *allocator,
    logger *logger):
    search_tree<tkey, tvalue>(keys_comparer, logger, allocator)
{
    if ((_t = t) < 2)
    {
        throw std::logic_error("Invalid value of t parameter");
    }
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue>::b_tree(
    b_tree<tkey, tvalue> const &other):
    search_tree<tkey, tvalue>(other._keys_comparer, other.get_logger(), other.get_allocator()),
    _t(other._t)
{
    this->_root = copy(other._root);
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue> &b_tree<tkey, tvalue>::operator=(
    b_tree<tkey, tvalue> const &other)
{
    if (this != &other)
    {
        clear();
        this->_logger = other.get_logger();
        this->_allocator = other.get_allocator();
        this->_root = copy(other._root);
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue>::b_tree(
    b_tree<tkey, tvalue> &&other) noexcept:
    search_tree<tkey, tvalue>(other._keys_comparer, other.get_logger(), other.get_allocator()),
    _t(other._t)
{
    other._logger = nullptr;

    other._allocator = nullptr;

    this->_root = other._root;
    other._root = nullptr;
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue> &b_tree<tkey, tvalue>::operator=(
    b_tree<tkey, tvalue> &&other) noexcept
{
    if (this != &other)
    {
        clear();

        this->_keys_comparer = other._keys_comparer;

        this->_logger = other._logger;
        other._logger = nullptr;

        this->_allocator = other._allocator;
        other._allocator = nullptr;

        this->_root = other._root;
        other._root = nullptr;
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue>
b_tree<tkey, tvalue>::~b_tree()
{
    clear();
}

template<
    typename tkey,
    typename tvalue>
inline size_t b_tree<tkey, tvalue>::get_min_keys_count() const noexcept
{
    return _t - 1;
}

template<
    typename tkey,
    typename tvalue>
inline size_t b_tree<tkey, tvalue>::get_max_keys_count() const noexcept
{
    return 2 * _t - 1;
}

template<
    typename tkey,
    typename tvalue>
typename search_tree<tkey, tvalue>::common_node *b_tree<tkey, tvalue>::copy(
    typename search_tree<tkey, tvalue>::common_node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    typename search_tree<tkey, tvalue>::common_node *copied = this->create_node(_t);
    copied->virtual_size = node->virtual_size;

    for (size_t i = 0; i < node->virtual_size; ++i)
    {
        allocator::construct(copied->keys_and_values + i, node->keys_and_values[i]);
    }

    for (size_t i = 0; i <= node->virtual_size; ++i)
    {
        copied->subtrees[i] = copy(node->subtrees[i]);
    }

    return copied;
}

template<
    typename tkey,
    typename tvalue>
typename search_tree<tkey, tvalue>::common_node *b_tree<tkey, tvalue>::copy()
{
    return copy(this->_root);
}

template<
    typename tkey,
    typename tvalue>
void b_tree<tkey, tvalue>::clear(
    typename search_tree<tkey, tvalue>::common_node *node)
{
    if (node == nullptr)
    {
        return;
    }

    for (size_t i = 0; i <= node->virtual_size; ++i)
    {
        clear(node->subtrees[i]);
    }

    search_tree<tkey, tvalue>::destroy_node(node);
}

template<
    typename tkey,
    typename tvalue>
void b_tree<tkey, tvalue>::clear()
{
    clear(this->_root);
}

#endif //INTERPRETERS_B_TREE_H