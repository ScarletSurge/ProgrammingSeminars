#include "dynamic_array.h" 
#include <stdlib.h>

int initialize_dynamic_array(
    p_dynamic_array to_init,
    size_t initial_capacity,
    int (*copy_value)(T* target, T const* source),
    int (*destroy_value)(T* target))
{
    if (to_init == NULL)
    {
        return -2;
    }
    // TODO: validate other parameters

    to_init->copy_value = copy_value;
    to_init->destroy_value = destroy_value;

    to_init->capacity = initial_capacity;
    to_init->size = 0;
    if ((to_init->values = (T*)malloc(sizeof(T) * to_init->capacity)) == NULL)
    {
        return -1;
    }

    return 0;
}

int destroy_dynamic_array(
    p_dynamic_array to_destroy)
{
    if (to_destroy == NULL)
    {
        return -2;
    }
    
    int i;
    for (i = 0; i < to_destroy->size; ++i)
    {
        to_destroy->destroy_value(to_destroy->values + i);
    }

    free(to_destroy->values);
    to_destroy->values = NULL;
    to_destroy->capacity = to_destroy->size = 0;
    to_destroy->copy_value = NULL;
    to_destroy->destroy_value = NULL;
    
    return 0;
}

int find_by_index_inside_dynamic_array(
    dynamic_array const* context,
    unsigned int index,
    T* found_value_target_place)
{
    if (context == NULL) {
        return -1;
    }
    if (index >= context->size) {
        return -2;
    }
    if (found_value_target_place == NULL) {
        return -3;
    }
    *found_value_target_place = context->values[index];
    return 0;
}

int insert_by_index_into_dynamic_array(
    p_dynamic_array to_insert_into,
    T const* value_to_insert,
    unsigned int index)
{
    if (to_insert_into == NULL)
    {
        return -1;
    }

    if (value_to_insert == NULL)
    {
        return -2;
    }

    if (index > to_insert_into->size)
    {
        return -3;
    }

    if (to_insert_into->capacity == to_insert_into->size)
    {
        T* for_realloc = (T*)realloc(to_insert_into->values, sizeof(T) * (to_insert_into->capacity << 1));

        if (for_realloc == NULL)
        {
            return -4;
        }

        to_insert_into->values = for_realloc;
        for_realloc = NULL;
        to_insert_into->capacity <<= 1;
    }

    int i;
    for (i = to_insert_into->size - 1; i >= (int)index; i--)
    {
        //to_insert_into->copy_value(to_insert_into->values + i + 1, to_insert_into->values + i);
        to_insert_into->values[i + 1] = to_insert_into->values[i];
    }

    to_insert_into->copy_value(to_insert_into->values + index, value_to_insert);
    //to_insert_into->values[index] = value_to_insert;
    to_insert_into->size++;

    return 0;
}

int delete_by_index_from_dynamic_array(
    p_dynamic_array to_delete_from,
    T* deleted_value, // TODO: this is hard :/
    unsigned int index)
{
    if (to_delete_from == NULL)
    {
        return -1;
    }

    if (deleted_value == NULL)
    {
        return -2;
    }

    if (index >= to_delete_from->size)
    {
        return -3;
    }
    int find_status;
    switch (find_status = find_by_index_inside_dynamic_array(to_delete_from, index, deleted_value))
    {
    case -1:
    case -2:
    case -3:
        return find_status;
    }
    int i;
    for (i = index; i >= to_delete_from->size - 2; i++)
    {
        to_delete_from->values[i] = to_delete_from->values[i + 1];
    }
    to_delete_from->size--;
    // n: n > 0 && (n & (n - 1) == 0)
    if (to_delete_from->size > 0 && (to_delete_from->size & (to_delete_from->size - 1)) == 0)
    {
        T* for_realloc;
        
        if ((for_realloc = (T *)realloc(to_delete_from->values, sizeof(T) * (to_delete_from->size >> 1))) == NULL)
        {
            return -4;
        }

        to_delete_from->values = for_realloc;
        to_delete_from->capacity >>= 1;
    }

    return 0;
}

int traverse_dynamic_array(
    p_dynamic_array to_traverse,
    size_t start_index_inclusive,
    size_t end_index_exclusive,
    void (*counter_updater)(int *),
    // size_t (*counter_updater)(size_t)
    int (*predicate)(T const* value, int index),
    void (*successor)(T* value, int index))
{
    // TODO: validate parameters
    
    int i = start_index_inclusive;
    for (; i != end_index_exclusive; counter_updater(&i))
    {
        if (!predicate(to_traverse->values + i, i))
        {
            successor(to_traverse->values + i, i);
        }
    }
}

void increment_counter(
    int *counter_addr)
{
    ++*counter_addr;
}

void decrement_counter(
    int *counter_addr)
{
    --*counter_addr;
}

int forward_traverse_dynamic_array(
    p_dynamic_array to_traverse,
    int (*predicate)(T const *value, int index),
    void (*successor)(T *value, int index))
{
    return traverse_dynamic_array(to_traverse, 0, to_traverse->size, increment_counter, predicate, successor);
}

int backward_traverse_dynamic_array(
    p_dynamic_array to_traverse,
    int (*predicate)(T const *value, int index),
    void (*successor)(T *value, int index))
{
    return traverse_dynamic_array(to_traverse, to_traverse->size - 1, -1, decrement_counter, predicate, successor);
}