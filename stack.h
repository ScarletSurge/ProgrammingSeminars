#ifndef INTERPRETERS_STACK_H
#define INTERPRETERS_STACK_H

#include <corecrt.h>

typedef struct variable_info
{
    char *name;
    int value;
} variable_info;

typedef struct code_block_variable_info
{
    variable_info info;
    size_t depth;
} code_block_variable_info;

typedef struct stack_item
{
    code_block_variable_info data;
    struct stack_item *next;
} stack_item;

typedef struct stack
{
    stack_item *top;
} stack;

int init_stack(
    stack *to_initialize);

int destroy_stack(
    stack *to_destroy);

int push_into_stack(
    stack *to_push_into,
    code_block_variable_info const *data);

int pop_from_stack(
    stack *to_pop_from,
    code_block_variable_info *data);

int peek_stack(
    stack const *to_peek,
    code_block_variable_info *data);

#endif //INTERPRETERS_STACK_H