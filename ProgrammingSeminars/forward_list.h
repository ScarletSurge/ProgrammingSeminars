#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

typedef struct forward_list_item
{
	int data;
	struct forward_list_item *next;
} forward_list_item;

typedef struct forward_list
{
	forward_list_item *first;
} forward_list;

int create_forward_list(
	forward_list *to_create);

int destroy_forward_list(
	forward_list *to_destroy);

int insert_into_forward_list(
	forward_list *to_insert_into,
	int value,
	int index);

int delete_from_forward_list(
	forward_list *to_delete_from,
	int index,
	int *deleted_value_storage);

int obtain_by_index_in_forward_list(
	forward_list const *to_obtain_by_index_in,
	int index,
	int *obtained_value_storage);

// TODO: add traverse
// TODO: add generics parody o_O

#endif