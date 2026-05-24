#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <stack>
#include <tuple>

template<
    typename tkey,
    typename tvalue>
class binary_search_tree
{

private:

    struct node
    {
        tkey key;
        tvalue value;
        node *left_subtree;
        node *right_subtree;

        node(
            tkey const &key,
            tvalue const &value):
                key(key),
                value(value),
                left_subtree(nullptr),
                right_subtree(nullptr)
        {

        }

        node(
            tkey const &key,
            tvalue &&value):
                key(key),
                value(std::move(value)),
                left_subtree(nullptr),
                right_subtree(nullptr)
        {

        }

    };

private:

    node *_root;
    int (*_keys_comparer)(tkey const &, tkey const &);

public:

    struct iterator_retval final
    {

        friend class binary_search_tree<tkey, tvalue>;

        tkey key;
        tvalue &value_ref;
        size_t depth;

    private:

        iterator_retval(
            tkey key,
            tvalue &value_ref,
            size_t depth);

    };

public:

    class prefix_iterator final
    {

    private:

        binary_search_tree<tkey, tvalue> *_context;
        iterator_retval *_retval;
        std::stack<std::tuple<node *, bool, bool>> _path;

    public:

        prefix_iterator(
            binary_search_tree<tkey, tvalue> *context,
            bool is_begin_iterator);

    public:

        ~prefix_iterator() noexcept;

        prefix_iterator(
            prefix_iterator const &other);

        prefix_iterator &operator=(
            prefix_iterator const &other);

        prefix_iterator(
            prefix_iterator &&other) noexcept;

        prefix_iterator &operator=(
            prefix_iterator &&other) noexcept;

    public:

        bool operator==(
            prefix_iterator const &other) const;

        bool operator!=(
            prefix_iterator const &other) const;

        prefix_iterator &operator++();

        prefix_iterator operator++(
            int);

        iterator_retval operator*() const;

        iterator_retval const *operator->() const;

    private:

        void copy_current_to_retval();

    };

private:

    void destruct(
        node *&subtree_root);

    void destruct();

    node *copy_node_recursive(
        node const *to_copy);

    void copy_from(
        binary_search_tree<tkey, tvalue> const &other);

    void move(
        binary_search_tree<tkey, tvalue> &&other) noexcept;

public:

    binary_search_tree(
        int (*keys_comparer)(tkey const &, tkey const &));

    virtual ~binary_search_tree() noexcept;

    binary_search_tree(
        binary_search_tree<tkey, tvalue> const &other);

    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> const &other);

    binary_search_tree(
        binary_search_tree<tkey, tvalue> &&other) noexcept;

    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> &&other) noexcept;

private:

    bool upsert_inner(
        tkey const &key,
        tvalue &&value);

public:

    bool upsert(
        tkey const &key,
        tvalue const &value);

    bool upsert(
        tkey const &key,
        tvalue &&value);

    tvalue const &find(
        tkey const &key) const;

    tvalue erase(
        tkey const &key);

public:

    prefix_iterator begin_prefix();

    prefix_iterator end_prefix();

};

