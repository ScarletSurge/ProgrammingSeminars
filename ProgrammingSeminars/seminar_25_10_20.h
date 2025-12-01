#ifndef SEMINAR_25_10_20
#define SEMINAR_25_10_20

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char* bad_concat(
    size_t count,
    ...)
{
    char* result, * for_realloc;
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
        char const* str = va_arg(args, char const*);
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

int seminar_25_10_20(
    int argc,
    char* argv[])
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

    return 0;
}

#endif