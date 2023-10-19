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

double average_geom2(
    double epsilon,
    ...)
{
    int i;
    va_list l;
    double actual_
    double result = 1.0;

    va_start(l, epsilon);
    while (1)
    {
        result *= va_arg(l, double);
    }

    if (fabs(result) < -epsilon && (values_count & 1) == 0)
    {
        return NAN;
    }

    return pow(result, 1. / values_count);
}

int main(
	int argc,
	char *argv[])
{
    // switch (validate_solution("task.txt"))
    // {
    //     case -1:
    //         printf("Input file can't be opened!");
    //         break;
    //     case 0:
    //         printf("Task finished.");
    //         break;
    // }

    return 0;
}