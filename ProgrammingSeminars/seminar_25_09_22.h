#ifndef SEMINAR_25_09_22
#define SEMINAR_25_09_22

#pragma warning(disable: 4996)

#include <stdio.h>

int seminar_25_09_22(
    int argc,
    char* argv[])
{
    // for (initialization block; conditional expression checking block; modification block)

    int maybe_prime;
    printf("input value: ");
    if (scanf("%d", &maybe_prime) != 1 || maybe_prime <= 0)
    {
        printf("incorrerct input!\n");
    }
    else
    {
        if (maybe_prime == 1)
        {
            printf("input num is not prime nor composite\n");
        }
        else
        {
            int i, is_prime = 1;
            for (i = 2; i * i <= maybe_prime; i += 1)
            {
                if (maybe_prime % i == 0)
                {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime == 0)
            {
                printf("is composite\n");
            }
            else
            {
                printf("is prime!\n");
            }

            // TODO: read about ?: operator
            //printf("is %s", is_prime == 0
            //    ? "composite"
            //    : "prime!");
        }

        while (1)
        {
            int value_45;
            printf("input value: ");
            if (scanf("%d", &value_45) != 1 || value_45 <= 0)
            {
                printf("invalid input!!!\n");
                continue;
            }

            if (value_45 == 1)
            {
                printf("inputed value is not prime\n");
                continue;
            }
            else {
                int i, is_prime = 1;
                for (i = 2; i * i <= value_45;i += 1)
                {
                    if (value_45 % i == 0)
                    {
                        is_prime = 0;
                        break;
                    }

                }
                if (is_prime == 1)
                {
                    break;
                }

                printf("inputed value is not prime\n");
            }
        }
    }

    return 0;
}

#endif