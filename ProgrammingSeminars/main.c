#pragma warning(disable: 4996)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

/*На языке программирования C (стандарт C99 и выше) реализовать приложение, запрашивающее со стандартного потока ввода у пользователя три целых числа, и сообщающее пользователю при помощи печати в стандартный поток вывода: а) являются ли считанные числа таковыми, что любое из них является суммой двух остальных; произведением двух остальных; б) являются ли введённые числа длинами сторон треугольника; в) является ли сумма введённых чисел некоторой степенью двойки.*/
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

/*На языке программирования C (стандарт C99 и выше) реализовать приложение, запрашивающее у пользователя из стандартного потока ввода значения для переменных first_value и epsilon типа double; значение epsilon при этом должно быть строго положительным (после трёх неуспешных попыток ввода значения переменной epsilon необходимо завершить приложение аварийно). Далее, приложение запрашивает со стандартного потока ввода значение second_value до тех пор, пока значения переменных first_value и second_value не станут равны с точностью epsilon; по достижении вышеописанного условия приложение должно напечатать в стандартный поток вывода результат произведения значений first_value и second_value.*/
int letuchka290925()
{
    double difference;
    int attempts_counter = 0;
    double first_value, second_value;
    double epsilon = 0.0;
    // while (epsilon == 0.0) - ЭТО БАН!!1!1
    // while (epsilon != 0.0) - ЭТО БАН!!1!1

    // TODO: printf
    if (scanf("%lf", &first_value) != 1)
    {
        // TODO: validate
    }

    while (epsilon <= 0.0)
    {
        // TODO: printf
        if (scanf("%lf", &epsilon) != 1)
        {
            // TODO: validate
        }

        if (++attempts_counter == 3 && epsilon <= 0.0)
        {
            // exit(1); - ЭТО БАН
            return 1;
        }
    }

    do
    {
        // TODO: printf
        if (scanf("%lf", &second_value) != 1)
        {
            // TODO: validate
        }
    }
    while (fabsl(first_value - second_value) >= epsilon);

    printf("v1 * v2 == %lf", first_value * second_value);

    return 0;
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

    /*unsigned int value1 = 0, value2, value3;
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
    //for (initialization block;conditional expression checking block;modification block)

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
    }*/

    // code from 29.09.25
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