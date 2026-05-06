#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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

public:

    binary_search_tree(
        int (*keys_comparer)(tkey const &, tkey const &));

    virtual ~binary_search_tree() noexcept;

    binary_search_tree(
        binary_search_tree<tkey, tvalue> const &other);

    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> const &other);

public:

    void upsert(
        tkey const &key,
        tvalue const &value);

    tvalue const &find(
        tkey const &key);

    tvalue erase(
        tkey const &key);

public:

    prefix_iterator begin_prefix() const;

    prefix_iterator end_prefix() const;

};

#endif