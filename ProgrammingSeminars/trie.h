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

	class const_prefix_iterator final
	{

	private:

		trie const *_context;
		char *_key, *_k;
		node **_path, **_path_top;
		size_t _key_max_length, _path_max_length;

	public:

		struct retval
		{
			char const *key;
			int value;
		};

	private:

		template<
			typename T>
		void add(
			T *&to_add_to,
			T *&to_add_to_target_place,
			size_t &to_add_to_max_length,
			T to_add)
		{
			if (to_add_to_target_place - to_add_to == to_add_to_max_length)
			{
				T *new_placement = new T[to_add_to_max_length * 2];
				memcpy(new_placement, to_add_to, sizeof(T) * to_add_to_max_length);
				delete[] to_add_to;
				to_add_to = new_placement;
				to_add_to_target_place = to_add_to + to_add_to_max_length;
				to_add_to_max_length *= 2;
			}

			*to_add_to_target_place++ = to_add;
		}

	public:

		const_prefix_iterator(
			trie const *context,
			bool is_end_iterator):
				_context(context),
				_key(nullptr),
				_k(nullptr),
				_path(nullptr),
				_path_top(nullptr)
		{
			if (is_end_iterator)
			{
				return;
			}

			_k = _key = new char[_key_max_length = 16];
			_path_top = _path = new node *[_path_max_length = 16];

			node *current = _context->_root;
			while (current->value == nullptr)
			{
				node *new_current = nullptr;

				for (int i = 1; i <= current->get_subtrees_count(); ++i)
				{
					if (current->subtrees[i] != nullptr)
					{
						add<char>(_key, _k, _key_max_length, _context->_alphabet[i - 1]);
						add<node *>(_path, _path_top, _path_max_length, current);
						new_current = current->subtrees[i];
						break;
					}
				}

				if (new_current == nullptr)
				{
					// empty trie
					current = nullptr;
					--_path_top;

					break;
				}

				current = new_current;
			}

			add<char>(_key, _k, _key_max_length, '\0');
			add<node *>(_path, _path_top, _path_max_length, current);
		}

		const_prefix_iterator &operator++()
		{
			if (_path == nullptr || _path == _path_top)
			{
				// UB
				return *this;
			}

			// "removing" '\0'
			--_k;

			int start_subtree = 1;
			while (_path_top != _path)
			{
				int i;
				for (i = 1 + start_subtree; i <= (*(_path_top - 1))->get_subtrees_count(); ++i)
				{
					if ((*(_path_top - 1))->subtrees[i] != nullptr)
					{
						add<char>(_key, _k, _key_max_length, _context->_alphabet[i - 1]);
						add<node *>(_path, _path_top, _path_max_length, (*(_path_top - 1))->subtrees[i]);

						if ((*(_path_top - 1))->value != nullptr)
						{
							add<char>(_key, _k, _key_max_length, '\0');

							return *this;
						}

						start_subtree = 0;

						break;
					}
				}

				if (i == (*(_path_top - 1))->get_subtrees_count() + 1)
				{
					--_path_top;
					if (_k != _key)
					{
						start_subtree = _context->get_idx_by_char(*(_k - 1)) + 1;
						*_k-- = '\0';
					}
				}
			}

			return *this;
		}

		const_prefix_iterator operator++(
			int)
		{
			auto result = *this;
			++*this;
			return result;
		}

		bool operator==(
			const_prefix_iterator const &other) const
		{
			if (_context != other._context)
			{
				return false;
			}

			if (_k - _key != other._k - other._key)
			{
				return false;
			}

			return memcmp(_key, other._key, sizeof(char) * (_k - _key)) == 0;
		}

		bool operator!=(
			const_prefix_iterator const &other) const
		{
			return !(*this == other);
		}

		retval operator*() const
		{
			if (_path_top == _path)
			{
				throw std::out_of_range("moving forward from end iterator");
			}

			auto result = retval();
			result.key = _key;
			result.value = *((*(_path_top - 1))->value);
			return result;
		}

	private:

		void destroy_state()
		{
			delete[] _key;
			_k = _key = nullptr;

			delete[] _path;
			_path_top = _path = nullptr;
		}

		void copy_state(
			const_prefix_iterator const &from)
		{
			_context = from._context;

			_key = new char[from._key_max_length];
			memcpy(_key, from._key, sizeof(char) * _key_max_length);
			_k = _key + (from._k - from._key);

			_path = new node *[from._path_max_length];
			memcpy(_path, from._path, sizeof(node *) * _path_max_length);
			_path_top = _path + (from._path_top - from._path);
		}

	public:

		~const_prefix_iterator()
		{
			destroy_state();
		}

		const_prefix_iterator(
			const_prefix_iterator const &other)
		{
			copy_state(other);
		}

		const_prefix_iterator &operator=(
			const_prefix_iterator const &other)
		{
			if (this == &other)
			{
				return *this;
			}

			destroy_state();
			copy_state(other);

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

public:

	const_prefix_iterator cbegin() const
	{
		return const_prefix_iterator(this, false);
	}

	const_prefix_iterator cend() const
	{
		return const_prefix_iterator(this, true);
	}

};

#endif