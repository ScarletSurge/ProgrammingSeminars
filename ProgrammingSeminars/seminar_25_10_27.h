#ifndef SEMINAR_27_10_25
#define SEMINAR_27_10_25

#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

//TODO: make this at home
int init_string_at_heap(
    char** to_init,
    char const* source)
{


    return -1;
}

struct puk_srenjk
{
    char c1;
    char c2;
};

typedef struct student
{
    char* surname;
    char* name;
    char* patronymic;
    size_t age;
    char sex;
    char* group_name;
} student, stud, *p_student;

void tuned_free_all(
    void** to_free,
    ...);

void free_student(
    p_student stud_ptr)
{
    tuned_free_all((void**)&stud_ptr->surname, &stud_ptr->name, &stud_ptr->patronymic, &stud_ptr->group_name, NULL);
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
    void* from_va;

    while ((from_va = va_arg(va, void*)) != NULL)
    {
        free(from_va);
    }
}

void tuned_free_all(
    void** to_free,
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

int seminar_25_10_27(
    int argc,
    char* argv[])
{
    sizeof(52 + 7); // expression-or-type

    float f = -12397.0975008;
    float* fptr = &f;

    int* iptr = (int*)&f;
    iptr = (int*)&f;

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

    stud_instance.surname = (char*)malloc(sizeof(char) * (strlen("Sadykov") + 1));
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

    return 0;
}

#endif