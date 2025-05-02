#ifndef PUKSRENJK_BINOMIAL_HEAP_H
#define PUKSRENJK_BINOMIAL_HEAP_H

#include <cstddef>
#include "priority_queue.h"

class binomial_priority_queue final:
    public priority_queue
{

public:

    struct node final
    {
        int priority;
        char *value;
        node *next;
        node *child;

        // TODO: для тех кто слаб, заменить next и child на:
        //node **children;
        //size_t children_count;
    };

private:

    node *_root;

public:

    binomial_priority_queue();

public:

    void insert(
        int priority,
        char const *value) override;

    char const *remove_max() override;

    char const *obtain_max() override;

public:

    priority_queue *merge(
        priority_queue *with) override;

    priority_queue *meld(
        priority_queue const *with) const override;

private:

    size_t nodes_count() const;

    static size_t get_rank(
        binomial_priority_queue::node const *binomial_tree_root);

    void traverse_root_list(
        node **for_merge);

    static node *merge_binomial_trees(
        node *first_to_merge,
        node *second_to_merge);

};

#endif //PUKSRENJK_BINOMIAL_HEAP_H