/*#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "stack.h"

int main(
    int argc,
    char *argv[])
{
    int i, depth = 0, status_code;
    char c, pc = ' ', buf[BUFSIZ], *b = buf, *initialization_mark = NULL;
    FILE *input_file;
    stack variables_stack;
    code_block_variable_info variable_info;
    stack_item *iterator;

    if (argc == 1)
    {
        printf("No input files passed!");
        return -1;
    }

    for (i = 1; i < argc; i++)
    {
        init_stack(&variables_stack);

        if (!(input_file = fopen(argv[i], "r")))
        {
            printf("Input file \"%s\" can't be opened!", argv[i]);

            continue;
        }

        while (!feof(input_file))
        {
            c = fgetc(input_file);

            if (c == '{')
            {
                ++depth;
            }
            else if (isalnum(c) || c == '=')
            {
                *b++ = c;
                if (c == '=')
                {
                    initialization_mark = b - 1;
                }
            }
            else if (c == '}')
            {
                do
                {
                    // TODO: check status_code validity
                    status_code = peek_stack(&variables_stack, &variable_info);
                    if (status_code == 3)
                    {
                        break;
                    }

                    free(variable_info.info.name);
                    variable_info.info.name = NULL;
                    if (depth == variable_info.depth)
                    {
                        // TODO: check status_code validity
                        status_code = pop_from_stack(&variables_stack, &variable_info);
                        free(variable_info.info.name);
                        variable_info.info.name = NULL;
                    }
                }
                while (depth == variable_info.depth);

                --depth;
            }
            else if (c == ';')
            {
                *b = '\0'; // = 0
                b = buf;

                if (initialization_mark == NULL)
                {
                    // ShowVar instruction handling
                    iterator = variables_stack.top;
                    while (iterator != NULL)
                    {
                        printf("\tName: \"%s\", value: %d\n", iterator->data.info.name, iterator->data.info.value);

                        iterator = iterator->next;
                    }
                    printf("\n");
                }
                else
                {
                    *initialization_mark++ = '\0';
                    // buf - variable name
                    // initialization_mark - variable value
                    variable_info.depth = depth;
                    if (sscanf(initialization_mark, "%d", &(variable_info.info.value)) != 1)
                    {
                        // TODO: handle parsing error
                    }
                    variable_info.info.name = buf;

                    // TODO: check status_code validity
                    status_code = push_into_stack(&variables_stack, &variable_info);

                    initialization_mark = NULL;
                }
            }

            pc = c;
        }

        fclose(input_file);
        destroy_stack(&variables_stack);
    }

    return 0;
}*/

#include <iostream>

#include "trie.h"

void print_trie(
    trie const &t)
{
    for (auto const &str: t.obtain_all())
    {
        std::cout << '\"' << str << '\"' << std::endl;
    }
}

int main(
    int argc,
    char *argv[])
{
    trie t(std::set<char> { 'a', 'b', 'c', 'd', 'e' });
    //t.insert("");
    t.insert("aaa");
    t.insert("abc");
    t.insert("abcde");
    t.insert("bdec");
    t.insert("");
    t.insert("decd");

    trie t1 = t;

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;

    t1.dispose("abc");
    t1.dispose("decd");
    t1.dispose("");

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;

    t = std::move(t1);

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;

    trie t2 = std::move(t);

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;
    std::cout << "t2: " << std::endl; print_trie(t2); std::cout << std::endl;

    return 0;
}