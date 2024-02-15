#include <stdio.h>

int main(
    int argc,
    char *argv[])
{
    FILE *input_file;
    int multiline_comment_nesting = 0;
    int oneline_comment_active = 0;
    char c;

    if (argc != 2)
    {
        printf("Invalid arguments count!");

        return -1;
    }

    if (!(input_file = fopen(argv[1], "r")))
    {
        printf("File not found!");
        return -2;
    }

    while (!feof(input_file))
    {
        c = fgetc(input_file);
        if (c == '[' && !oneline_comment_active)
        {
            ++multiline_comment_nesting;
        }
        else if (c == ']')
        {
            if (!multiline_comment_nesting)
            {
                fprintf(stderr, "Error: found multiline comment closing bracket while out of comment!");

                return 1;
            }

            --multiline_comment_nesting;
        }
        else if (c == '#' && !multiline_comment_nesting)
        {
            oneline_comment_active = 1;
        }
        else if (c == '\n' || c == '\r' || c == '\v' || c == EOF)
        {
            oneline_comment_active = 0;
            if (c != EOF && !multiline_comment_nesting)
            {
                fputc(c, stdout);
            }
        }
        else if (!multiline_comment_nesting && !oneline_comment_active)
        {
            fputc(c, stdout);
        }
    }

    if (multiline_comment_nesting)
    {
        fprintf(stderr, "Error: multiline comment not closed at the end of file!");

        return 2;
    }

    fclose(input_file);

    return 0;
}