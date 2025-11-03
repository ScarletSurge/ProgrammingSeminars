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
        char const *str = va_arg(args, char const*);
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

void tuned_free_all(
    void** to_free,
    ...);

typedef struct student
{
    char *surname;
    char *name;
    char *patronymic;
    size_t age;
    char sex;
    char *group_name;
} student, stud, *p_student;

void free_student(
    p_student stud_ptr)
{
    tuned_free_all((void **)&stud_ptr->surname, &stud_ptr->name, &stud_ptr->patronymic, &stud_ptr->group_name, NULL);
}

// typedef void* T;

void free_all(
    void* to_free,
    ...)
{
    if (to_free == NULL)
    {
        return;
    }

    free(to_free);

    va_list va;
    va_start(va, to_free);
    void *from_va;

    while ((from_va = va_arg(va, void*)) != NULL)
    {
        free(from_va);
    }
}

void tuned_free_all(
    void **to_free,
    ...)
{
    if (to_free == NULL)
    {
        return;
    }

    free(*to_free);
    *to_free = NULL;

    va_list va;
    va_start(va, to_free);
    void** from_va;

    while ((from_va = va_arg(va, void**)) != NULL)
    {
        free(*from_va);
        *from_va = NULL;
    }
}

int code_from_271025(
    int argc,
    char* argv[])
{
    sizeof(52+7); // expression-or-type

    float f = -12397.0975008;
    float *fptr = &f;
    
    int *iptr = (int *)&f;
    iptr = (int *)&f;

    printf("Bits as int: %d\n", *iptr);
    printf("Bits as float: %f\n\n", *fptr);

    // open file with existence check
    // FILE *f;
    // if (!(f = fopen(file_path, file_mode)))
    // {
    //     // TODO
    // }
    
    // file reading loop (with EOF handling)
    // char c;
    // while (!feof(f))
    // {
    //     c = fgetc(f);
    //     // TODO: handle read character/byte
    // }
    
    // file reading loop (without EOF handling)
    // char c;
    // while ((c = fgetc(f)) != EOF)
    // {
    //     // TODO: handle read character/byte
    // }

    // Gorner schema
    // char const *value = "12bC04", *v = value;
    //                      ^
    //                      |
    //                      v
    // size_t const base = 18;
    // int result = 0;
    // while (*v)
    // {
    //     result = result * base + (isdigit(*v)
    //       ? *v++ - '0'
    //       : toupper(*v++) - 'A' + 10);
    // }
    
    // Gorner inverted schema
    // int value = 1923876;
    // int const base = 16;
    // char buf[BUFSIZ], *b = buf + BUFSIZ - 1;
    // *b = 0;
    // if (value == 0) { *--b = '0'; }
    // // TODO: handle value sign
    // while (value)
    // {
    //     int const rem = value % base;
    //     *--b = rem < 10
    //       ? rem + '0'
    //       : rem + 'A' - 10;
    //     value /= base;
    // }

    student stud_instance;
    stud_instance.age = 17;

    stud_instance.surname = (char *)malloc(sizeof(char) * (strlen("Sadykov") + 1));
    if (stud_instance.surname == NULL)
    {
        return 1;
    }
    strcpy(stud_instance.surname, "Sadykov");

    stud_instance.name = (char*)malloc(sizeof(char) * (strlen("Timur") + 1));
    if (stud_instance.name == NULL)
    {
        free(stud_instance.surname);
        return 1;
    }
    strcpy(stud_instance.surname, "Timur");

    stud_instance.patronymic = (char*)malloc(sizeof(char) * (strlen("Eduardovich") + 1));
    if (stud_instance.patronymic == NULL)
    {
        // free(stud_instance.surname);
        // free(stud_instance.name);
        free_all(stud_instance.surname, stud_instance.name, NULL);
        return 1;
    }
    strcpy(stud_instance.surname, "Eduardovich");

    stud_instance.group_name = (char*)malloc(sizeof(char) * (strlen("ITPM-125") + 1));
    if (stud_instance.group_name == NULL)
    {
        // free(stud_instance.surname);
        // free(stud_instance.name);
        // free(stud_instance.patronymic);
        free_all(stud_instance.surname, stud_instance.name, stud_instance.patronymic, NULL);
        return 1;
    }
    strcpy(stud_instance.surname, "ITPM-125");

    stud_instance.sex = 52;

    printf("sizeof(puk_srenjk) == %u\n", sizeof(struct puk_srenjk));
    printf("sum of sizeofs of char and int == %u", sizeof(char) + sizeof(int));

    free_student(&stud_instance);

    // TODO: usage of initialized struct instance...

    // TODO: make this at home
    // int init_string_at_heap(
    //    char** to_init,
    //    char const* source);

    return 0;
}

int code_from_031125(
    int argc,
    char *argv[])
{


    return 0;
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

    //return code_from_271025(argc, argv);
    return code_from_031125(argc, argv);

    return 0;
}