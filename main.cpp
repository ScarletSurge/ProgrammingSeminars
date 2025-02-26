#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

template<
    typename tkey,
    typename tvalue>
class associative_container
{

public:

    virtual ~associative_container() noexcept = default;

public:

    virtual void upsert(
        tkey const &key,
        tvalue &&value) = 0;

    virtual tvalue &obtain(
        tkey const &key) = 0;

    virtual tvalue dispose(
        tkey const &key) = 0;

};

template<
    typename tvalue>
class trie final:
    public associative_container<std::string, tvalue>
{

private:

    // std::optional<T>
    // std::variant<T>

    struct node
    {

        std::vector<node *> subtrees;
        tvalue *value;

        explicit node(
            std::map<char, size_t> const &alphabet):
                subtrees(alphabet.size()),
                value(nullptr)
        {
            for (auto &s: subtrees)
            {
                s = nullptr;
            }
        }

    };

private:

    trie::node *_root;
    std::map<char, size_t> _alphabet_mapping;

public:

    explicit trie(
        std::string const &alphabet);

public:

    trie(
        trie const &other);

    trie& operator=(
        trie const &other);

    trie(
        trie &&other) noexcept;

    trie &operator=(
        trie &&other) noexcept;

    ~trie() noexcept override;

private:

    std::stack<trie<tvalue>::node **> find_path(
        std::string const &key);

public:

    virtual void upsert(
        std::string const &key,
        tvalue &&value);

    virtual tvalue &obtain(
        std::string const &key);

    virtual tvalue dispose(
        std::string const &key);

};

template<
    typename tvalue>
trie<tvalue>::trie(
    std::string const &alphabet)
{
    if (alphabet.empty())
    {
        throw std::out_of_range("empty alphabet passed");
    }

    std::set<char> alphabet_items;
    for (auto a: alphabet)
    {
        alphabet_items.insert(a);
    }

    if (alphabet_items.size() != alphabet.length())
    {
        throw std::out_of_range("similar elements found in alphabet");
    }

    size_t i = 0;
    for (auto a: alphabet_items)
    {
        _alphabet_mapping[a] = i++;
    }

    _root = new node(_alphabet_mapping);
}

template<
    typename tvalue>
trie<tvalue>::trie(
    trie<tvalue> const &other)
{

}

template<
    typename tvalue>
trie<tvalue>& trie<tvalue>::operator=(
    trie<tvalue> const &other)
{

}

template<
    typename tvalue>
trie<tvalue>::trie(
    trie<tvalue> &&other) noexcept
{

}

template<
    typename tvalue>
trie<tvalue>& trie<tvalue>::operator=(
    trie<tvalue> &&other) noexcept
{

}

template<
    typename tvalue>
trie<tvalue>::~trie() noexcept
{

}

template<
    typename tvalue>
std::stack<typename trie<tvalue>::node **> trie<tvalue>::find_path(
    std::string const &key)
{
    std::stack<typename trie<tvalue>::node **> path;
    auto *current = _root;

    path.push(&_root);
    for (auto k: key)
    {
        auto it = _alphabet_mapping.find(k);
        if (it == _alphabet_mapping.end())
        {
            throw std::out_of_range("character is not contained in alphabet");
        }

        // TODO: this is BAD
        // current = current->subtrees[it->second];
        // path.push(&current);

        path.push(&current->subtrees[it->second]);
        if ((current = current->subtrees[it->second]) == nullptr)
        {
            return path;
        }
    }

    return path;
}

template<
    typename tvalue>
void trie<tvalue>::upsert(
    std::string const &key,
    tvalue &&value)
{
    auto *current_node = _root;

    for (auto k: key)
    {
        if (_alphabet_mapping.find(k) == _alphabet_mapping.end())
        {
            throw std::out_of_range("character is not contained in alphabet");
        }

        if (current_node->subtrees[_alphabet_mapping[k]] == nullptr)
        {
            current_node->subtrees[_alphabet_mapping[k]] = new node(_alphabet_mapping);
        }

        current_node = current_node->subtrees[_alphabet_mapping[k]];
    }

    // value not exists
    if (current_node->value == nullptr)
    {
        current_node->value = new tvalue(std::forward(value));
    }
    else
    {
        *(current_node->value) = std::forward(value);
    }
}

template<
    typename tvalue>
tvalue &trie<tvalue>::obtain(
    std::string const &key)
{
    /*auto *current_node = _root;

    for (auto k: key)
    {
        if (_alphabet_mapping.find(k) == _alphabet_mapping.end())
        {
            throw std::out_of_range("character is not contained in alphabet");
        }

        if (current_node->subtrees[_alphabet_mapping[k]] == nullptr)
        {
            throw std::out_of_range("key is not contained in trie");
        }

        current_node = current_node->subtrees[_alphabet_mapping[k]];
    }

    if (current_node->value == nullptr)
    {
        throw std::out_of_range("key is not contained in trie");
    }

    return current_node->value;*/

    auto path = find_path(key);
    if (*path.top() == nullptr || (*path.top())->value == nullptr)
    {
        throw std::out_of_range("key is not contained in trie");
    }
    return *((*path.top())->value);
}

template<
    typename tvalue>
tvalue trie<tvalue>::dispose(
    std::string const &key)
{
    auto path = find_path(key);
    if (*path.top() == nullptr || (*path.top())->value == nullptr)
    {
        throw std::out_of_range("key is not contained in trie");
    }

    delete (*path.top())->value;
}

int main()
{


    return 0;
}
