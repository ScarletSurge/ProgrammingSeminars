#include "trie.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

trie::node::node(
    size_t alphabet_size):
    subtrees(alphabet_size)
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
        //if (subtree_root->subtrees[i].first == nullptr)
        //{
        //    continue;
        //}

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
        _alphabet(alphabet.size()),
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
    
}

trie::trie(
    trie const &other)
{
    
}

trie &trie::operator=(
    trie const &other)
{
    
}

trie::trie(
    trie &&other) noexcept
{
    
}

trie &trie::operator=(
    trie &&other) noexcept
{
    
}

trie::~trie()
{

}