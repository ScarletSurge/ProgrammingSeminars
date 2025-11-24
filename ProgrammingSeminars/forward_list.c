#include "forward_list.h"
#include <stdio.h>
#include <malloc.h>

// TODO: препаду лень делать валидацыэ((9(9

int create_forward_list(
	forward_list* to_create)
{
	to_create->first = NULL;
	return 0;
}

int destroy_forward_list(
	forward_list* to_destroy)
{
	while (to_destroy->first != NULL)
	{
		delete_from_forward_list(to_destroy, 0, NULL);
	}

	return 0;
}

int insert_into_forward_list(
	forward_list* to_insert_into,
	int value,
	int index)
{
	forward_list_item* for_malloc = (forward_list_item*)malloc(sizeof(forward_list_item));
	// validate 
	for_malloc->data= value;
	if (index == 0)
	{
		for_malloc->next = to_insert_into->first;
		to_insert_into->first = for_malloc;
		return 0;
	}
	int i;
	forward_list_item *previous = to_insert_into->first;
	for (i = 0; i < index - 1; ++i)
	{
		if (previous == NULL)
		{
			return 1;
		}
		previous = previous->next;
	}
	forward_list_item* temp = previous->next;
	previous->next = for_malloc;
	for_malloc->next = temp;
	return 0;
}

int delete_from_forward_list(
	forward_list* to_delete_from,
	int index,
	int* deleted_value_storage)
{	
	if (index == 0)
	{
		if (to_delete_from->first == NULL)
		{
			return 1;
		}

		forward_list_item* temp = to_delete_from->first->next;
		if (deleted_value_storage != NULL)
		{
			*deleted_value_storage = to_delete_from->first->data;
		}
		free(to_delete_from->first);
		to_delete_from->first = temp;
		return 0;
	}

	int i;
	forward_list_item *previous = to_delete_from->first;
	for (i = 0; i < index - 1; ++i)
	{
		if (previous == NULL)
		{
			return 2;
		}
		previous = previous->next;
	}
	if (previous == NULL)
	{
		return 2;
	}
	if (previous->next == NULL)
	{
		return 2;
	}

	forward_list_item* to_delete = previous->next;
	previous->next = previous->next->next;
	if (deleted_value_storage != NULL)
	{
		*deleted_value_storage = to_delete->data;
	}
	free(to_delete);
	return 0;
}

int obtain_by_index_in_forward_list(
	forward_list const* to_obtain_by_index_in,
	int index,
	int* obtained_value_storage)
{
	// TODO: You can do it o_O
}