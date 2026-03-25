#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include "mergeable_priority_queue.h"

class binomial_priority_queue final:
	public mergeable_priority_queue
{

private:

	struct node
	{
		char const *value;
		int priority;
		node *brother;
		node *children;
	};

private:

	node *_root;
	int (*_priorities_comparer)(int, int);

public:

	binomial_priority_queue(
		int (*priorities_comparer)(int, int)):
			_priorities_comparer(priorities_comparer),
			_root(nullptr)
	{

	}

	~binomial_priority_queue() noexcept override
	{
		// TODO: ?!
	}

	binomial_priority_queue(
		binomial_priority_queue const &copy_from)
	{

	}

	binomial_priority_queue &operator=(
		binomial_priority_queue const &)
	{

	}

	void merge(
		mergeable_priority_queue* to_merge_into) override
	{

	}

	mergeable_priority_queue* meld(
		mergeable_priority_queue const* to_meld_with) const override
	{

	}

public:

	void insert(
		int priority,
		char const *value) override
	{

	}

	char *remove_max() override
	{
		return nullptr;
	}

	char const* get_max() override
	{
		return nullptr;
	}

};

#endif