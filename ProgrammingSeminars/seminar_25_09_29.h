#ifndef SEMINAR_25_09_29
#define SEMINAR_25_09_29

#include <stdio.h>
#include <limits.h>

int seminar_25_09_29(
	int argc,
	char *argv[])
{
    // malloc, calloc, realloc, free - read about it
    // lvalue, rvalue

    int x = 5, y = 10;
    x = y;
    printf("%p\n\n", &x);

    // definition
    int *ptr_to_x = &x;

    int *p = ptr_to_x + 3;
    printf("sizeof(int) == %d\n", sizeof(int)); // expression-or-type
    printf("INT_MAX + 1 == INT_MIN - %s\n",
        INT_MAX + 1 == INT_MIN
            ? "true"
            : "false");

    x;
    y;
    ptr_to_x = &y;
    *ptr_to_x = 7;

    printf("%d\n\n", y);

    int i = 0;
    int arr[10] = { 0 };
    arr[0] = 10;
    printf("arr[%d] == %d\n\n", 1, *arr);

    // arr[i]
    // *(arr + i)
    // i[arr]

    for (i = 0; i < 10; ++i)
    {
        arr[i] = i + 1;
    }

    for (i = 0; i < 10; ++i)
    {
        printf("%d at 0x%p\n", arr[i], arr + i);
    }

	return 0;
}

#endif