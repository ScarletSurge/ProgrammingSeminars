#ifndef TRIE_H
#define TRIE_H

#pragma warning(disable: 4996)

#include <cstring>
#include <stdexcept>
#include <string>

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
			subtrees = new node *[1 + subtrees_count];
			*reinterpret_cast<size_t *>(subtrees) = subtrees_count;
			for (int i = 1; i <= subtrees_count; ++i)
			{
				subtrees[i] = nullptr;
			}
		}

		~node()
		{
			delete value;
			delete[] subtrees;
		}

		node(
			node const& other):
				subtrees(new node *[other.get_subtrees_count() + 1])
		{
			value = other.value == nullptr
				? nullptr
				: new int(*other.value);
			subtrees[0] = other.subtrees[0];
			for (int i = 1; i <= get_subtrees_count(); ++i)
			{
				subtrees[i] = nullptr;
			}
		}

		node &operator=(
			node const &other)
		{
			if (this == &other)
			{
				return *this;
			}

			delete[] subtrees;
			delete value;

			subtrees = new node *[1 + other.get_subtrees_count()];
			subtrees[0] = other.subtrees[0];
			for (int i = 1; i <= get_subtrees_count(); ++i)
			{
				subtrees[i] = nullptr;
			}

			value = other.value == nullptr
				? nullptr
				: new int(*other.value);

			return *this;
		}

	public:

		size_t get_subtrees_count() const
		{
			return reinterpret_cast<size_t>(subtrees[0]);
		}

	};

public:

	class iterator final
	{

	private:

		char *key;

	public:

		struct retval
		{
			char *key;
			int &value;
		};

	public:

		iterator &operator++()
		{

		}

		iterator operator++(
			int)
		{

		}

		bool operator==(
			iterator const &other) const
		{

		}

		bool operator!=(
			iterator const &other) const
		{

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

		_alphabet = new char[_alphabet_length];
		memcpy(_alphabet, alphabet, sizeof(char) * _alphabet_length);

		_root = new node(_alphabet_length);
	}

private:

	node *copy_node_recursive(
		node const *to_copy)
	{
		if (to_copy == nullptr)
		{
			return nullptr;
		}

		node *result = new node(*to_copy);

		for (int i = 1; i <= to_copy->get_subtrees_count(); ++i)
		{
			result->subtrees[i] = copy_node_recursive(to_copy->subtrees[i]);
		}

		return result;
	}

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
		trie const &other):
			_root(copy_node_recursive(other._root)),
			_alphabet(new char[_alphabet_length]),
			_alphabet_length(other._alphabet_length)
	{
		memcpy(_alphabet, other._alphabet, sizeof(char) * _alphabet_length);
	}

	trie &operator=(
		trie const &other)
	{
		if (this == &other) return *this;

		delete[] _alphabet;
		free_node_recursive(_root);

		_root = copy_node_recursive(other._root); 
		
		_alphabet = new char[_alphabet_length];
		
		_alphabet_length = other._alphabet_length; 

		memcpy(_alphabet, other._alphabet, sizeof(char) * _alphabet_length);

		return *this;
	}

private:

	size_t get_idx_by_char(
		char maybe_alphabet_element) const
	{
		char *alphabet_item = _alphabet;
		for (int i = 0; i < _alphabet_length; ++i)
		{
			if (maybe_alphabet_element == *alphabet_item)
			{
				break;
			}

			++alphabet_item;
		}

		return alphabet_item - _alphabet;
	}

private:

	void insert(
		node *&subtree_root,
		char const *key,
		int value)
	{
		if (subtree_root == nullptr)
		{
			subtree_root = new node(_alphabet_length);
		}

		if (*key == '\0')
		{
			if (subtree_root->value != nullptr)
			{
				throw std::logic_error("duplicate key");
			}

			subtree_root->value = new int(value);

			return;
		}

		size_t first_character_idx = get_idx_by_char(*key);
		if (first_character_idx == _alphabet_length)
		{
			throw std::invalid_argument("invalid character found");
		}

		insert(subtree_root->subtrees[1 + first_character_idx], key + 1, value);
	}

	int &find(
		node const *subtree_root,
		char const *key) const
	{
		if (subtree_root == nullptr)
		{
			throw std::invalid_argument("subtree_root");
		}

		if (*key == '\0')
		{
			if (subtree_root->value == nullptr)
			{
				throw std::logic_error("value not found by key");
			}

			return *(subtree_root->value);
		}

		size_t first_character_idx = get_idx_by_char(*key);
		if (first_character_idx == _alphabet_length)
		{
			throw std::invalid_argument("invalid character found");
		}

		return find(subtree_root->subtrees[1 + first_character_idx], key + 1);
	}

	void after_removal(
		node *&subtree_root)
	{
		if (subtree_root == _root)
		{
			return;
		}

		if (subtree_root->value != nullptr)
		{
			return;
		}

		for (int i = 1; i < _alphabet_length; ++i)
		{
			if (subtree_root->subtrees[i] != nullptr)
			{
				return;
			}
		}

		delete subtree_root;
		subtree_root = nullptr;
	}

	void remove(
		node *&subtree_root,
		char const *key)
	{
		if (subtree_root == nullptr)
		{
			throw std::out_of_range("key doesn't exist inside trie");
		}

		if (*key == '\0')
		{
			if (subtree_root->value == nullptr)
			{
				throw std::logic_error("value not found by key");
			}

			delete subtree_root->value;
			subtree_root->value = nullptr;

			after_removal(subtree_root);

			return;
		}

		size_t first_character_idx = get_idx_by_char(*key);
		if (first_character_idx == _alphabet_length)
		{
			throw std::invalid_argument("invalid character found");
		}

		remove(subtree_root->subtrees[1 + first_character_idx], key + 1);

		after_removal(subtree_root);
	}

public:

	void insert(
		char const *key,
		int value)
	{
		try
		{
			return insert(_root, key, value);
		}
		catch (std::logic_error const &)
		{
			char exception_message[BUFSIZ];
			strcpy(exception_message, "Can't insert value = ");
			strcat(exception_message, std::to_string(value).c_str());
			strcat(exception_message, " by duplicate key = \"");
			strcat(exception_message, key);
			strcat(exception_message, "\"");

			throw std::logic_error(exception_message);
		}
		// TODO: handle invalid_argument exception instance
	}

	int &find(
		char const *key) const
	{
		return find(_root, key);
	}

	void remove(
		char const *key)
	{
		remove(_root, key);
	}

};

#endif