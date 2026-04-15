#ifndef ARITHMETIC_EXPRESSIONS_CONTEXT_H
#define ARITHMETIC_EXPRESSIONS_CONTEXT_H

#include <cstring>
#include <stdexcept>

#include "trie.h"

class arithmetic_expressions_context final
{

public:

	struct node_base
	{

	public:

		virtual ~node_base() noexcept = default;

	public:

		virtual int calculate(
			trie &variables_storage) = 0;

	};

	struct node_atom final:
		public node_base
	{

	private:

		int _value;

	public:

		explicit node_atom(
			int value):
				_value(value)
		{

		}

	public:

		int get_value() const noexcept
		{
			return _value;
		}

	public:

		int calculate(
			trie &variables_storage) override
		{
			return _value;
		}

	};

	struct node_variable final:
		public node_base
	{

	private:

		char *_variable_name;

	public:

		explicit node_variable(
			char const *variable_name)
		{
			_variable_name = new char[strlen(variable_name) + 1];
			strcpy(_variable_name, variable_name);
		}

		~node_variable() noexcept
		{
			delete[] _variable_name;
			_variable_name = nullptr;
		}

		// TODO: implement rule of 3

	public:

		char const *get_variable_name() const noexcept
		{
			return _variable_name;
		}

	public:

		int calculate(
			trie &variables_storage)
		{
			return variables_storage.find(_variable_name);
		}

	};

	class node_binary_operator final:
		public node_base
	{

	private:

		int (*_operator_action)(
			int left_operand,
			int right_operand);
		node_base *left_subtree;
		node_base *right_subtree;

	public:

		explicit node_binary_operator(
			int (*operator_action)(
				int left_operand,
				int right_operand)):
				_operator_action(operator_action),
			left_subtree(nullptr),
			right_subtree(nullptr)
		{

		}

	public:

		int calculate(
			trie &variables_storage) override
		{
			if (left_subtree == nullptr || right_subtree == nullptr)
			{
				throw std::logic_error("can't perform binary operator with lower than 2 arguments");
			}

			return _operator_action(left_subtree->calculate(variables_storage), right_subtree->calculate(variables_storage));
		}

	};

private:

	arithmetic_expressions_context() = default;

public:

	node_base *build_expression_tree(
		char const *expression)
	{
		// TODO: ?!

		return nullptr;
	}

	int calculate_expression(
		char const *expression,
		trie &variables_storage)
	{
		node_base *expression_tree = build_expression_tree(expression);
		int expression_result = expression_tree->calculate(variables_storage);
		// TODO: delete built expression tree
		return expression_result;
	}

};

#endif