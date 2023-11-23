#include "dynamic_array.h"

int find_by_index_in_array(
        array const *target,
        unsigned int index,
        int *result_value)
{
    if (target == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    // can be used: (*target).size
    if (index >= target->virtual_size)
    {
        return OUT_OF_BOUNDS;
    }

    *result_value = target->elements[index];
    return OK;
}

int find_by_value_in_array(
        array const *target,
        unsigned int value,
        int *result_index)
{
    int i;

    if (target == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    for (i = 0; i < target->virtual_size; i++)
    {
        if (target->elements[i] == value)
        {
            *result_index = i;
            return OK_FOUND;
        }
    }

    return OK_NOT_FOUND;
}

int add_value_into_array(
        array *target,
        int value,
        unsigned int index)
{
    int *reallocated;

    if (index > target->virtual_size)
    {
        return OUT_OF_BOUNDS;
    }

    if (target->virtual_size == target->physical_size)
    {
        reallocated = (int *)realloc(target->elements, sizeof(int) * (target->physical_size << 1));
        if (reallocated == NULL)
        {
            return MEMORY_REALLOCATION_ERROR;
        }

        target->elements = reallocated;
        target->physical_size <<= 1;
    }

    memcpy(target->elements + index + 1, target->elements + index, sizeof(int) * (target->virtual_size - index));
    target->elements[index] = value;
    target->virtual_size++;

    return OK;
}

int create_empty_array(
        array *target)
{
    if (target == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    target->elements = (int *)malloc(sizeof(int) * EMPTY_ARRAY_PHYSICAL_SIZE);
    if (target->elements == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    target->physical_size = EMPTY_ARRAY_PHYSICAL_SIZE;
    target->virtual_size = 0;

    return OK;
}

int free_array(
        array *target)
{
    free(target->elements);
    target->elements = NULL;
    target->physical_size = target->virtual_size = 0;
}

int print_array(
        array const *target,
        FILE *stream)
{
    if (target == NULL || stream == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    int i;

    for (i = 0; i < target->virtual_size; i++)
    {
        fprintf(stream, "%d ", target->elements[i]);
    }

    return OK;
}