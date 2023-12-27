#include "binary_heap.h"
#include <stdlib.h>

#define ЛЮБЛИНО_РАБОТАЕМ 0

void swap(
    T *left,
    T *right)
{
    T temp = *left;
    *left = *right;
    *right = temp;
}

int create_binary_heap(
        binary_heap **to_create_under,
        int (*comparer)(T const *, T const *))
{
    const int initial_heap_physical_size = 16;

    if (to_create_under == NULL)
    {
        return 1;
    }

    if (comparer == NULL)
    {
        return 2;
    }

    if (!(*to_create_under = (binary_heap *)malloc(sizeof(binary_heap))))
    {
        return 3;
    }

    if (!((*to_create_under)->values = (T *)malloc(sizeof(T) * initial_heap_physical_size)))
    {
        free(*to_create_under);
        *to_create_under = NULL;
        return 4;
    }

    (*to_create_under)->comparer = comparer;
    (*to_create_under)->physical_size = initial_heap_physical_size;
    (*to_create_under)->virtual_size = 0;

    return ЛЮБЛИНО_РАБОТАЕМ;
}

int destroy_binary_heap(
    binary_heap **to_destroy_under)
{
    if (to_destroy_under == NULL)
    {
        return 1;
    }

    if (*to_destroy_under == NULL)
    {
        return 2;
    }

    free((*to_destroy_under)->values);
    free(*to_destroy_under);
    *to_destroy_under = NULL;

    return ЛЮБЛИНО_РАБОТАЕМ;
}

int find_minimum_inside_binary_heap(
        binary_heap const *target,
        T *found_minimum)
{
    if (target == NULL)
    {
        return 1;
    }

    if (found_minimum == NULL)
    {
        return 2;
    }

    if (target->virtual_size == 0)
    {
        return 3;
    }

    *found_minimum = target->values[0];

    return 0;
}

int insert_into_binary_heap(
        binary_heap *target,
        T to_insert)
{
    return 0;
}

int remove_minimum_from_binary_heap(
        binary_heap *target,
        T *removed_minimum)
{
    int sift_down_element_index = 0;
    int left_child_index, right_child_index;
    int comparison_result;

    if (target == NULL)
    {
        return 1;
    }

    if (removed_minimum == NULL)
    {
        return 2;
    }

    if (target->virtual_size == 0)
    {
        return 3;
    }

    *removed_minimum = target->values[0];

    target->values[0] = target->values[--target->virtual_size];

    while (1)
    {
        left_child_index = 2 * sift_down_element_index + 1;
        right_child_index = 2 * sift_down_element_index + 2;

        if (right_child_index >= target->virtual_size)
        {
            if (left_child_index >= target->virtual_size)
            {
                break;
            }

            if (target->comparer(target->values + sift_down_element_index, target->values + left_child_index) > 0)
            {
                swap(target->values + sift_down_element_index, target->values + left_child_index);
            }

            break;
        }
        else
        {
            comparison_result = target->comparer(target->values + left_child_index, target->values + right_child_index);

            if (comparison_result >= 0)
            {
                if (target->comparer(target->values + sift_down_element_index, target->values + right_child_index) > 0)
                {
                    swap(target->values + sift_down_element_index, target->values + right_child_index);

                    sift_down_element_index = right_child_index;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (target->comparer(target->values + sift_down_element_index, target->values + left_child_index) > 0) {
                    swap(target->values + sift_down_element_index, target->values + left_child_index);

                    sift_down_element_index = left_child_index;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return 0;
}

int print_binary_heap(
    binary_heap const *target)
{
    int i;

    if (target == NULL)
    {
        return 1;
    }

    printf("[ ");
    for (i = 0; i < target->virtual_size; i++)
    {
        printf("%d ", target->values[i]);
    }
    printf("]\n");

    return 0;
}