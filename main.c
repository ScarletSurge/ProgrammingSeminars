#include <stdio.h>
#include <stdarg.h>

#define __DEBUG

int avg(
    unsigned int,
    double *,
    ...);

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
        c = fgetc(fin);

        // TODO: handle read char from file
    }

    fclose(fin);

    return 0;
}

int main(
    int argc,
    char const *argv[]) // char **argv
{
    // return avg_call_sample();
    return files_interaction_demo(argc, argv);
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