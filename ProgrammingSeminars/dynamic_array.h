#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>

typedef void *T;

typedef struct dynamic_array
{
    T* values;
    size_t size;
    size_t capacity;
    int (*copy_value)(T *target, T const *source);
    int (*destroy_value)(T *target);
} dynamic_array, *p_dynamic_array;

int initialize_dynamic_array(
    p_dynamic_array to_init,
    size_t initial_capacity,
    int (*copy_value)(T *target, T const *source),
    int (*destroy_value)(T *target));

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

int traverse_dynamic_array(
    p_dynamic_array to_traverse,
    size_t start_index_inclusive,
    size_t end_index_exclusive,
    void (*counter_updater)(size_t*),
    // size_t (*counter_updater)(size_t)
    int (*predicate)(T const* value, int index),
    void (*successor)(T* value, int index));

int forward_traverse_dynamic_array(
    p_dynamic_array to_traverse,
    int (*predicate)(T const* value, int index),
    void (*successor)(T* value, int index));

int backward_traverse_dynamic_array(
    p_dynamic_array to_traverse,
    int (*predicate)(T const* value, int index),
    void (*successor)(T* value, int index));

#endif