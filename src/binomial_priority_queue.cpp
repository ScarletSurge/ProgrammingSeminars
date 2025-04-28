#include "../include/binomial_priority_queue.h"

#include <cmath>

priority_queue *binomial_priority_queue::merge(
    priority_queue *with)
{
    // TODO: check that with is ptr to binomial_priority_queue
    // dynamic_cast

    auto this_nodes_count = this->nodes_count();
    // TODO: with
    auto with_nodes_count = this->nodes_count();

    auto merged_nodes_count = this_nodes_count + with_nodes_count;

    auto max_binomial_trees_count = floor(log2(merged_nodes_count)) + 1;

    node **for_merge = new node*[max_binomial_trees_count];
    for (auto i = 0; i < max_binomial_trees_count; ++i)
    {
        for_merge[i] = nullptr;
    }


}