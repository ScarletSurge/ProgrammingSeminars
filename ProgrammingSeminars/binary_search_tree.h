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
        tvalue tvalue;
        node *left_subtree;
        node *right_subtree;
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

        iterator_retval _retval;

    public:

        bool operator==(
            prefix_iterator const &other) const;

        bool operator!=(
            prefix_iterator const &other) const;

        prefix_iterator &operator++();

        prefix_iterator operator++(
            int);

        iterator_retval operator*() const;

        iterator_retval *operator->() const;

    };

private:

    void destruct(
        node *&subtree_root);

    void destruct();

    void copy_node_recursive(
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

public:

    void upsert(
        tkey const &key,
        tvalue const &value);

    void upsert(
        tkey const &key,
        tvalue &&value);

    tvalue const &find(
        tkey const &key);

    tvalue erase(
        tkey const &key);

public:

    prefix_iterator begin_prefix() const;

    prefix_iterator end_prefix() const;

};

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
    node *&subtree_root)
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
void binary_search_tree<tkey, tvalue>::copy_node_recursive(
    node const *to_copy)
{
    if (to_copy == nullptr)
    {
        return nullptr;
    }

    node *copied = new node(*to_copy);
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

#endif