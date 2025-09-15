#pragma warning(disable: 4996)

#include <stdio.h>
#include <math.h>

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

    return 0;
}