#include <stdio.h>
#include <math.h>
#include <string.h>

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

int main(
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

    const double epsilon = 1e-7;
    double a = 2, b = sqrt(2) * sqrt(2);

    // WRONG
    // printf("%s", a == b ? "Equals" : "Not equals");

    // CORRECT
    printf("Result: %s", fabs(a - b) < epsilon ? "Equals" : "Not equals");

    return 0;
}