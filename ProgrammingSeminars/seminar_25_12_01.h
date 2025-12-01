#ifndef SEMINAR_25_12_01
#define SEMINAR_25_12_01

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "dynamic_array.h"

int calculate_infix_expression_without_postfix(
	char const* expression,
	int* expression_result)
{

}

int convert_to_postfix_form_dynarr_copy_value(
	T *target,
	T const *source)
{
	if (!(*target = (T)malloc(sizeof(char))))
	{
		return 1;
	}

	*((char *)*target) = *((char const *)*source);

	return 0;
}

int convert_to_postfix_form_dynarr_destroy_value(
	T* target)
{
	free(*target);

	return 0;
}

int priority(
	char operation)
{
	switch (operation)
	{
	case '+':
	case '-':
		return 0;
	case '*':
	case '/':
		return 1;
	default:
		return -1;
	}
}

int convert_infix_expression_to_postfix_form(
	char const* infix_expression,
	char** postfix_expression)
{
	stack operations;
	dynamic_array result_storage;
	initialize_dynamic_array(&result_storage, strlen(infix_expression), convert_to_postfix_form_dynarr_copy_value, convert_to_postfix_form_dynarr_destroy_value);

	stack_push(&operations, '(');
	char const* ie = infix_expression;
	char cp = ' ';
	char buf[1] = { ' ' };
	while (1)
	{
		if (isdigit(*ie))
		{
			// TODO: maybe there is smth wrong o_O
			insert_by_index_into_dynamic_array(&result_storage, (T const *)&ie, result_storage.size);
		}
		else if (isdigit(cp))
		{
			insert_by_index_into_dynamic_array(&result_storage, (T const *)&buf, result_storage.size);
		}
		if (*ie == '(')
		{
			stack_push(&operations, '(');
		}
		else if (*ie == '+' || *ie == '-' || *ie == '*' || *ie == '/')
		{
			int peek_operation;
			stack_peek(&operations, &peek_operation);
			while (priority(*ie) >= priority(peek_operation))
			{
				stack_pop(&operations, &peek_operation);
				*buf = *(char *)&peek_operation;
				insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				*buf = ' ';
				insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				stack_peek(&operations, &peek_operation);
				if (peek_operation == '(')
				{
					break;
				}
			}
			insert_by_index_into_dynamic_array(&result_storage, (T const *)&ie, result_storage.size);
			insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
		}
		else if (*ie == ')' || *ie == '\0')
		{
			int peek_operation;
			stack_peek(&operations, &peek_operation);
			while (peek_operation != '(')
			{
				stack_pop(&operations, &peek_operation);
				*buf = *(char*)&peek_operation;
				insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				*buf = ' ';
				insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				stack_peek(&operations, &peek_operation);
			}
			stack_pop(&operations, &peek_operation);

			if (*ie == '\0')
			{
				break;
			}
		}

		cp = *ie;
		++ie;
	}

	char *result = (char *)malloc(sizeof(char) * (result_storage.size + 1));
	if (!result)
	{
		// TODO: handle o_O
	}

	int i;
	for (i = 0; i < result_storage.size; ++i)
	{
		find_by_index_inside_dynamic_array(&result_storage, i, &buf);
		result[i] = *buf;
	}
	result[result_storage.size] = '\0';
	*postfix_expression = result;
	return 0;
}

int calculate_postfix_expression(
	char const* postfix_expression)
{

}

int calculate_infix_expression_with_postfix(
	char const* expression,
	int* expression_result)
{
	char* postfix_expression;
	convert_infix_expression_to_postfix_form(expression, &postfix_expression);
	printf("Infix expression: \"%s\"\n", expression);
	printf("Postfix expression: \"%s\"\n", postfix_expression);
	int result = calculate_postfix_expression(postfix_expression);
	free(postfix_expression);
	*expression_result = result;
	return 0;
}

int stack_print_successor(
	int* value,
	int index)
{
	printf("%d ", *value);
	return 0;
}

int seminar_25_12_01(
	int argc,
	char* argv[])
{
	stack st;
	create_stack(&st);
	stack_push(&st, 8);
	stack_push(&st, 11);
	stack_push(&st, 37);
	stack_push(&st, 997);
	
	printf("[ ");
	traverse_forward_list(&st.inner, stack_print_successor);
	printf("]\n");

	int rem;
	while (!stack_is_empty(&st))
	{
		printf("[ ");
		stack_pop(&st, &rem);
		traverse_forward_list(&st.inner, stack_print_successor);
		printf("]\n");
	}
	
	destroy_stack(&st);

	int expression_result;
	//calculate_infix_expression_without_postfix("((7 -3)*(11-(4- 7)) / (11+(33-6)*3)", &expression_result);
	calculate_infix_expression_with_postfix("((7 -3)*(11-(4- 7)) / (11+(33-6)*3)", &expression_result);

	return 0;
}

#endif