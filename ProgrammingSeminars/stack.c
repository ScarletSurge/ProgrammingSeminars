#include "stack.h"

int create_stack(
	stack* to_create)
{
	return create_forward_list(&to_create->inner);
}

int destroy_stack(
	stack* to_destroy)
{
	return destroy_forward_list(&to_destroy->inner);
}

int stack_push(
	stack* to_push_into,
	int value_to_push)
{
	return insert_into_forward_list(&to_push_into->inner, value_to_push, 0);
}

int stack_peek(
	stack const* to_peek_inside,
	int* result_placement)
{
	return obtain_by_index_in_forward_list(&to_peek_inside->inner, 0, result_placement);
}

int stack_pop(
	stack* to_pop_from,
	int* result_placement)
{
	return delete_from_forward_list(&to_pop_from->inner, 0, result_placement);
}