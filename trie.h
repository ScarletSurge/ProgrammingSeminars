#ifndef INTERPRETERS_TRIE_H
#define INTERPRETERS_TRIE_H

#include <set>
#include <string>
#include <vector>

class trie final
{

private:

    struct node
    {

    public:

        std::vector<std::pair<node *, bool>> subtrees;
        size_t active_subtrees;

    public:

        explicit node(
            size_t alphabet_size);

    };

private:

    node *create_empty_node();

    size_t throw_if_outside_alphabet(
        char c) const;

    void obtain_all_inner(
        node *subtree_root,
        std::string &path,
        std::vector<std::string> &obtained) const;

private:

    node *_root;
    std::vector<char> _alphabet;
    bool _empty_string_present;

public:

    explicit trie(
        std::set<char> const &alphabet);

public:

    void insert(
        std::string const &value);

    bool obtain(
        std::string const &value) const;

    std::vector<std::string> obtain_all() const;

    void dispose(
        std::string const &value);

private:

    void clear();

    static void clear_recursive(
        node *to_clear,
        size_t alphabet_size);

    node *copy() const;

    static node *copy_recursive(
        node *to_copy,
        size_t alphabet_size);

public:

    trie(
        trie const &other);

    trie &operator=(
        trie const &other);

    trie(
        trie &&other) noexcept;

    trie &operator=(
        trie &&other) noexcept;

    ~trie();

};

#endif //INTERPRETERS_TRIE_H