#pragma warning(disable: 4996)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <stdarg.h>
#include <string.h>

#define MACRO_KEY хы
#define MUL(x, y) ((x) *\
 (y))

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

/*На языке программирования C (стандарт C99 и выше) реализовать приложение, заполняющее массив размера 512 целыми псевдослучайными числами из диапазона [-500..500], причём события выпадения каждого отдельного значения из диапазона равновероятны. Необходимо вывести сгенерированный массив в стандартный поток вывода, а далее вычислить среднее арифметическое (типа double) элементов массива, используя указатель для прохода по элементам массива. Значение среднего арифметического необходимо вывести в стандартный поток вывода с точностью 6 знаков после десятичной точки.*/
int letuchka061025()
{
    int values[512], i;
    int* p_value = values;
    double average = 0.0;
    // rand() % (b - a + 1) + a
    // rand() % 7 - 0, 1, 2, 3, 4, 5, 6
    // [a..b] -> [0...b-a] + a

    srand((unsigned int)time(NULL));
    for (i = 0; i < 512; ++i)
    {
        values[i] = rand() % 1001 - 500;
        printf("%d ", values[i] /*use assignment operator*/);
    }

    for (i = 0; i < 512; ++i)
    {
        average += *p_value;
        p_value++;
    }

    printf("%.6lf", average /= 512);

    return 0;
}

