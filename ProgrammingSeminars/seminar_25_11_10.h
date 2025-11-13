#ifndef SEMINAR_25_11_10
#define SEMINAR_25_11_10

#include "dynamic_array.h"
#include <stdlib.h>
#include <time.h>

void print_decimal(
	int value)
{
	printf("%d ", value);
}

void print_hexadecimal(
	int value)
{
	printf("%X ", value);
}

void print_with_my_own_wants(
	int value)
{
	printf("puk-srenjk! %d %X %o\n\n\n", value, value, 52);
}

void print_array(
	int *values,
	size_t values_count,
	/*int flag - бред*/
	void (*action)(int))
{
	// void (*foo)(int) = action;
	int i;
	for (i = 0; i < values_count; ++i)
	{
		action(values[i]);
	}

	// бред сумасшедшего
	/*switch (flag)
	{
	case 0:
		for (i = 0; i < values_count; ++i)
		{
			print_decimal(values[i]);
		}
		break;
	case 1:
		for (i = 0; i < values_count; ++i)
		{
			print_hexadecimal(values[i]);
		}
		break;
	}*/
}

int copy_int2(
	T* target,
	T const* source)
{
	if (!(*target = (T)malloc(sizeof(int))))
	{
		// TODO
	}
	*((int*)*target) = *((int const* const)*source);

	return 0;
}

int destroy_int2(
	T* target)
{
	free(*target);
	*target = NULL;

	return 0;
}

int is_prime(
	int value)
{
	if (value <= 1)
	{
		return 0;
	}
	if (value == 2 || value == 3)
	{
		return 1;
	}
	if (value % 2 == 0 || value % 3 == 0)
	{
		return 0;
	}
	int i;
	for (i = 5; i * i <= value; i += (i % 6 == 5 ? 2 : 4))
	{
		if (value % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int traverse_predicate(
	T const *value_ptr,
	int index)
{
	// is_prime: 1 - prime, 0 - not prime
	// is_prime(...) -> 0 - prime, 1 - not prime
	return !is_prime(*((int const * const)*value_ptr));
}

int traverse_successor(
	T *value_ptr,
	int index)
{
	*((int *)(*value_ptr)) *= *((int*)(*value_ptr));

	return 0;
}

int print_predicate(
	T const* value_ptr,
	int index)
{
	return 0;
}

int print_successor(
	T* value_ptr,
	int index)
{
	printf("%6d ", *((int *)*value_ptr));
	if (index != 0 && index % 10 == 0)
	{
		printf("\n");
	}

	return 0;
}

int seminar_25_11_10(
	int argc,
	char *argv[])
{
	{
		int i;
		int arr[10];
		srand(23456);
		for (i = 0; i < 10; ++i)
		{
			arr[i] = rand() % 201 - 100;
		}

		print_array(arr, 10, print_with_my_own_wants);
	}

	dynamic_array arr;
	switch (initialize_dynamic_array(&arr, 16, copy_int2, destroy_int2))
	{
	case 0:

		break;
	case -1:
		// TODO: handle
		break;
	case -2:
		// TODO: handle
		break;
	}

	{
		int x;
		{
			x = 10;
		}
		T ptr_x = (T)&x;
		// arr.insert(...); - active voice
		switch (insert_by_index_into_dynamic_array(&arr, &ptr_x, 0))
		{
			// TODO: handle status codes
		}
	}

	destroy_dynamic_array(&arr);
	initialize_dynamic_array(&arr, 100, copy_int2, destroy_int2);
	int i;
	int const *ip = &i;
	for (i = 0; i < arr.capacity; ++i)
	{
		insert_by_index_into_dynamic_array(&arr, (T const *)&ip, i);
	}

	printf("Initial array:\n");
	backward_traverse_dynamic_array(&arr, print_predicate, print_successor);
	printf("\n\n");

	backward_traverse_dynamic_array(&arr, traverse_predicate, traverse_successor);

	printf("Modified array:\n");
	backward_traverse_dynamic_array(&arr, print_predicate, print_successor);
	
	destroy_dynamic_array(&arr);

	// 1. Initialize all values (100 elements) inside dyn array as value index
	// 2. Increase value by its index if and only if value is prime
	// 3. Print values of array (backward)

	return 0;
}

#endif