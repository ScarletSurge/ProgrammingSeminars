#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

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
        tkey key;
        tvalue &value_ref;
        size_t depth;
    };

public:

    class prefix_iterator final
    {

    private:

        binary_search_tree<tkey, tvalue> *_context;
        iterator_retval *_retval;

    public:

        prefix_iterator(
            binary_search_tree<tkey, tvalue> *context):
                _context(context),
                _retval(nullptr)
        {

        }

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

    prefix_iterator begin_prefix() const;

    prefix_iterator end_prefix() const;

};

#pragma region BST ITERATOR

template<
    typename tkey,
    typename tvalue>
bool binary_search_tree<tkey, tvalue>::prefix_iterator::operator==(
    typename binary_search_tree<tkey, tvalue>::prefix_iterator const &other) const
{
    return false;
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
    // TODO: ?!
    
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
    return *_retval;
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::iterator_retval const *binary_search_tree<tkey, tvalue>::prefix_iterator::operator->() const
{
    return _retval;
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
    binary_search_tree<tkey, tvalue>::node *subtree_root = _root;

    while (subtree_root != nullptr)
    {
        auto comparison_result = _keys_comparer(key, subtree_root->key);
        if (comparison_result == 0)
        {
            tvalue result = std::move(subtree_root->value);

            if (subtree_root->left_subtree == nullptr && subtree_root->right_subtree == nullptr) // no subtrees
            {
                delete subtree_root;
                subtree_root = nullptr;
            }
            else if (subtree_root->left_subtree == nullptr || subtree_root->right_subtree == nullptr) // one subtree
            {
                node *existing_subtree = subtree_root->left_subtree == nullptr
                    ? subtree_root->right_subtree
                    : subtree_root->left_subtree;
                delete subtree_root;
                subtree_root = existing_subtree;
            }
            else // two subtrees
            {
                node *&right_subtree_min = subtree_root->right_subtree;
                while (right_subtree_min->left_subtree != nullptr)
                {
                    right_subtree_min = right_subtree_min->left_subtree;
                }

                {
                    tkey temp = std::move(subtree_root->key);
                    subtree_root->key = std::move(right_subtree_min->key);
                    right_subtree_min->key = std::move(temp);
                }
                {
                    tvalue temp = std::move(subtree_root->value);
                    subtree_root->value = std::move(right_subtree_min->value);
                    right_subtree_min->value = std::move(temp);
                }

                node *right_subtree_min_right_subtree = right_subtree_min->right_subtree;
                delete right_subtree_min;
                right_subtree_min = right_subtree_min_right_subtree;
            }

            return result;
        }

        subtree_root = (comparison_result < 0
            ? subtree_root->left_subtree
            : subtree_root->right_subtree);
    }

    throw std::out_of_range("Key to erase doesn't exist inside tree");
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::begin_prefix() const
{
    // TODO:
    return binary_search_tree<tkey, tvalue>::prefix_iterator(this);
}

template<
    typename tkey,
    typename tvalue>
typename binary_search_tree<tkey, tvalue>::prefix_iterator binary_search_tree<tkey, tvalue>::end_prefix() const
{
    // TODO:
    return binary_search_tree<tkey, tvalue>::prefix_iterator(this);
}

#endif