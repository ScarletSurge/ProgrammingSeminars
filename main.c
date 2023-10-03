#include <stdio.h>

int main(
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