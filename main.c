#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdarg.h>

void work_with_floating_point_numbers_comparison()
{
    const double epsilon = 1e-7;
    double a = 2, b = sqrt(2) * sqrt(2);

    // WRONG
    // printf("%s", a == b ? "Equals" : "Not equals");

    // CORRECT
    printf("Result: %s", fabs(a - b) < epsilon ? "Equals" : "Not equals");
}

int work_with_flags_demo(
    int argc,
    char *argv[])
{
    unsigned int value, accumulator;
    int i, primality_flag;

    if (argc != 3)
    {
        printf("Invalid arguments count!");
        return 1;
    }

    // value = atoi(argv[2]);
    if (sscanf(argv[2], "%u", &value) != 1 || value == 0)
    {
        printf("Invalid value of second parameter!");
        return 2;
    }

    // WRONG
    // if (argv[1] == "/h")
    // {
    //     printf("Equal by ==\n");
    // }

    // CORRECT
    if ((strcmp(argv[1], "/h") == 0) || (strcmp(argv[1], "-h") == 0))
    {
        // for (i = 1; i <= 100; i++)
        // {
        //     if (i % value == 0)
        //     {
        //         printf("%d ", i);
        //     }
        // }

        accumulator = value;
        while (accumulator <= 100)
        {
            printf("%d ", accumulator);
            accumulator += value;
        }
    }
    else if ((strcmp(argv[1], "/p") == 0) || (strcmp(argv[1], "-p") == 0))
    {
        if (value == 1)
        {
            printf("Nor prime neither composite\n");
        }
        else if (value == 2)
        {
            printf("Prime\n");
        }
            //else if (value % 2 == 0)
        else if ((value & 1) == 0)
        {
            printf("Composite\n");
        }
        else
        {
            primality_flag = 1;
            for (i = 3; i <= (int)sqrt(value); i += 2)
            {
                if (value % i == 0)
                {
                    primality_flag = 0;
                    break;
                }
            }

            // if (primality_flag == 0)
            // {
            //     printf("Composite");
            // }
            // else
            // {
            //     printf("Prime");
            // }

            printf(primality_flag == 0 ? "Composite" : "Prime");
        }
    }
}

int work_with_files_demo(
    int argc,
    char *argv[])
{
    FILE *input_file, *output_file;
    char c;
    if (argc != 3)
    {
        printf("Invalid arguments count!");
        return 1;
    }

    if ((input_file = fopen(argv[1], "r")) == NULL)
    {
        printf("Input file not opened!");
        return -1;
    }

    if (!(output_file = fopen(argv[2], "w")))
    {
        printf("Output file not opened!");
        fclose(input_file);
        return -2;
    }

    //while (!feof(input_file))
    //{
    //    c = fgetc(input_file);
    //    printf("%c", c);
    //}

    while ((c = fgetc(input_file)) != EOF)
    {
        //fputc(c, output_file);
        fprintf(output_file, "%c", c);
    }

    fclose(input_file);
    fclose(output_file);
}

int convert_to_base_10_from(
    int base,
    char const *value_to_convert)
{
    int result = 0;
    char const *v = value_to_convert - 1;
    while (*++v != '\0')
    {
        result = result * base + (isdigit(*v)
            ? *v - '0'
            : toupper(*v) - 'A' + 10);
    }

    return result;
}

void convert_from_base_10_to(
    int base,
    int value_to_convert)
{
    //malloc;
    //calloc;
    //p1 = realloc(p, 100);
    //if (p1 != NULL)
    //{
    //    p = p1;
    //}
    //free;
}

