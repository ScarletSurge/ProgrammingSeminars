#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

#define SIZE 26

typedef struct array_descriptor
{
    int *elements;
    size_t elements_count;
} array_descriptor;

int initialize_variable(
    array_descriptor *variable)
{
    variable->elements_count = 0;
    if ((variable->elements = (int *)malloc(sizeof(int) * 0)) == NULL)
    {
        return 1;
    }

    return 0;
}

void destroy_variable(
    array_descriptor *variable)
{
    free(variable->elements);
}

int main(
    int argc,
    char *argv[])
{
    int i;
    char c, c_;
    array_descriptor variables[SIZE];
    FILE *input_file;

    if (argc != 2)
    {
        printf("Input file path not passed!");
        return -1;
    }

    for (i = 0; i < SIZE; i++)
    {
        //initialize_variable(&variables[i])
        switch (initialize_variable(variables + i))
        {
            case 0:
                // TODO:
                break;
            case 1:
                // TODO:
                break;
        }
    }

    if (!(input_file = fopen(argv[1], "r")))
    {
        printf("Input file can't be opened!");

        for (i = 0; i < SIZE; i++)
        {
            destroy_variable(variables + i);
        }

        return -2;
    }

    while (!feof(input_file))
    {
        fgetc(input_file);
    }

    fclose(input_file);
    for (i = 0; i < SIZE; i++)
    {
        destroy_variable(variables + i);
    }

    return 0;
}