#ifndef PUKSRENJK_BINOMIAL_HEAP_H
#define PUKSRENJK_BINOMIAL_HEAP_H

#include <cstddef>
#include "priority_queue.h"

class binomial_priority_queue final:
    public priority_queue
{

private:

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

};

#endif //PUKSRENJK_BINOMIAL_HEAP_H