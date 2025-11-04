#ifndef SEMINAR_25_10_06
#define SEMINAR_25_10_06

#pragma warning(disable: 4996)

#include <stdio.h>
#include <limits.h>

int seminar_25_10_06(
	int argc,
	char* argv[])
{
    FILE *input_file; // FILE is typedef for struct _iobuf
    // variable of type `FILE *` is called file variable

    // postfix notation: 1 2 + 
    // (123 + 7) * (9 - (1 - 2)) / (5 - 5)
    // const int const * const * const* const** const;

    char const *file_path = "C:\\Users\\scarl\\Desktop\\pukipuki.txt";
    input_file = fopen(file_path, "r");
    if (input_file == NULL)
    {
        // File not opened!
        // TODO: handle fopen retval
        return -1;
    }

    // loop of reading file with EOF handling
    while (!feof(input_file))
    {
        // read character from file stream,
        char readChar = fgetc(input_file);
        
        // then handle it
        putc(readChar, stdout);
        // printf("%c", readChar);
    }
    
    // open file variable with opening validation
    // if (!(input_file = fopen("path", "mode"))) { // File not opened! }
    
    // TODO: read about this functions
    // fgetc, fscanf, fprintf, fputs
    // fread, fwrite, open, close
    // rewind

    // close previously
    fclose(input_file);

    input_file = fopen(file_path, "r");
    if (input_file == NULL)
    {
        return -2;
    }

    // loop of reading file without EOF handling
    char c;
    while ((c = fgetc(input_file)) != EOF)
    {
        // TODO: handle read character
    }

    fclose(input_file);

	return 0;
}

#endif