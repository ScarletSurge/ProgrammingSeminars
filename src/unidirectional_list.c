#include "..\include\unidirectional_list.h"
#include <stdio.h>
#include <malloc.h>

#define DEREFERENCING_NULL_POINTER_ATTEMPT 1
#define OK 0
#define ELEMENT_UNACCESSABLE 3
#define MEMORY_ALLOCATION_ERROR 2

int create_ul(
    p_unidirectional_list to_create)
{
    if (to_create == NULL) {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    to_create->first = NULL;
    return OK;
}

int ul_get_values_count(
    unidirectional_list const * list_pointer,
    size_t *size_placement)
{
    p_unidirectional_list_item item;
    size_t size = 0;
    if (list_pointer == NULL || size_placement == NULL)
    {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    item = list_pointer->first;
    while(item){
        size++;
        item = item->next;
    }
    *size_placement = size;
    return OK;
}

int ul_insert_value(
    p_unidirectional_list to_insert_into,
    T value,
    size_t target_position)
{
    int i;
    size_t count = 0;
    p_unidirectional_list_item item = NULL;
    p_unidirectional_list_item temp = NULL;

    if (!to_insert_into)
    {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (target_position == 0)
    {
        item = (p_unidirectional_list_item)malloc(sizeof(unidirectional_list_item));
        if (!item)
        {
            return MEMORY_ALLOCATION_ERROR;
        }
        item->next = to_insert_into->first;
        to_insert_into->first = item;
        item->data = value;
        return OK;
    }

    for (i = 0; i < target_position - 1; ++i) {
        if (item->next) {
            item = item->next;
        }
    }

    temp = item->next;
    item->next = (p_unidirectional_list_item)malloc(sizeof(unidirectional_list_item));

    if (!item->next)
    {
        item->next = temp;
        return MEMORY_ALLOCATION_ERROR;
    }

    item->next->next = temp;
    item->next->data = value;

    return OK;

}

int ul_remove_value(
    p_unidirectional_list to_remove_from,
    size_t target_position,
    T *removed_value_box)
{
    p_unidirectional_list_item ptr, temp;
    int i;
    if (to_remove_from == NULL || removed_value_box == NULL){
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }
    if (to_remove_from->first == NULL){
        return ELEMENT_UNACCESSABLE;
    }
    if (target_position == 0){
        ptr = to_remove_from->first->next;
        *removed_value_box = to_remove_from->first->data;
        free(to_remove_from->first);
        to_remove_from->first = ptr;
        return OK;
    }
    ptr = to_remove_from->first;
    for (i = 0; i < target_position - 1; ++ i){
        if (ptr->next == NULL){
            return ELEMENT_UNACCESSABLE;
        }
        ptr = ptr->next;
    }
    if (ptr->next == NULL){
        return  ELEMENT_UNACCESSABLE;
    }
    temp = ptr->next->next;
    *removed_value_box = ptr->next->data;
    free(ptr->next);
    ptr->next = temp;
    return OK;
}

int ul_traverse_datas(
    p_unidirectional_list to_traverse,
    void (*callback)(
        T *value_to_traverse,
        size_t index))
{
    p_unidirectional_list_item iterator;
    size_t index = 0;

    if (to_traverse == NULL || callback == NULL)
    {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    iterator = to_traverse->first;

    while (iterator != NULL)
    {
        callback(&iterator->data, index++);

        iterator = iterator->next;
    }
}

int ul_traverse_items(
    p_unidirectional_list to_traverse,
    void (*callback)(
        p_unidirectional_list_item *value_to_traverse,
        size_t index))
{
    p_unidirectional_list_item iterator, temp;
    size_t index = 0;

    if (to_traverse == NULL || callback == NULL)
    {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    iterator = to_traverse->first;

    while (iterator != NULL)
    {
        temp = iterator->next;

        callback(&iterator, index++);

        iterator = temp;
    }
}

void clear_traverse_callback(
    p_unidirectional_list_item *value_to_traverse,
    size_t index)
{
    free(*value_to_traverse);
    *value_to_traverse = NULL;
}

int clear_ul(
    p_unidirectional_list to_clear)
{
    if (to_clear == NULL)
    {
        return DEREFERENCING_NULL_POINTER_ATTEMPT;
    }

    ul_traverse_items(to_clear, clear_traverse_callback);

    return OK;
}