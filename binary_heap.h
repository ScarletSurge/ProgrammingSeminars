#pragma once

#include <stdio.h>

typedef int T;

typedef struct binary_heap
{
    T *values;
    size_t physical_size;
    size_t virtual_size;
    int (*comparer)(T const *, T const *);
} binary_heap;

int create_binary_heap(
    binary_heap **to_create_under,
    int (*comparer)(T const *, T const *));

int destroy_binary_heap(
    binary_heap **to_destroy_under);

int find_minimum_inside_binary_heap(
    binary_heap const *target,
    T *found_minimum);

int insert_into_binary_heap(
    binary_heap *target,
    T to_insert);

int remove_minimum_from_binary_heap(
    binary_heap *target,
    T *removed_minimum);

int print_binary_heap(
    binary_heap const *target);