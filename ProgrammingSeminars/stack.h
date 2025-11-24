#ifndef STACK_H
#define STACK_H

#include "forward_list.h"

typedef struct stack
{
	forward_list inner;
} stack;

int create_stack(
	stack *to_create);

int destroy_stack(
	stack *to_destroy);

int stack_push(
	stack *to_push_into,
	int value_to_push);

int stack_peek(
	stack const* to_peek_inside,
	int* result_placement);

int stack_pop(
	stack *to_pop_from,
	int* result_placement);

#endif