/*
 * На языке программирования C реализовать приложение, открывающее текстовый файл с именем "inputFile.txt" уровня директории exe-файла, связанного с приложением. Из открытого файла необходимо выделить все непустые подстроки, являющиеся корректным представлением целого неотрицательного числа в системе счисления с основанием 16; разделителем между такими подстроками являются символы пробела, табуляции и переноса строки. Выделенные подстроки представлений и эквивалентные им значения чисел в системе счисления с основанием 10 необходимо построчно записать в текстовый файл с именем "outputFile.txt" уровня директории exe-файла, связанного с приложением.
*/
int letuchka131025(
    int argc,
    char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid command arguments count!");
        return -3;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile)
    {
        // TODO: handle file opening error
        printf("Input file not exists!");
        return -1;
    }

    FILE* outputFile = fopen(argv[2], "w");
    if (!outputFile)
    {
        printf("Output file can't be created!");
        fclose(inputFile);
        return -2;
    }

    char buf[BUFSIZ], *b = buf, c, c_ = ' ';
    int convertedValue;

    while (!feof(inputFile))
    {
        c = toupper(fgetc(inputFile));

        if (!(c == ' ' || c == '\t' || c == '\n' || c == EOF))
        {
            // x = ++*b, *++b, x = *b++, x = (*b)++
            *b = c;
            b++;
        }
        else if (b != buf) // lexem found!
        {
            *b = '\0'; // b - buf == strlen(buf)
            b = buf;
            convertedValue = 0;

            while (*b /*!= 0*/)
            {
                if (isdigit(*b) || (*b >= 'A' && *b <= 'F'))
                {
                    convertedValue = convertedValue * 16 + (isdigit(*b)
                        ? *b - '0' // *b - 48 - the same
                        : *b - 'A' + 10); // *b - 55
                }
                else
                {
                    break;
                }

                ++b;
            }

            if (!*b)
            {
                fprintf(outputFile, "%s(16) == %d(10)\n", buf, convertedValue);
            }

            b = buf;
        }

        c_ = c;
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

/*
 * На языке программирования C (стандарт C99 и выше) реализовать приложение, принимающее в качестве аргументов командной строки путь к текстовому файлу. Файловая переменная, полученная при открытии файла, должна быть передана в функцию, принимающую также переменное число аргументов (непустых строк). В файле необходимо найти вхождения всех строк из списка аргументов переменной длины в качестве подстрок, и напечатать в стандартный поток вывода номера символов из файла (начиная с 1) с указанием всех подстрок, начинающихся с данного символа.
 */
int letuchka201025(
    int argc,
    char* argv[])
{
    // TODO

    return 0;
}

int avg(
    size_t values_count,
    double *target,
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

char* bad_concat(
    size_t count,
    ...)
{
    char *result, *for_realloc;
    int result_length = 0;
    int i;
    va_list args;
    // #define va_start(ap, x) ((ap) = (va_list)(&(x) + 1))
    
    result = (char*)malloc(sizeof(char) * 1);
    if (result == NULL)
    {
        return NULL;
    }
    strcpy(result, ""); // *result = 0; - the same

    if (count == 0)
    {
        // return "";
        // return strdup("");
        return result;
    }

    va_start(args, count); // args = (va_list)(&count + 1);
    for (i = 0; i < count; ++i)
    {
        char *str = va_arg(args, char const*);
        size_t str_len = strlen(str);
        
        if ((for_realloc = (char*)realloc(result, sizeof(char) * (result_length + str_len + 1))) == NULL)
        {
            free(result);
            return NULL;
        }
        result = for_realloc;

        // strcat(result, str); // this is slow
        strcpy(result + result_length, str); // this is faster
        result_length += str_len;

        //printf("\tva_list[%d] == \"%s\"\n", i, va_arg(args, char const*));
    }
    va_end(args);

    return result;
}

int code_from_201025(
    int argc,
    char *argv[])
{
    char* concatenated_strings = bad_concat(0, "AbcdE", "BCdfhfdkdfjdfkdfD", "DFGHJKLKGFGHJKL:", "", "", "1234567890");
    switch ((size_t)concatenated_strings)
    {
        case 0:
            printf("Memory allocation error!!1!1");
            break;
        default:
            printf("concat result == \"%s\"\n", concatenated_strings);
            free(concatenated_strings);
            break;
    }
}

int main(
    int argc,
    char *argv[])
{
    //printf("%s", 1.85);
    // setlocale(LC_ALL, "Russian");
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

    /*int x = 5, y = 10;
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
    }*/

    // code from 06.10.25
    FILE *input_file; // FILE is typedef for struct _iobuf
    // variable of type `FILE *` is called file variable

    //1 2 + 
    // (123 + 7) * (9 - (1 - 2)) / (5 - 5)
    //const int const * const * const* const** const;

    char const * const filePath = "C:\\Users\\Ilya\\Desktop\\pukipuki.txt";
    /*input_file = fopen(filePath, "r");
    if (input_file == NULL)
    {
        // File not opened!
        // TODO: handle fopen retval
        return -1;
    }

    // loop of reading file with EOF handling
    while (!feof(input_file))
    {
        char readChar = fgetc(input_file);
        putc(readChar, stdout);
        //printf("%c", readChar);
    }
    // if (!(input_file = fopen("path", "mode"))) { // File not opened! }
    // fgetc, fscanf, fprintf, fputs
    // fread, fwrite, open, close
    // rewind
    fclose(input_file);
    input_file = fopen(filePath, "r");
    if (input_file == NULL)
    {
        return -2;
    }

    char c;
    while ((c = fgetc(input_file)) != EOF)
    {
        // TODO: handle read character
    }

    fclose(input_file);*/

    //int Arsenya = -2;
    //printf("%d\n", ++Arsenya);
    //printf("%d\n\n", Arsenya);
    //
    //int i;
    //for (i = 0; i < argc; ++i)
    //{
    //    printf("argv[%d] == \"%s\"\n", i, argv[i]);
    //}

    //letuchka131025(argc, argv);

    //int хы = 53;
    //printf("%d", MUL(1 + 2, 3 + 4));
    //printf("%d", (1 + 2) * (3 + 4));
    //printf("%d", хы);
    //double result = 0.0;
    //
    //switch (avg(5, NULL, 1, 2, 3, 7, 13))
    //{
    //case 0:
    //    printf("%.6lf", result);
    //    break;
    //case 1:
    //    printf("Puk-puk, values count can't be EQ to 0!");
    //    break;
    //case 2:
    //    printf("Puk-srenjk, can't store result!");
    //    break;
    //}

    return code_from_201025(argc, argv);

    return 0;
}