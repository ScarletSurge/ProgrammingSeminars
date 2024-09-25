#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INPUT_ERROR (10)

// TODO: enum
// TODO: fork + exec

int sum(int, int);

int demo1();

void demo2_foo(int *);
int demo2();

int demo3();

int demo4();

int demo5();

int main()
{
    // printf("%d\n\n", sum('0', '0'));
    // return demo1();
    // return demo2();
    // return demo3();
    // return demo4();
    return demo5();
}

int sum(
    int left_summand,
    int right_summand)
{
    int result = left_summand + right_summand;

    return result;
}

int demo1()
{
    int sum_result = 0;
    int left_summand = 0, right_summand = 0;
    int x = printf("Hello, World!");
    printf(" x = %d\n", x);

    // == !=

    printf("Enter first summand (int value): ");
    if (scanf("%d", &left_summand) != 1)
    {
        printf("input error!");
        return INPUT_ERROR;
    }

    printf("Enter second summand (int value): ");
    if (scanf("%d", &right_summand) != 1)
    {
        printf("input error!");
        return INPUT_ERROR;
    }

    sum_result = sum(left_summand, right_summand);

    printf("%d\n", sum_result);
}

void demo2_foo(
    int *value_ptr)
{
    *value_ptr = 52;
}

int demo2()
{
    int value = 10;
    int *value_pointer;

    demo2_foo(value_pointer = &value);

    printf("value == %d\n", value);

    return 0;
}

int demo3()
{
    int const immutable_value = 10;
    int const immutable_value2 = 20;

    int *value_ptr = &immutable_value;
    value_ptr = &immutable_value2;

    *value_ptr = 20;

    return 0;
}

int demo4()
{
    int const array_length = 15;
    int i = 0;
    int arr[array_length];

    for (i = 0; i < array_length; ++i)
    {
        // *(arr + i)
        // *(i + arr)
        printf("%d ", 2 + (i[arr] = i));
    }

    printf("\n");

    for (i = 0; i < array_length; ++i)
    {
        // *(arr + i)
        // *(i + arr)
        printf("%d ", arr[i]);
    }

    return 0;
}

int demo5()
{
    int i;
    char buf[BUFSIZ] = { 0 };

    printf("Input string value: ");
    scanf("%s", buf);

    printf("String length == %d\n\n", strlen(buf));

    for (i = 0; i < strlen(buf); ++i)
    {
        printf("%d ", (int const)buf[i]);
    }
    printf("\n%s", buf);

    return 0;
}