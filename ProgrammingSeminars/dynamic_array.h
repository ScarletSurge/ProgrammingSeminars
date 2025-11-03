#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdio.h>

typedef void *T;

typedef struct dynamic_array
{
    T* values;
    size_t virtual_size;
    size_t physical_size;
} dynamic_array, * p_dynamic_array;

int initialize_dynamic_array(
    p_dynamic_array to_init);

int destroy_dynamic_array(
    p_dynamic_array to_destroy);

int find_by_index_inside_dynamic_array(
    dynamic_array const *context,
    unsigned int index,
    T *found_value_target_place);

int insert_by_index_into_dynamic_array(
    p_dynamic_array to_insert_into,
    T const *value_to_insert,
    unsigned int index);

int delete_by_index_from_dynamic_array(
    p_dynamic_array to_delete_from,
    T *deleted_value,
    unsigned int index);

#endif