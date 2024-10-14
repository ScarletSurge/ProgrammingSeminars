#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "include\dump.h"

#define __DEBUG

#define MALLOC_PUK_SRENJK 1

void free_all(
    void *to_free,
    ...)
{
    va_list p;

    if (to_free == NULL)
    {
        return;
    }

    va_start(p, to_free);

    do
    {
        free(to_free);

        to_free = va_arg(p, void *);
    }
    while (to_free != NULL);
}

int avg(
    unsigned int,
    double *,
    ...);

int dynamic_structures_intro(
    int argc,
    char *argv[])
{
    char *p2, *p3;
    char *p = (char *)malloc(100 * sizeof(char));
    if (!p)
    {
        return MALLOC_PUK_SRENJK;
    }

    if (!(p2 = (char *)malloc(100 * sizeof(char))))
    {
        free(p);

        return MALLOC_PUK_SRENJK;
    }

    if (!(p3 = (char *)malloc(100 * sizeof(char))))
    {
        free_all(p, p2, NULL);

        return MALLOC_PUK_SRENJK;
    }

    return 0;
}

int avg_call_sample()
{
    double result;
    printf("Hello, World!\n", 1, 'c', "12345");

    switch (avg(4, &result, (double)1, (double)2, (double)3, (double)4))
    {
        case 0:
            printf("Average value == %lf\n", result);
            break;
        case 1:
            printf("Invalid values count!");
            break;
        case 2:
            printf("Invalid result address value!");
            break;
    }

    return 0;
}

void handle_read_char(
    int read_char)
{
    putchar(read_char);
}

int float_format_output(
    int argc,
    char *argv[])
{
    float f = -123.45;

    printf("%08X", *(int *)&f);

    return 0;
}

int files_interaction_demo(
    int argc,
    char const *argv[])
{
    FILE *fin;
    char c;

    if (argc != 2)
    {
        return -1;
    }

    if (!(fin = fopen(argv[1], "r")))
    {
        return -2;
    }

    // file reading loop with EOF handling
    while (!feof(fin))
    {
        handle_read_char(c = fgetc(fin));
    }

    printf("\n\n\n");

    fclose(fin);
    if (!(fin = fopen(argv[1], "r")))
    {
        return -2;
    }

    while ((c = fgetc(fin)) != EOF)
    {
        handle_read_char(c);
    }

    fclose(fin);

    return 0;
}

int dump_demo(
    int argc,
    char *argv)
{
    size_t value = -1;
    dump_bytes((unsigned char const *)&value, sizeof(value), stdout);

    printf(" %zu", value);

    return 0;
}

int main(
    int argc,
    char *argv[]) // char **argv
{
    // return avg_call_sample();
    // return files_interaction_demo(argc, argv);
    // return float_format_output(argc, argv);
    // switch (dynamic_structures_intro(argc, argv))

    return dump_demo(argc, argv);
}

int avg(
    unsigned int values_count,
    double *result_placement,
    ...)
{
    int i; // i, j, k, x, y, z
    double result = 0;
    va_list iterator;
    double got_from_va_arg;

    if (values_count == 0)
    {
        return 1;
    }

    if (result_placement == NULL)
    {
        return 2;
    }

    va_start(iterator, result_placement);

    for (i = 0; i < values_count; ++i)
    {
        result += (got_from_va_arg = va_arg(iterator, double));
#ifdef __DEBUG
        printf("Got an argument with value == %lf\n", got_from_va_arg);
#endif
    }

    va_end(iterator);

    *result_placement = result / values_count;

    return 0;
}