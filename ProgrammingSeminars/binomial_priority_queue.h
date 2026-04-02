#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#pragma warning(disable: 4996)

#include "mergeable_priority_queue.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

class binomial_priority_queue final:
	public mergeable_priority_queue
{

private:

	struct node
	{
		char *value;
		int priority;
		node *brother;
		node *children;
	};

public:

	class empty_priority_queue_exception:
		public std::exception
	{

	public:

		char const *what() const override
		{
			return "Can't get/remove maximum from priority queue";
		}

	};

private:

	node *_root;
	int (*_priorities_comparer)(int, int);
	size_t _values_count;

private:

	static void delete_node_state(
		node *state)
	{
		delete[] state->value;
		state->value = nullptr;
	}

	static void delete_binomial_trees_list(
		node **tree_root)
	{
		if (*tree_root == nullptr)
		{
			return;
		}

		node *runner = *tree_root;
		do
		{
			delete_binomial_trees_list(&runner->children);
			node *to_delete = runner;
			runner = runner->brother;
			delete_node_state(to_delete);
			delete to_delete;
		} while (runner != *tree_root);

		*tree_root = nullptr;
	}

	static node *copy_binomial_trees_list(
		node const *root)
	{
			if (root == nullptr)
			{
				return nullptr;
			}

		node const *runner = root;
		node *runner_copy = nullptr;
		node *first_node = nullptr;
		do
		{
			if (first_node == nullptr)
			{
				runner_copy = first_node = create_node(runner->priority, runner->value);
			}
			else
			{
				runner_copy->brother = create_node(runner->priority, runner->value);
				runner_copy = runner_copy->brother;
			}
			runner_copy->children = copy_binomial_trees_list(runner->children);

			runner = runner->brother;
		} while (runner != root);

		runner_copy->brother = first_node;
		return first_node;
	}

public:

	binomial_priority_queue(
		int (*priorities_comparer)(int, int)):
			_priorities_comparer(priorities_comparer),
			_root(nullptr),
			_values_count(0)
	{

	}

	~binomial_priority_queue() noexcept override
	{
		delete_binomial_trees_list(&_root);
		_values_count = 0;
		_priorities_comparer = nullptr;
	}


	binomial_priority_queue(
		binomial_priority_queue const &copy_from):
			_root(copy_binomial_trees_list(copy_from._root)),
			_values_count(copy_from._values_count),
			_priorities_comparer(copy_from._priorities_comparer)
	{

	}

	binomial_priority_queue &operator=(
		binomial_priority_queue const &other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete_binomial_trees_list(&_root);

		_root = copy_binomial_trees_list(other._root);
		_values_count = other._values_count;
		_priorities_comparer = other._priorities_comparer;

		return *this;
	}

public:

	void merge(
		mergeable_priority_queue *to_merge_from) override
	{
		binomial_priority_queue *bpq_to_merge_from;

		if ((bpq_to_merge_from = dynamic_cast<binomial_priority_queue *>(to_merge_from)) == nullptr)
		{
			throw std::invalid_argument("Parameter must be of type binomial_priority_queue *");
		}

		if (this == to_merge_from)
		{
			return;
		}

		if (bpq_to_merge_from->_root == nullptr)
		{
			return;
		}
		if (this->_root == nullptr && bpq_to_merge_from->_root != nullptr)
		{
			// move
			this->_root = bpq_to_merge_from->_root;
			this->_values_count = bpq_to_merge_from->_values_count;
			bpq_to_merge_from->_root = nullptr;
			bpq_to_merge_from->_values_count = 0;

			return;
		}

		size_t merged_values_count = this->_values_count + bpq_to_merge_from->_values_count;

		size_t max_trees_count = 0;
		while (merged_values_count != 0)
		{
			merged_values_count >>= 1;
			++max_trees_count;
		}

		node **merged_trees = new node *[max_trees_count];
		for (int i = 0; i < max_trees_count; i++)
		{
			merged_trees[i] = nullptr;
		}

		node *runner = this->_root;
		do
		{
			merged_trees[get_rank(runner)] = runner;
			runner = runner->brother;
		} while (runner != this->_root);

		node *two_merged_trees;
		runner = bpq_to_merge_from->_root;
		do
		{
			size_t rank = get_rank(runner);
			if (merged_trees[rank] == nullptr)
			{
				merged_trees[rank] = runner;
				runner = runner->brother;
				
				continue;
			}
			
			two_merged_trees = runner;
			runner = runner->brother;
			while (merged_trees[rank] != nullptr)
			{
				two_merged_trees = merge_binomial_trees(two_merged_trees, merged_trees[rank]);
				merged_trees[rank] = nullptr;
				++rank;
			}
			merged_trees[rank] = two_merged_trees;
		} while (runner != bpq_to_merge_from->_root);

		bpq_to_merge_from->_root = nullptr;

		node *first_existent_root = nullptr;
		node *last_existent_root = nullptr;
		node *root_with_max_priority = nullptr;
		for (int i = 0; i < max_trees_count; ++i)
		{
			if (merged_trees[i] == nullptr)
			{
				continue;
			}

			if (first_existent_root == nullptr)
			{
				first_existent_root = merged_trees[i];
				root_with_max_priority = merged_trees[i];
			}
			else if (_priorities_comparer(root_with_max_priority->priority, merged_trees[i]->priority) < 0)
			{
				root_with_max_priority = merged_trees[i];
			}

			if (last_existent_root != nullptr)
			{
				last_existent_root->brother = merged_trees[i];
			}

			last_existent_root = merged_trees[i];
		}

		last_existent_root->brother = first_existent_root;

		_root = root_with_max_priority;
		_values_count += bpq_to_merge_from->_values_count;
		bpq_to_merge_from->_values_count = 0;
	}

	mergeable_priority_queue *meld(
		mergeable_priority_queue const *to_meld_with) const override
	{
		binomial_priority_queue const * bpq_to_meld_from;

		if ((bpq_to_meld_from = dynamic_cast<binomial_priority_queue const *>(to_meld_with)) == nullptr)
		{
			throw std::invalid_argument("Parameter must be of type binomial_priority_queue const *");
		}

		binomial_priority_queue *to_meld_into = new binomial_priority_queue(*this);
		binomial_priority_queue to_meld_from(*bpq_to_meld_from);
		to_meld_into->merge(&to_meld_from);

		return to_meld_into;
	}

public:

	void insert(
		int priority,
		char const *value) override
	{
		binomial_priority_queue new_heap(_priorities_comparer);
		(new_heap._root = create_node(priority, value))->brother = new_heap._root;
		new_heap._values_count = 1;

		merge(&new_heap);
	}

	char *remove_max() override
	{
		if (_root == nullptr)
		{
			throw empty_priority_queue_exception();
		}

		node *tree_to_split = _root;
		if (tree_to_split->brother == tree_to_split)
		{
			_root = nullptr;
		}
		else
		{
			node *new_max_tree = tree_to_split->brother;
			node *runner = tree_to_split->brother;
			while (runner->brother != _root)
			{
				if (_priorities_comparer(runner->priority, new_max_tree->priority) > 0)
				{
					new_max_tree = runner;
				}
				runner = runner->brother;
			}
			runner->brother = runner->brother->brother;
			_root = new_max_tree;
		}

		_values_count -= (1 << get_rank(tree_to_split));

		binomial_priority_queue new_heap(_priorities_comparer);
		new_heap._root = tree_to_split->children;
		new_heap._values_count = (1 << get_rank(tree_to_split)) - 1;

		char *to_return = tree_to_split->value;

		delete tree_to_split;

		merge(&new_heap);

		return to_return;
	}

	char const *get_max() override
	{
		if (_root == nullptr)
		{
			throw empty_priority_queue_exception();
		}

		return _root->value;
	}

public:

	void debug_print() const
	{
		node* runner = _root;

		std::cout << _values_count << ": ";
		
		if (runner == nullptr)
		{
			std::cout << "<EMPTY>" << std::endl;

			return;
		}
		
		do
		{
			std::cout << 'B' << get_rank(runner) << '<' << runner->priority << '>' << " -> ";
			runner = runner->brother;
		} while (runner != _root);
		std::cout << std::endl;
	}

private:

	static node *create_node(
		int priority,
		char const *value)
	{
		node *result = new node;
		result->priority = priority;
		result->value = new char[strlen(value) + 1];
		strcpy(result->value, value);
		result->brother = result->children = nullptr;
		// code --compile-> code' --build-> .exe --obfuscate->
		return result;
	}

	static size_t get_rank(
		node const *root)
	{
		size_t rank = 0;
		node const *child = root->children;
		if (child != nullptr)
		{
			do
			{
				++rank;
				child = child->brother;
			} while (child != root->children);
		}
		return rank;
	}

	node *merge_binomial_trees(
		node *first_to_merge,
		node *second_to_merge)
	{
		if (first_to_merge == second_to_merge)
		{
			throw std::runtime_error(first_to_merge == nullptr
				? "At least one of binomial trees not exist"
				: "Can't merge tree with itself");
		}

		if (get_rank(first_to_merge) != get_rank(second_to_merge))
		{
			throw std::runtime_error("Can't merge trees with different ranks");
		}

		node *new_tree_root = _priorities_comparer(first_to_merge->priority, second_to_merge->priority) >= 0
			? first_to_merge
			: second_to_merge;
		node *new_tree_root_child = new_tree_root == first_to_merge
			? second_to_merge
			: first_to_merge;

		if (new_tree_root->children == nullptr)
		{
			new_tree_root->children = new_tree_root_child;
			new_tree_root_child->brother = new_tree_root_child;

			return new_tree_root;
		}

		node *after_maximum_child = new_tree_root->children->brother;
		new_tree_root->children->brother = new_tree_root_child;
		new_tree_root_child->brother = after_maximum_child;

		new_tree_root->children = _priorities_comparer(new_tree_root->children->priority, new_tree_root->children->brother->priority) >= 0
			? new_tree_root->children
			: new_tree_root->children->brother;

		return new_tree_root;
	}

};

#endif