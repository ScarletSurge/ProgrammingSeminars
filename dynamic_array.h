#ifndef PROGRAMMINGSEMINARS_DYNAMIC_ARRAY_H
#define PROGRAMMINGSEMINARS_DYNAMIC_ARRAY_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define OK 0
#define OUT_OF_BOUNDS 1
#define MEMORY_ALLOCATION_ERROR 2
#define MEMORY_REALLOCATION_ERROR 3
#define DEREFERENCING_NULL_POINTER 4
#define OK_NOT_FOUND 0
#define OK_FOUND 1

#define EMPTY_ARRAY_PHYSICAL_SIZE 16

typedef struct array
{
    int *elements;
    unsigned int physical_size;
    unsigned int virtual_size;
} array;

int find_by_index_in_array(
        array const *target,
        unsigned int index,
        int *result_value);

int find_by_value_in_array(
        array const *target,
        unsigned int value,
        int *result_index);

int add_value_into_array(
        array *target,
        int value,
        unsigned int index);

int create_empty_array(
        array *target);

int free_array(
        array *target);

int print_array(
        array const *target,
        FILE *stream);

#endif //PROGRAMMINGSEMINARS_DYNAMIC_ARRAY_H