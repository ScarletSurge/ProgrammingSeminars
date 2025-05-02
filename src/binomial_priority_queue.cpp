#include "../include/binomial_priority_queue.h"

#include <stdexcept>
#include <cstring>

binomial_priority_queue::binomial_priority_queue():
    _root(nullptr)
{

}

void binomial_priority_queue::insert(
    int priority,
    char const *value)
{
    node *root = new node;
    root->priority = priority;
    root->value = new char[strlen(value) + 1];
    strcpy(root->value, value);
    root->child = nullptr;
    root->next = root;

    binomial_priority_queue for_merge;
    for_merge._root = root;

    this->merge(reinterpret_cast<priority_queue *>(&for_merge));
}

char const *binomial_priority_queue::remove_max()
{
    if (_root == nullptr)
    {
        throw std::logic_error("attempt to remove element with max priority, while heap was empty");
    }

    if (_root->next == _root)
    {
        binomial_priority_queue::node *child = _root->child;
        char const *value = _root->value;
        delete _root;
        _root = child;
        return value;
    }

    binomial_priority_queue::node *current = _root;
    while (current->next != _root)
    {
        current = current->next;
    }

    current->next = current->next->next;
    binomial_priority_queue::node *old_root = _root;
    _root = current;

    binomial_priority_queue::node *child = old_root->child;
    char const *value = old_root->value;
    delete old_root;
    binomial_priority_queue for_merge;
    for_merge._root = child;

    this->merge(dynamic_cast<priority_queue *>(&for_merge));
    return value;
}

char const *binomial_priority_queue::obtain_max()
{
    if (_root == nullptr)
    {
        throw std::logic_error("attempt to obtain element with max priority, while heap was empty");
    }

    return _root->value;
}

priority_queue *binomial_priority_queue::merge(
    priority_queue *with)
{
    binomial_priority_queue *with_binomial;

    if ((with_binomial = dynamic_cast<binomial_priority_queue *>(with)) == nullptr)
    {
        throw std::invalid_argument("invalid heap type");
    }

    auto this_nodes_count = this->nodes_count();
    auto with_nodes_count = with_binomial->nodes_count();

    auto merged_nodes_count = this_nodes_count + with_nodes_count; // 136

    auto max_binomial_trees_count = 0;
    while (merged_nodes_count != 0)
    {
        ++max_binomial_trees_count;
        merged_nodes_count >>= 1;
    }

    node **for_merge = new node *[max_binomial_trees_count];
    for (auto i = 0; i < max_binomial_trees_count; ++i)
    {
        for_merge[i] = nullptr;
    }

    this->traverse_root_list(for_merge);
    with_binomial->traverse_root_list(for_merge);

    binomial_priority_queue::node *node_with_max_priority;

    binomial_priority_queue::node *current = nullptr;
    for (auto i = 0; i < max_binomial_trees_count; ++i)
    {
        if (for_merge[i] == nullptr)
        {
            continue;
        }

        if (_root == nullptr)
        {
            _root = for_merge[i];
            current = _root;
            node_with_max_priority = _root;
        }
        else
        {
            current->next = for_merge[i];
            current = current->next;

            if (current->priority > node_with_max_priority->priority)
            {
                node_with_max_priority = current;
            }
        }
    }

    delete [] for_merge;

    current->next = _root;
    _root = node_with_max_priority;

    return dynamic_cast<priority_queue *>(this);
}

priority_queue *binomial_priority_queue::meld(
    priority_queue const *with) const
{
    binomial_priority_queue const *with_binomial;

    if ((with_binomial = dynamic_cast<binomial_priority_queue const *>(with)) == nullptr)
    {
        throw std::invalid_argument("invalid heap type");
    }

    binomial_priority_queue with_binomial_copy(*with_binomial);
    binomial_priority_queue *this_copy = new binomial_priority_queue(*this);

    return this_copy->merge(dynamic_cast<priority_queue *>(&with_binomial_copy));
}

size_t binomial_priority_queue::nodes_count() const
{
    binomial_priority_queue::node *current = _root;
    if (current == nullptr)
    {
        return 0;
    }

    auto elements_count = 0;

    do
    {
        elements_count += (1 << get_rank(current));
        current = current->next;
    }
    while (current != _root);

    return elements_count;
}

size_t binomial_priority_queue::get_rank(
    binomial_priority_queue::node const *binomial_tree_root)
{
    if (binomial_tree_root == nullptr)
    {
        throw std::logic_error("invalid root value");
    }

    binomial_priority_queue::node *child = binomial_tree_root->child;

    if (child == nullptr)
    {
        return 0;
    }

    auto rank = 0;
    do
    {
        ++rank;
        child = child->next;
    }
    while (child != binomial_tree_root->child);

    return rank;
}

void binomial_priority_queue::traverse_root_list(
    binomial_priority_queue::node **for_merge)
{
    binomial_priority_queue::node *root_list_item = _root;
    if (root_list_item == nullptr)
    {
        return;
    }

    size_t root_list_items_count = 0;
    do
    {
        ++root_list_items_count;
        root_list_item = root_list_item->next;
    }
    while (root_list_item != _root);

    binomial_priority_queue::node **root_list_items = new binomial_priority_queue::node *[root_list_items_count];
    size_t i = 0;
    do
    {
        root_list_items[i] = root_list_item;
        root_list_item = root_list_item->next;
        root_list_items[i++]->next = nullptr;
    }
    while (root_list_item != _root);

    _root = nullptr;

    for (i = 0; i < root_list_items_count; ++i)
    {
        auto rank = get_rank(root_list_items[i]);

        while (for_merge[rank] != nullptr)
        {
            root_list_items[i] = merge_binomial_trees(for_merge[rank], root_list_items[i]);
            for_merge[rank++] = nullptr;
        }

        for_merge[rank] = root_list_items[i];
    }
}

binomial_priority_queue::node *binomial_priority_queue::merge_binomial_trees(
    binomial_priority_queue::node *first_to_merge,
    binomial_priority_queue::node *second_to_merge)
{
    if (first_to_merge == nullptr || second_to_merge == nullptr)
    {
        throw std::invalid_argument("nullptr detected!!1!1");
    }

    auto rank = get_rank(first_to_merge);

    auto first_priority = first_to_merge->priority;
    auto second_priority = second_to_merge->priority;

    node *new_root = first_priority >= second_priority
        ? first_to_merge
        : second_to_merge;

    node *new_root_subtree = new_root == first_to_merge
        ? second_to_merge
        : first_to_merge;

    if (rank == 0)
    {
        new_root->child = new_root_subtree;
        new_root_subtree->next = new_root_subtree;

        return new_root;
    }

    binomial_priority_queue::node *next = new_root->child->next;
    new_root->child->next = new_root_subtree;
    new_root_subtree->next = next;

    if (new_root_subtree->priority > new_root->child->priority)
    {
        new_root->child = new_root->child->next;
    }

    return new_root;
}