#pragma region BST ITERATOR

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::iterator_retval::iterator_retval(
    tkey key,
    tvalue &value_ref,
    size_t depth):
        key(std::move(key)),
        value_ref(value_ref),
        depth(depth)
{

}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(
    binary_search_tree<tkey, tvalue> *context,
    bool is_begin_iterator):
        _context(context),
        _retval(nullptr)
{
    if (!is_begin_iterator)
    {
        return;
    }

    if (context->_root != nullptr)
    {
        _path.push(std::make_tuple(context->_root, false, false));
        _retval = new iterator_retval(context->_root->key, context->_root->value, 0);
    }
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other)
{

}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::prefix_iterator::~prefix_iterator() noexcept
{
    delete _retval;
    _retval = nullptr;
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator &binary_search_tree<tkey, tvalue>::prefix_iterator::operator=(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other)
{
    // TODO

    return *this;
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::prefix_iterator::prefix_iterator(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator &&other) noexcept
{
    // TODO
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator &binary_search_tree<tkey, tvalue>::prefix_iterator::operator=(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator &&other) noexcept
{
    // TODO

    return *this;
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other) const
{
    if (_context != other._context)
    {
        return false;
    }

    if (_path.empty() && other._path.empty())
    {
        return true;
    }

    if (_path.empty() ^ other._path.empty()) // !=
    {
        return false;
    }

    return _path.top() == other._path.top();
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator!=(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other) const
{
    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator &binary_search_tree<tkey, tvalue>::prefix_iterator::operator++()
{
    while (!_path.empty())
    {
        std::tuple<binary_search_tree<tkey, tvalue>::node *, bool, bool> &current = _path.top();
        if (std::get<1>(current) == false && std::get<0>(current)->left_subtree != nullptr)
        {
            std::get<1>(current) = true;
            _path.push(std::make_tuple(std::get<0>(current)->left_subtree, false, false));
            copy_current_to_retval();

            return *this;
        }

        if (std::get<2>(current) == false && std::get<0>(current)->right_subtree != nullptr)
        {
            std::get<2>(current) = true;
            _path.push(std::make_tuple(std::get<0>(current)->right_subtree, false, false));
            copy_current_to_retval();

            return *this;
        }

        _path.pop();
        if (!_path.empty())
        {
            if (std::get<0>(current) == std::get<0>(_path.top())->left_subtree)
            {
                std::get<1>(_path.top()) = true;
            }

            if (std::get<0>(current) == std::get<0>(_path.top())->right_subtree)
            {
                std::get<2>(_path.top()) = true;
            }
        }
    }

    delete _retval;
    _retval = nullptr;
    
    return *this;
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::prefix_iterator::operator++(
    int not_used)
{
    (void)not_used;

    auto result = *this;
    ++*this;
    return result;
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::iterator_retval binary_search_tree<tkey, tvalue>::prefix_iterator::operator*() const
{
    if (_retval == nullptr)
    {
        throw std::runtime_error("can't get data from iterator, which is outside of container");
    }

    return *_retval;
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::iterator_retval const *binary_search_tree<tkey, tvalue>::prefix_iterator::operator->() const
{
    if (_retval == nullptr)
    {
        throw std::runtime_error("can't get data from iterator, which is outside of container");
    }

    return _retval;
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::prefix_iterator::copy_current_to_retval()
{
    if (_path.empty())
    {
        return;
    }

    binary_search_tree<tkey, tvalue>::node *top = std::get<0>(_path.top());
    _retval->key = top->key;
    _retval->value_ref = top->value;
    _retval->depth = _path.size() - 1;
}

#pragma endregion

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree(
    int (*keys_comparer)(tkey const &, tkey const &)):
        _keys_comparer(keys_comparer),
        _root(nullptr)
{

}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::destruct(
    typename binary_search_tree<tkey, tvalue>::node *&subtree_root)
{
    if (subtree_root == nullptr)
    {
        return;
    }

    destruct(subtree_root->left_subtree);
    destruct(subtree_root->right_subtree);
    delete subtree_root;
    subtree_root = nullptr;
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::destruct()
{
    destruct(_root);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::node *binary_search_tree<tkey, tvalue>::copy_node_recursive(
    typename binary_search_tree<tkey, tvalue>::node const *to_copy)
{
    if (to_copy == nullptr)
    {
        return nullptr;
    }

    binary_search_tree<tkey, tvalue>::node *copied = new binary_search_tree<tkey, tvalue>::node(*to_copy);
    copied->left_subtree = copy_node_recursive(to_copy->left_subtree);
    copied->right_subtree = copy_node_recursive(to_copy->right_subtree);

    return copied;
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::copy_from(
    binary_search_tree<tkey, tvalue> const &other)
{
    if (this != &other)
    {
        _keys_comparer = other._keys_comparer;
        _root = copy_node_recursive(other._root);
    }
}

template<
    typename tkey,
    typename tvalue>
void binary_search_tree<tkey, tvalue>::move(
    binary_search_tree<tkey, tvalue> &&other) noexcept
{
    _keys_comparer = other._keys_comparer;

    _root = other._root;
    other._root = nullptr;
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::~binary_search_tree() noexcept
{
    destruct();
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree(
    binary_search_tree<tkey, tvalue> const &other)
{
    copy_from(other);
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue> &binary_search_tree<tkey, tvalue>::operator=(
    binary_search_tree<tkey, tvalue> const &other)
{
    if (this != &other)
    {
        destruct();
        copy_from(other);
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue>::binary_search_tree(
    binary_search_tree<tkey, tvalue> &&other) noexcept
{
    move(std::move(other));
}

template<
    typename tkey,
    typename tvalue>
binary_search_tree<tkey, tvalue> &binary_search_tree<tkey, tvalue>::operator=(
    binary_search_tree<tkey, tvalue> &&other) noexcept
{
    if (this != &other)
    {
        destruct();
        move(std::move(other));
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::upsert_inner(
    tkey const &key,
    tvalue &&value)
{
    binary_search_tree<tkey, tvalue>::node **subtree_root = &_root;

    while (*subtree_root != nullptr)
    {
        auto comparison_result = _keys_comparer(key, (*subtree_root)->key);
        if (comparison_result == 0)
        {
            (*subtree_root)->value = std::forward<tvalue &&>(value);

            return false;
        }

        subtree_root = (comparison_result < 0
            ? &(*subtree_root)->left_subtree
            : &(*subtree_root)->right_subtree);
    }

    *subtree_root = new binary_search_tree<tkey, tvalue>::node(key, std::forward<tvalue &&>(value));

    return true;
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::upsert(
    tkey const &key,
    tvalue const &value)
{
    // TODO: ?!
    // return upsert_inner(key, std::forward<tvalue const &>(value));
    return upsert_inner(key, std::forward<tvalue>(tvalue(value)));
}

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::upsert(
    tkey const &key,
    tvalue &&value)
{
    return upsert_inner(key, std::forward<tvalue>(value));
}

template<
    typename tkey,
    typename tvalue>
tvalue const &binary_search_tree<tkey, tvalue>::find(
    tkey const &key) const
{
    binary_search_tree<tkey, tvalue>::node const *subtree_root = _root;

    while (subtree_root != nullptr)
    {
        auto comparison_result = _keys_comparer(key, subtree_root->key);
        if (comparison_result == 0)
        {
            return subtree_root->value;
        }

        subtree_root = (comparison_result < 0
            ? subtree_root->left_subtree
            : subtree_root->right_subtree);
    }

    throw std::out_of_range("Key to find doesn't exist inside tree");
}

template<
    typename tkey,
    typename tvalue>
tvalue binary_search_tree<tkey, tvalue>::erase(
    tkey const &key)
{
    binary_search_tree<tkey, tvalue>::node **subtree_root = &_root;

    while (*subtree_root != nullptr)
    {
        auto comparison_result = _keys_comparer(key, (*subtree_root)->key);
        if (comparison_result == 0)
        {
            tvalue result = std::move((*subtree_root)->value);

            if ((*subtree_root)->left_subtree == nullptr && (*subtree_root)->right_subtree == nullptr) // no subtrees
            {
                delete *subtree_root;
                *subtree_root = nullptr;
            }
            else if ((*subtree_root)->left_subtree == nullptr || (*subtree_root)->right_subtree == nullptr) // one subtree
            {
                node *existing_subtree = (*subtree_root)->left_subtree == nullptr
                    ? (*subtree_root)->right_subtree
                    : (*subtree_root)->left_subtree;
                delete *subtree_root;
                *subtree_root = existing_subtree;
            }
            else // two subtrees
            {
                node *&right_subtree_min = (*subtree_root)->right_subtree;
                while (right_subtree_min->left_subtree != nullptr)
                {
                    right_subtree_min = right_subtree_min->left_subtree;
                }

                {
                    tkey temp = std::move((*subtree_root)->key);
                    (*subtree_root)->key = std::move(right_subtree_min->key);
                    right_subtree_min->key = std::move(temp);
                }
                {
                    tvalue temp = std::move((*subtree_root)->value);
                    (*subtree_root)->value = std::move(right_subtree_min->value);
                    right_subtree_min->value = std::move(temp);
                }

                node *right_subtree_min_right_subtree = right_subtree_min->right_subtree;
                delete right_subtree_min;
                right_subtree_min = right_subtree_min_right_subtree;
            }

            return result;
        }

        subtree_root = (comparison_result < 0
            ? &((*subtree_root)->left_subtree)
            : &((*subtree_root)->right_subtree));
    }

    throw std::out_of_range("Key to erase doesn't exist inside tree");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::begin_prefix()
{
    // TODO:
    return binary_search_tree<tkey, tvalue>::prefix_iterator(this, true);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::end_prefix()
{
    // TODO:
    return binary_search_tree<tkey, tvalue>::prefix_iterator(this, false);
}

#endif