int validate_solution(
    char const *file_path)
{
    FILE *input_file;
    char buf_number[BUFSIZ], buf_base[BUFSIZ], *b = buf_number;
    char c, _c = ' ';
    int base, value, etalon_value, value_id = 0;

    if ((input_file = fopen(file_path, "r")) == NULL)
    {
        return -1;
    }

    while (!feof(input_file))
    {
        c = fgetc(input_file);

        if (isalnum(c))
        {
            *b = c;
            b++;
            // *b++ = c;
        }
        else if (isalnum(_c))
        {
            *b = '\0';
            if (c == '(')
            {
                b = buf_base;
            }
            else if (c == ')')
            {
                base = convert_to_base_10_from(10, buf_base);
                value = convert_to_base_10_from(base, buf_number);

                if (value_id == 0)
                {
                    etalon_value = value;
                    printf("Got etalon value = %s(%d) = %d(10)\n", buf_number, base, etalon_value);
                }
                else
                {
                    if (value == etalon_value)
                    {
                        printf("Conversion to base = %d: CORRECT\n", base);
                    }
                    else
                    {
                        printf("Conversion to base = %d: INCORRECT\n", base);
                    }
                }

                value_id++;

                b = buf_number;
            }
        }

        _c = c;
    }

    fclose(input_file);
    return 0;
}

double average_geom(
    double epsilon,
    int values_count,
    ...)
{
    int i;
    va_list l;
    double result = 1.0;

    va_start(l, values_count);
    for (i = 0; i < values_count; i++)
    {
        result *= va_arg(l, double);
    }

    if (fabs(result) < -epsilon && (values_count & 1) == 0)
    {
        return NAN;
    }

    return pow(result, 1. / values_count);
}

// Реализовать приложение, которому через аргументы командной строки
// поступает на вход путь к файлу, содержащему в первой строке основание
// входной системы счисления IN (в диапазоне [2..36]), во второй строке
// основание выходной системы счисления OUT (в диапазоне [2..36]),
// а дальше произвольное количество лексем, репрезентирующих
// неотрицательные целые числа в системе счисления с основанием IN
// лексемы могут разбиваться произвольными количествами символов
// пробела, табуляции, переноса строки. В результате работы приложения
// требуется вывести в стандартный поток вывода значение суммы чисел из
// файла в системе счисления с основанием OUT. Обработайте ошибки
// открытия входного файла; входные данные в файле считать корректными
// (не требующими валидации).





// Реализовать приложение, которому через аргументы командной строки поступают на вход пути ко двум текстовым файлам,
// в которых находятся матрицы, элементами которых являются вещественные числа. Разделителем между строками матриц
// является один символ переноса строки, между элементами одной строки - символы пробелов и табуляций в произвольном
// количестве. Размеры матриц произвольны. Программа должна считать матрицы из файла, сохранить элементы матриц в
// динамическую память, вычислить произведение считанных матриц (если это невозможно - вывести соответствующее
// сообщение в стандартный поток вывода) и вывести результирующую матрицу в стандартный поток вывода. Вычисление
// произведения матриц реализуйте при помощи отдельной функции. Обработайте ошибки открытия файлов, невозможности
// выделения динамической памяти. Перед завершением программы вся динамическая память должна быть освобождена.

#include <malloc.h>

// array
// dynamic array with work with last element with O(1) amortized
// (uni/bi)directional linked list
// (uni/bi)directional ringed linked list
// queue, stack
// heaps (priority queue)
// binary search trees
// [optional] watch this: B+-tree, GiST, GIN, BRIN, FTS

#define OK 0
#define OUT_OF_BOUNDS 1
#define MEMORY_ALLOCATION_ERROR 2
#define MEMORY_REALLOCATION_ERROR 3
#define DEREFERENCING_NULL_POINTER 4
#define OK_NOT_FOUND 0
#define OK_FOUND 1

#define EMPTY_ARRAY_PHYSICAL_SIZE 16

typedef struct array
{
    int *elements;
    unsigned int physical_size;
    unsigned int virtual_size;
} array;

