#ifndef SEMINAR_25_12_01
#define SEMINAR_25_12_01

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "dynamic_array.h"

int stack_print_successor(
	int* value,
	int index)
{
	printf("%d ", *value);
	return 0;
}

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
	case '(':
		return 255;
	case '+':
	case '-':
		return 0;
	case '*':
	case '/':
	case '%':
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
	create_stack(&operations);

	stack_push(&operations, '(');
	char const* ie = infix_expression;
	char cp = ' ';
	char *buf = (char *)malloc(sizeof(char));
	// TODO: validate
	*buf = ' ';
	while (1)
	{
		//printf("%c", *ie);
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
		else if (*ie == '+' || *ie == '-' || *ie == '*' || *ie == '/' || *ie == '%')
		{
			int peek_operation;
			stack_peek(&operations, &peek_operation);
			while (priority(peek_operation) >= priority(*ie))
			{
				if (peek_operation == '(')
				{
					break;
				}
				stack_pop(&operations, &peek_operation);
				*buf = *(char *)&peek_operation;
				insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				*buf = ' ';
				insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				stack_peek(&operations, &peek_operation);
			}
			stack_push(&operations, *ie);
			//insert_by_index_into_dynamic_array(&result_storage, (T const *)&ie, result_storage.size);
			//insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
		}
		else if (*ie == ')' || *ie == '\0')
		{
			/*if (*ie == '\0')
			{
				traverse_forward_list(&operations.inner, stack_print_successor);
			}*/
			int peek_operation;
			stack_peek(&operations, &peek_operation);
			while (peek_operation != '(')
			{
				stack_pop(&operations, &peek_operation);
				*buf = *(char*)&peek_operation;
				insert_by_index_into_dynamic_array(&result_storage, (T const *)&buf, result_storage.size);
				*buf = ' ';
				if (*ie != '\0')
				{
					insert_by_index_into_dynamic_array(&result_storage, (T const*)&buf, result_storage.size);
				}
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
	free(buf);
	// TODO: fix this
	//destroy_dynamic_array(&result_storage);
	destroy_stack(&operations);
	return 0;
}

int calculate_postfix_expression(
	char const *postfix_expression,
	int *expression_calculation_result)
{
	stack values;
	create_stack(&values);
	int value = 0;
	int left_operand, right_operand;

	// value = 45
	// 123 45 +
	// 123 45|<-stack

	char const* pe = postfix_expression;
	char c_ = ' ';
	while (*pe != '\0')
	{
		if (isdigit(*pe))
		{
			value = value * 10 + *pe - '0';
		}
		else if (isdigit(c_))
		{
			stack_push(&values, value);
			value = 0;
		}
		else if (*pe == '+' || *pe == '-' || *pe == '*' || *pe == '/' || *pe == '%')
		{
			stack_pop(&values, &right_operand);
			stack_pop(&values, &left_operand);

			switch (*pe)
			{
			case '+':
				stack_push(&values, left_operand + right_operand);
				break;
			case '-':
				stack_push(&values, left_operand - right_operand);
				break;
			case '*':
				stack_push(&values, left_operand * right_operand);
				break;
			case '/':
				if (right_operand == 0)
				{
					destroy_stack(&values);
					return 1;
				}
				stack_push(&values, left_operand / right_operand);
				break;
			case '%':
				if (right_operand == 0)
				{
					destroy_stack(&values);
					return 1;
				}
				if (right_operand < 0)
				{
					destroy_stack(&values);
					return 2;
				}
				stack_push(&values, left_operand % right_operand);
				break;
			}
		}

		c_ = *pe;
		++pe;
	}

	stack_pop(&values, expression_calculation_result);
	destroy_stack(&values);

	return 0;
}

int calculate_infix_expression_with_postfix(
	char const* expression,
	int* expression_result)
{
	char* postfix_expression;
	int conversion_result = convert_infix_expression_to_postfix_form(expression, &postfix_expression);
	if (conversion_result != 0)
	{
		return conversion_result;
	}
	printf("Infix expression: \"%s\"\n", expression);
	printf("Postfix expression: \"%s\"\n", postfix_expression);
	int calculation_result = calculate_postfix_expression(postfix_expression, expression_result);
	free(postfix_expression);
	return calculation_result;
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
	switch (calculate_infix_expression_with_postfix("75 % (5-6)", &expression_result))
	{
	case 0:
		printf("Calculated result: %d", expression_result);
		break;
	case 1:
		printf("Division by zero!");
		break;
	case 2:
		printf("Modulo division by negative value!");
		break;
	}
	return 0;
}

// -7 % -6 -> (-7 + 2*6) % 6 -> 5 % 6

// 7 % (7 - 8)
// (7 -3)*(11-(4- 7)) / (11+(33-6)*3)
// (<-stack
// 7 3 - 11 4 7 - - * 11 33 6 - 3 * + / 

#endif