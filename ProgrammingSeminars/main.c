#pragma warning(disable: 4996)

#include <stdio.h>
#include <math.h>

void letuchka220925()
{
    int value1, value2, value3;
    printf("Input 3 integral values: ");
    if (scanf("%d%d%d", &value1, &value2, &value3) != 3)
    {
        // TODO: validation
    }

    // a)
    if (value1 == value2 + value3 ||
        value2 == value3 + value1 ||
        value3 == value1 + value2)
    {
        // TODO: for product, You can do the same with operator*
    }

    // b)
    if (value1 > 0 && value2 > 0 && value3 > 0 &&
        value1 + value2 > value3 &&
        value1 - value2 < value3 &&
        value2 - value1 < value3 &&
        value3 + value2 > value1 &&
        value3 - value2 < value1 &&
        value2 - value3 < value1 &&
        value1 + value3 > value2 &&
        value1 - value3 < value2 &&
        value3 - value1 < value2)
    {
        // TODO
    }

    // в) 
    // 8192 == 2^13
    // 00100000 00000000
    //                 1
    // 00011111 11111111
    int n = value1 + value2 + value3;
    int is_power_of_two = (n & (n - 1)) == 0 && n > 0;
    printf("Is power of 2: %d", is_power_of_two);

    // 2^0 == 2^1 - 1
    // 2^0 + 2^1 == 2^2 - 1
    // 2^0 + 2^1 + 2^2 == 2^3 - 1
    // 2^13 - 1 = 

}

int main(void)
{
    // code from 08.09.25
    // variables & types
    int summand1, summand2; // integral
    int X = 138;
    // int, char, short, long, long long
    // unsigned --//--
    // void
    // float, double

    // printf("Hello World");

    // float f = -123.45;
    // printf("%08X", *((unsigned int*)&f));
    // \n \t \v \r \f '\\'
    //printf("%u %i %c %s %f %lf %o %x %X", X, X, X, "this is string o_O",
    //    123.45, 197776.52, 64, X, X);
    //printf("puk %d srenjk", X);

    // code from 15.09.25
    // ASCII:
    // code 32 - ' '
    // code 26 - EOF
    // code 48 - '0'
    // code 65 - 'A'
    // code 97 - 'a'
    //char var = 32;
    //double x = 0.1;
    //double y = 0.2;
    //printf("sum of %lf and %lf == %lf\n", x, y, //pow(sqrt(x + y), 2.0));
    //printf("%p", 123);

    // 0111 1011
    // 80 - 1 - 4 = 7F - 4 = 7B

    // %d, %i - int as decimal
    // %c - char
    // %u - unsigned int
    // %s - char *
    // %f - float
    // %lf - double
    // %o - int as octal
    // %x, %X - int as hexadecimal
    // %p - pointer

    // obsolete/deprecated

    unsigned int value1 = 0, value2, value3;
    int i;

    printf("Enter 3 decimal values: ");
    scanf("%u%u%u", &value1, &value2, &value3);
    printf("value1 == %u, value2 == %u, value3 == %u", value1, value2, value3);

    if (value1 == 30)
    {
        printf("worked!\n");
    }
    if (value1 == 45)
    {
        printf(":(\n");
    }
    else if (value2 == 52)
    {
        printf("OMG LOL");
    }
    else
    {
        printf("Nothing happpened((9(9");
    }
    // TODO: switch/case/default

    for (i = 1; i <= 10; ++i)
    {
        printf("%d ", i);
    }

    // TODO: while, do/while

    // 22.09.2025
    //for (/*initialization block*/;/*conditional expression checking block*/;/*modification block*/)

    int maybe_prime;
    printf("input value: ");
    if (scanf("%d", &maybe_prime) != 1 || maybe_prime <= 0)
    {
        printf("incorrerct input!\n");
    }
    else {
        if (maybe_prime == 1)
        {
            printf("input num is not prime nor composite\n");
        }
        else {
            int i, is_prime = 1;
            for (i = 2;i * i <= maybe_prime;i += 1) 
            {
                if (maybe_prime % i == 0)
                {
                    is_prime = 0;
                    break;

                }
                
            }
            if (is_prime == 0)
                printf("is composite\n");
            else printf("is prime!\n");

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