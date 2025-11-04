#include "dynamic_array.h" 
#include <stdlib.h>

int initialize_dynamic_array(
    p_dynamic_array to_init)
{
    if (to_init == NULL)
    {
        return -2;
    }
    to_init->physical_size = 16;
    to_init->virtual_size = 0;
    if ((to_init->values = (T*)malloc(sizeof(T) * to_init->physical_size)) == NULL)
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
    free(to_destroy->values);
    to_destroy->values = NULL;
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
    if (index >= context->virtual_size) {
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

    if (index > to_insert_into->virtual_size)
    {
        return -3;
    }

    if (to_insert_into->physical_size == to_insert_into->virtual_size)
    {
        T* for_realloc = (T*)realloc(to_insert_into->values, sizeof(T) * (to_insert_into->physical_size << 1));

        if (for_realloc == NULL)
        {
            return -4;
        }

        to_insert_into->values = for_realloc;
        for_realloc = NULL;
        to_insert_into->physical_size <<= 1;

    }

    int i;
    for (i = to_insert_into->virtual_size - 1; i >= (int)index; i--)
    {
        to_insert_into->values[i + 1] = to_insert_into->values[i];
    }

    to_insert_into->values[index] = value_to_insert;
    to_insert_into->virtual_size++;

    return 0;
}

int delete_by_index_from_dynamic_array(
    p_dynamic_array to_delete_from,
    T* deleted_value,
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

    if (index >= to_delete_from->virtual_size)
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
    for (i = index; i >= to_delete_from->virtual_size - 2; i++)
    {
        to_delete_from->values[i] = to_delete_from->values[i + 1];
    }
    to_delete_from->virtual_size--;
    // n: n > 0 && (n & (n - 1) == 0)
    if (to_delete_from->virtual_size > 0 && (to_delete_from->virtual_size & (to_delete_from->virtual_size - 1)) == 0)
    {
        T* for_realloc;
        
        if ((for_realloc = (T *)realloc(to_delete_from->values, sizeof(T) * (to_delete_from->virtual_size >> 1))) == NULL)
        {
            return -4;
        }

        to_delete_from->values = for_realloc;
        to_delete_from->physical_size >>= 1;
    }

    return 0;
}