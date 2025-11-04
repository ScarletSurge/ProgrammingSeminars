#ifndef SEMINAR_25_10_13
#define SEMINAR_25_10_13

#include <stdio.h>
#include <stdarg.h>

#define MACRO_KEY хы
#define MUL(x, y) ((x) *\
 (y))

int avg(
    size_t values_count,
    double* target,
    ...);

int seminar_25_10_13(
	int argc,
	char *argv[])
{
    int Arsenya = -2;
    printf("%d\n", ++Arsenya);
    printf("%d\n\n", Arsenya);
    
    int i;
    for (i = 0; i < argc; ++i)
    {
        printf("argv[%d] == \"%s\"\n", i, argv[i]);
    }

    int хы = 53;
    printf("%d", MUL(1 + 2, 3 + 4));
    printf("%d", (1 + 2) * (3 + 4));
    printf("%d", хы);
    double result = 0.0;
    
    switch (avg(5, NULL, 1, 2, 3, 7, 13))
    {
    case 0:
        printf("%.6lf", result);
        break;
    case 1:
        printf("Puk-puk, values count can't be EQ to 0!");
        break;
    case 2:
        printf("Puk-srenjk, can't store result!");
        break;
    }

	return 0;
}

int avg(
    size_t values_count,
    double* target,
    ...)
{
    if (values_count == 0)
    {
        return 1;
    }

    if (target == NULL)
    {
        return 2;
    }

    int result = 0, i;
    va_list args;
    va_start(args, target); // args = &values_count + 0
    for (i = 0; i < values_count; ++i)
    {
        result += va_arg(args, int);
    }

    *target = (double)result / values_count;
    return 0;
}

#endif