#include "trie.h"

#include <algorithm>
#include <stack>
#include <stdexcept>

trie::node::node(
    size_t alphabet_size):
    subtrees(alphabet_size),
    active_subtrees(0)
{
    for (auto i = 0; i < alphabet_size; ++i)
    {
        subtrees[i] = std::move(std::pair<node *, bool>(nullptr, false));
    }
}

trie::node *trie::create_empty_node()
{
    return new trie::node(_alphabet.size());
}

size_t trie::throw_if_outside_alphabet(
    char c) const
{
    auto it = std::find(_alphabet.cbegin(), _alphabet.cend(), c);

    if (it == _alphabet.end())
    {
        throw std::logic_error("character is outside alphabet");
    }

    return std::distance(_alphabet.cbegin(), it);
}

void trie::obtain_all_inner(
    trie::node *subtree_root,
    std::string &path,
    std::vector<std::string> &obtained) const
{
    if (subtree_root == nullptr)
    {
        return;
    }

    for (auto i = 0; i < _alphabet.size(); ++i)
    {
        path.push_back(_alphabet[i]);
        if (subtree_root->subtrees[i].second)
        {
            obtained.push_back(path);
        }
        obtain_all_inner(subtree_root->subtrees[i].first, path, obtained);
        path.pop_back();
    }
}

trie::trie(
    std::set<char> const &alphabet):
        _empty_string_present(false)
{
    if (alphabet.empty())
    {
        throw std::logic_error("omg lol o_O");
    }

    for (auto alphabet_item: alphabet)
    {
        _alphabet.push_back(alphabet_item);
    }

    _root = create_empty_node();
}

void trie::insert(
    std::string const &value)
{
    if (value.empty())
    {
        if (_empty_string_present)
        {
            throw std::logic_error("duplicate word ._.");
        }

        _empty_string_present = true;
        return;
    }

    node *current = _root;

    for (auto i = 0; i < value.size(); ++i)
    {
        auto index = throw_if_outside_alphabet(value[i]);

        if (i == value.size() - 1)
        {
            if (current->subtrees[index].second)
            {
                throw std::logic_error("duplicate word ._.");
            }

            current->subtrees[index].second = true;
            return;
        }

        if (current->subtrees[index].first == nullptr)
        {
            current->subtrees[index].first = create_empty_node();
            ++current->active_subtrees;
        }

        current = current->subtrees[index].first;
    }
}

bool trie::obtain(
    std::string const &value) const
{
    if (value.empty() && _empty_string_present)
    {
        return true;
    }

    node *current = _root;

    for (auto i = 0; i < value.size(); ++i)
    {
        auto index = throw_if_outside_alphabet(value[i]);
        if (current->subtrees[index].first == nullptr)
        {
            return false;
        }

        if (current->subtrees[index].second && i == value.size() - 1)
        {
            return true;
        }

        current = current->subtrees[index].first;
    }

    return false;
}

std::vector<std::string> trie::obtain_all() const
{
    std::vector<std::string> obtained;
    std::string path;

    if (_empty_string_present)
    {
        obtained.emplace_back("");
    }

    obtain_all_inner(_root, path, obtained);

    return obtained;
}

void trie::dispose(
    std::string const &value)
{
    if (value.empty())
    {
        if (!_empty_string_present)
        {
            throw std::logic_error("trying to dispose non existing key ._.");
        }

        _empty_string_present = false;
        return;
    }

    std::stack<std::pair<node **, size_t>> path;
    node **current = &_root;

    for (auto i = 0; i < value.size(); ++i)
    {
        if (*current == nullptr)
        {
            throw std::logic_error("trying to dispose non existing key ._.");
        }

        auto index = throw_if_outside_alphabet(value[i]);

        if (i == value.size() - 1)
        {
            if (!(*current)->subtrees[index].second)
            {
                throw std::logic_error("trying to dispose non existing key ._.");
            }

            (*current)->subtrees[index].second = false;
            while ((*current)->active_subtrees == 0)
            {
                delete *current;
                *current = nullptr;

                if (path.empty())
                {
                    break;
                }

                auto pair = path.top();
                path.pop();

                --(*(current = pair.first))->active_subtrees;
                index = pair.second;
            }

            return;
        }

        path.push(std::make_pair(current, index));
        current = &(*current)->subtrees[index].first;
    }
}

void trie::clear()
{
    clear_recursive(_root, _alphabet.size());
    _root = nullptr;
}

void trie::clear_recursive(
    trie::node *to_clear,
    size_t alphabet_size)
{
    if (to_clear == nullptr)
    {
        return;
    }

    for (auto i = 0; i < alphabet_size; ++i)
    {
        clear_recursive(to_clear->subtrees[i].first, alphabet_size);
    }

    delete to_clear;
}

trie::node *trie::copy() const
{
    return copy_recursive(_root, _alphabet.size());
}

trie::node *trie::copy_recursive(
    trie::node *to_copy,
    size_t alphabet_size)

{
    if (to_copy == nullptr)
    {
        return nullptr;
    }

    int i;
    node *copy = nullptr;
    try
    {
        copy = new trie::node(alphabet_size);
        copy->active_subtrees = to_copy->active_subtrees;

        for (i = 0; i < alphabet_size; ++i)
        {
            node *copied_subtree = copy_recursive(to_copy->subtrees[i].first, alphabet_size);

            copy->subtrees[i] = std::move(std::make_pair(copied_subtree, to_copy->subtrees[i].second));
        }
    }
    catch (std::bad_alloc const &ex)
    {
        for (auto j = 0; j < i; ++j)
        {
            clear_recursive(copy->subtrees[j].first, alphabet_size);
        }

        delete copy;

        throw;
    }

    return copy;
}

trie::trie(
    trie const &other):
        _empty_string_present(other._empty_string_present),
        _alphabet(other._alphabet)
{
    _root = other.copy();
}

trie &trie::operator=(
    trie const &other)
{
    if (this != &other)
    {
        clear();

        _empty_string_present = other._empty_string_present;
        _alphabet = other._alphabet;

        _root = other.copy();
    }

    return *this;
}

trie::trie(
    trie &&other) noexcept:
    _empty_string_present(other._empty_string_present),
    _alphabet(std::move(other._alphabet)),
    _root(other._root)
{
    other._root = nullptr;
}

trie &trie::operator=(
    trie &&other) noexcept
{
    if (this != &other)
    {
        clear();

        _empty_string_present = other._empty_string_present;

        _alphabet = std::move(other._alphabet);

        _root = other._root;
        other._root = nullptr;
    }

    return *this;
}

trie::~trie()
{
    clear();
}