#ifndef PROGRAMMINGSEMINARS_UNIDIRECTIONAL_LIST_H
#define PROGRAMMINGSEMINARS_UNIDIRECTIONAL_LIST_H

// ulist, blist, urlist, ublist, queue (FIFO), stack (LIFO), deque

typedef struct unidirectional_list_item
{
    int data;
    struct unidirectional_list_item* next;
} unidirectional_list_item;

typedef struct unidirectional_list
{
    unidirectional_list_item *first;
} unidirectional_list;

int allocate_list_item(
    unidirectional_list_item **result,
    int value,
    unidirectional_list_item *next);

int create_unidirectional_list(
    unidirectional_list *list);

int delete_unidirectional_list(
    unidirectional_list *list);

int insert_value_into_unidirectional_list(
    unidirectional_list *list,
    int value,
    int position);

int get_value_from_unidirectional_list_by_index(
    unidirectional_list *list,
    int index,
    int *result);

int get_value_from_unidirectional_list_by_value(
    unidirectional_list *list,
    int value,
    int **result_indices,
    int *result_indices_count);

int delete_value_from_unidirectional_list(
    unidirectional_list *list,
    int position,
    int *result);

int traverse_list(
    unidirectional_list *list,
    void (*callback)(int *));

// 1. create list
// 2. delete list
// 3. insert value into list by position
// 4. get value from list by index
// 5. get value from list by value
// 6. delete value from list by index
// 7. traverse list

#endif //PROGRAMMINGSEMINARS_UNIDIRECTIONAL_LIST_H
