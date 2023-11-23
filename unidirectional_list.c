#include "unidirectional_list.h"

#include <stdio.h>
#include <malloc.h>

int allocate_list_item(
    unidirectional_list_item **result,
    int value,
    unidirectional_list_item *next)
{
    unidirectional_list_item *created_item;

    if (result == NULL)
    {
        return 1;
    }

    if ((created_item = (unidirectional_list_item *)malloc(sizeof(unidirectional_list_item))) == NULL)
    {
        return 2;
    }

    created_item->data = value;
    created_item->next = next;
    *result = created_item;

    return 0;
}

int create_unidirectional_list(
    unidirectional_list *list)
{
    if (list == NULL)
    {
        // TODO: this is bad, make enum or define
        return 1;
    }

    list->first = NULL;
    return 0;
}

int delete_unidirectional_list(
    unidirectional_list *list)
{

}

int insert_value_into_unidirectional_list(
    unidirectional_list *list,
    int value,
    int position)
{
    unidirectional_list_item *item_to_insert, *iterator;
    int i;

    if (list == NULL)
    {
        return 1;
    }

    if (position < 0)
    {
        return 2;
    }

    if (position == 0)
    {
        // insertion at beginning
        switch (allocate_list_item(&item_to_insert, value, list->first))
        {
            case 0:
                break;
            case 1:
                // TODO: handling not needed
                break;
            case 2:
                return 3;
        }

        list->first = item_to_insert;
        return 0;
    }

    iterator = list->first;
    for (i = 0; i < position - 1; i++)
    {
        if ((iterator = iterator->next) == NULL)
        {
            return 4;
        }
    }

    switch (allocate_list_item(&item_to_insert, value, iterator->next))
    {
        case 0:
            break;
        case 1:
            // TODO: handling not needed
            break;
        case 2:
            return 3;
    }

    iterator->next = item_to_insert;
    return 0;
}

int get_value_from_unidirectional_list_by_index(
        unidirectional_list *list,
        int index,
        int *result)
{

}

int get_value_from_unidirectional_list_by_value(
        unidirectional_list *list,
        int value,
        int **result_indices,
        int *result_indices_count)
{

}

int delete_value_from_unidirectional_list(
        unidirectional_list *list,
        int position,
        int *result)
{

}

int traverse_list(
    unidirectional_list *list,
    void (*callback)(int *))
{
    unidirectional_list_item *iterator;

    if (list == NULL)
    {
        return 1;
    }

    iterator = list->first;
    while (iterator != NULL)
    {
        callback(&(iterator->data));
        iterator = iterator->next;
    }

    return 0;
}