#ifndef TRIE_H
#define TRIE_H

#include <cstring>
#include <stdexcept>

class trie final
{

private:

	struct node final
	{
		int *value;
		node **subtrees;

		node(
			size_t subtrees_count):
				value(nullptr)
		{
			subtrees = new node * [subtrees_count + 1];
			*reinterpret_cast<size_t *>(subtrees) = subtrees_count;
			for (int i = 1; i <= subtrees_count; ++i)
			{
				subtrees[i] = nullptr;
			}
		}

		~node()
		{
			delete value;
		}

		node(
			node const& other):
				subtrees(new node *[reinterpret_cast<size_t>(other.subtrees[0]) + 1])
		{
			value = other.value == nullptr
				? nullptr
				: new int(*other.value);
			subtrees[0] = other.subtrees[0];
			for (int i = 1; i <= reinterpret_cast<size_t>(subtrees[0]); ++i)
			{
				subtrees[i] = nullptr;
			}
		}

		node &operator=(
			node const &other)
		{
			// TODO: You can do it :)

			return *this;
		}
	};

private:

	node *_root;
	char *_alphabet;
	size_t _alphabet_length;

public:

	trie(
		char const *alphabet):
		_root(nullptr),
		_alphabet_length(strlen(alphabet))
	{
		if (_alphabet_length == 0)
		{
			throw std::logic_error("An alphabet can't be empty");
		}

		for (int i = 0; i < _alphabet_length - 1; ++i)
		{
			for (int j = i + 1; j < _alphabet_length; ++j)
			{
				if (alphabet[i] == alphabet[j])
				{
					throw std::logic_error("An alphabet's components must be unique");
				}
			}
		}

		_alphabet = new char[_alphabet_length + 1];
		strcpy(_alphabet, alphabet);
	}

private:

	void free_node_recursive(
		node *&to_free)
	{
		if (to_free == nullptr)
		{
			return;
		}

		for (int i = 1; i <= _alphabet_length; ++i)
		{
			free_node_recursive(to_free->subtrees[i]);
		}

		delete to_free;
		to_free = nullptr;
	}

public:

	~trie()
	{
		delete[] _alphabet;
		free_node_recursive(_root);
	}

	trie(
		trie const &other)
	{
		// TODO
	}

	trie &operator=(
		trie const &other)
	{
		// TODO

		return *this;
	}

private:

	void insert(
		node *&subtree_root,
		char const *key,
		int value)
	{
		if (*key == '\0')
		{
			// node place found
			if (subtree_root == nullptr)
			{
				subtree_root = new node(_alphabet_length);
			}

			if (subtree_root->value != nullptr)
			{
				// TODO: key already exists (exception)
			}

			subtree_root->value = new int(value);
		}

		
	}

public:

	void insert(
		char const *key,
		int value)
	{
		return insert(_root, key, value);
	}

	int &find(
		char const *key)
	{
		// TODO
	}

	void remove(
		char const *key)
	{
		// TODO
	}

};

#endif