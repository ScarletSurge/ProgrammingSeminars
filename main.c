#include <stdio.h>

enum factorial_status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter
};

enum factorial_status_codes factorial(
        unsigned int value,
        unsigned long *result)
{
    enum factorial_status_codes recursive_status_code;

    if (value > 20)
    {
        return fsc_invalid_parameter;
    }

    if (value == 0 || value == 1)
    {
        *result = 1;
        return fsc_ok;
    }

    recursive_status_code = factorial(value - 1, result);
    if (recursive_status_code == fsc_ok)
    {
        *result *= value;
    }

    return recursive_status_code;
}

#include <stdlib.h>
#include <stdarg.h>

double average(int count, ...);

double average(int count, ...) {
    int i;
    double summ = 0;
    va_list ptr;
    va_start(ptr, count);

    for (i = 0; i < count; ++i)
    {
        //ptr += sizeof((l))
        summ += va_arg(ptr, double);
    }

    return summ / count;
};

int main()
{
    average(5, (double)1, (double)2, (double)3, (double)4, (double)10);
    printf("%lf", average(5, (double)1, (double)2, (double)3, (double)4));

    return 0;
}
