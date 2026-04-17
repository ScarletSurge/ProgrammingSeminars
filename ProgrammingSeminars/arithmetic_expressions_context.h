#ifndef ARITHMETIC_EXPRESSIONS_CONTEXT_H
#define ARITHMETIC_EXPRESSIONS_CONTEXT_H

#include <cstring>
#include <stdexcept>
#include <stack>

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

		char _operation;
		int (*_operator_action)(
			int left_operand,
			int right_operand);
		node_base *_left_subtree;
		node_base *_right_subtree;

	public:

		explicit node_binary_operator(
			char operation,
			int (*operator_action)(
				int left_operand,
				int right_operand)):
				_operation(operation),
				_operator_action(operator_action),
				_left_subtree(nullptr),
				_right_subtree(nullptr)
		{

		}

	public:

		char get_operation() const
		{
			return _operation;
		}

		node_base *&get_left_subtree()
		{
			return _left_subtree;
		}

		node_base *&get_right_subtree()
		{
			return _right_subtree;
		}

	public:

		int calculate(
			trie &variables_storage) override
		{
			if (_left_subtree == nullptr || _right_subtree == nullptr)
			{
				throw std::logic_error("can't perform binary operator with lower than 2 arguments");
			}

			int left_subtree_result = _left_subtree->calculate(variables_storage);
			int right_subtree_result = _right_subtree->calculate(variables_storage);

			switch (_operation)
			{
			case '+':
				return left_subtree_result + right_subtree_result;
			case '-':
				return left_subtree_result - right_subtree_result;
			case '*':
				return left_subtree_result * right_subtree_result;
			case '/':
				return left_subtree_result / right_subtree_result;
			case '%':
				return left_subtree_result % right_subtree_result;
			}

			throw std::logic_error("?!");
		}

	};

private:

	static arithmetic_expressions_context *_instance;

public:

	static arithmetic_expressions_context& get_instance()
	{
		return *_instance;
	}

private:

	arithmetic_expressions_context() = default;

public:

	arithmetic_expressions_context(
		arithmetic_expressions_context const &) = delete;

private:

	static bool is_identifier_char(
		char c)
	{
		return isalnum(c) || c == '_';
	}

	static bool is_operation(
		char c)
	{
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
	}

	static int priority(
		char operation)
	{
		if (operation == '(')
		{
			return -1;
		}

		if (operation == '+' || operation == '-')
		{
			return 0;
		}

		if (operation == '*' || operation == '/' || operation == '%')
		{
			return 1;
		}

		throw std::invalid_argument("invalid operation");
	}

public:

	node_base *build_expression_tree(
		char const *expression)
	{
		char var_name_buf[BUFSIZ], *vnb = var_name_buf, c_ = ' ';
		int value = 0;
		bool is_variable_name = false;
		std::stack<char> operators;
		std::stack<node_base *> subexpressions;

		operators.push('(');

		char const *e = expression - 1;
		do
		{
			char c = *++e;

			if (is_identifier_char(c))
			{
				if (!is_identifier_char(c_))
				{
					is_variable_name = !isdigit(c);
				}

				if (is_variable_name)
				{
					*vnb++ = c;
				}
				else
				{
					if (!isdigit(c))
					{
						// TODO: clear expression tree and expression subtrees stack
						throw std::invalid_argument("invalid expression syntax");
					}

					value = value * 10 + c - '0';
				}
			}
			else
			{
				if (is_identifier_char(c_))
				{
					node_base *to_push;

					if (is_variable_name)
					{
						*vnb = '\0';
						vnb = var_name_buf;
						to_push = new node_variable(var_name_buf);
					}
					else
					{
						to_push = new node_atom(value);
						value = 0;
					}

					subexpressions.push(to_push);
				}

				if (c == '(')
				{
					operators.push(c);
				}
				else if (c == ')' || c == '\0')
				{
					while (operators.top() != '(')
					{
						node_base *right_subtree = subexpressions.top();
						subexpressions.pop();

						node_base *left_subtree = subexpressions.top();
						subexpressions.pop();

						char operation = operators.top();
						operators.pop();

						// TODO: add operator action
						node_binary_operator *subtree_root = new node_binary_operator(operation, nullptr);
						subtree_root->get_left_subtree() = left_subtree;
						subtree_root->get_right_subtree() = right_subtree;

						subexpressions.push(subtree_root);
					}

					operators.pop();
				}
				else if (is_operation(c))
				{
					while (priority(operators.top()) >= priority(c))
					{
						node_base *right_subtree = subexpressions.top();
						subexpressions.pop();

						node_base *left_subtree = subexpressions.top();
						subexpressions.pop();

						char operation = operators.top();
						operators.pop();

						// TODO: add operator action
						node_binary_operator *subtree_root = new node_binary_operator(operation, nullptr);
						subtree_root->get_left_subtree() = left_subtree;
						subtree_root->get_right_subtree() = right_subtree;

						subexpressions.push(subtree_root);
					}

					operators.push(c);
				}
			}

			c_ = c;
		} while (*e != '\0');

		return subexpressions.top();
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

arithmetic_expressions_context * arithmetic_expressions_context::_instance = new arithmetic_expressions_context;

#endif