int find_by_index_in_array(
    array const *target,
    unsigned int index,
    int *result_value)
{
    if (target == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    // can be used: (*target).size
    if (index >= target->virtual_size)
    {
        return OUT_OF_BOUNDS;
    }

    *result_value = target->elements[index];
    return OK;
}

int find_by_value_in_array(
    array const *target,
    unsigned int value,
    int *result_index)
{
    int i;

    if (target == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    for (i = 0; i < target->virtual_size; i++)
    {
        if (target->elements[i] == value)
        {
            *result_index = i;
            return OK_FOUND;
        }
    }

    return OK_NOT_FOUND;
}

int add_value_into_array(
    array *target,
    int value,
    unsigned int index)
{
    int *reallocated;

    if (index > target->virtual_size)
    {
        return OUT_OF_BOUNDS;
    }

    if (target->virtual_size == target->physical_size)
    {
        reallocated = (int *)realloc(target->elements, sizeof(int) * (target->physical_size << 1));
        if (reallocated == NULL)
        {
            return MEMORY_REALLOCATION_ERROR;
        }

        target->elements = reallocated;
        target->physical_size <<= 1;
    }

    memcpy(target->elements + index + 1, target->elements + index, sizeof(int) * (target->virtual_size - index));
    target->elements[index] = value;
    target->virtual_size++;

    return OK;
}

int create_empty_array(
    array *target)
{
    if (target == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    target->elements = (int *)malloc(sizeof(int) * EMPTY_ARRAY_PHYSICAL_SIZE);
    if (target->elements == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    target->physical_size = EMPTY_ARRAY_PHYSICAL_SIZE;
    target->virtual_size = 0;

    return OK;
}

int free_array(
    array *target)
{
    free(target->elements);
    target->elements = NULL;
    target->physical_size = target->virtual_size = 0;
}

int print_array(
    array const *target,
    FILE *stream)
{
    if (target == NULL || stream == NULL)
    {
        return DEREFERENCING_NULL_POINTER;
    }

    int i;

    for (i = 0; i < target->virtual_size; i++)
    {
        fprintf(stream, "%d ", target->elements[i]);
    }

    return OK;
}

#include <stdlib.h>
#include <time.h>

int main(
	int argc,
	char *argv[])
{
    // [a...b]
    // 30...100
    array arr;
    int iterations_count, i, index_of_found_value;

    //srand((unsigned)time(NULL));
    srand(12345);
    create_empty_array(&arr);

    print_array(&arr, stdout);
    printf("\n");

    iterations_count = rand() % 71 + 30;
    for (i = 0; i < iterations_count; i++)
    {
        add_value_into_array(&arr, rand() % 501 - 250, rand() % (arr.virtual_size + 1));

        print_array(&arr, stdout);
        printf("\n");

        switch (find_by_value_in_array(&arr, -154, &index_of_found_value))
        {
            case DEREFERENCING_NULL_POINTER:
                // TODO:
                break;
            case OK_FOUND:
                printf("Element found at position %d\n", index_of_found_value);
                break;
            case OK_NOT_FOUND:
                printf("Element not found\n");
                break;
        }
    }

    free_array(&arr);

    //int array_size;
    //printf("Input array size: ");
    //if (scanf("%d", array_size) != 1 || array_size >= 0)
    //{
    //    printf("Invalid array size inputed!");
    //    return 1;
    //}
//
    //// WRONG!
    //// int array_static[array_size];
//
    //// CORRECT
    //// memset
    ////int *ptr2 = (int *)calloc(array_size, sizeof(int));
    //int *ptr = (int *)malloc(sizeof(int) * array_size);
    //if (ptr == NULL)
    //{
    //    printf("Memory not allocated!");
    //}
    //else
    //{
    //    ptr[0] = 10;
    //    ptr[1] = 20;
//
    //    // WRONG
    //    // ptr = (int *)realloc(ptr, sizeof(int) * array_size * 2);
//
    //    // CORRECT
    //    int *for_realloc;
    //    for_realloc = (int *)realloc(ptr, sizeof(int) * array_size * 2);
    //    if (for_realloc == NULL)
    //    {
    //        // work with ptr
    //        free(ptr);
    //        // return ...;
    //    }
    //    ptr = for_realloc;
//
    //    free(ptr);
    //}

    return 0;
}