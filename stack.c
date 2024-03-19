#include "stack.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

int init_stack(
    stack *to_initialize)
{
    if (to_initialize == NULL)
    {
        return 1;
    }

    to_initialize->top = NULL;

    return 0;
}

int destroy_stack(
    stack *to_destroy)
{
    stack_item *iterator;

    if (to_destroy == NULL)
    {
        return 1;
    }

    iterator = to_destroy->top;

    while (iterator != NULL)
    {
        free(iterator->data.info.name);
        iterator = iterator->next;
    }

    return 0;
}

int push_into_stack(
    stack *to_push_into,
    code_block_variable_info const *data)
{
    stack_item *item_to_push;

    if (to_push_into == NULL)
    {
        return 1;
    }

    else if (data == NULL)
    {
        return 2;
    }

    if ((item_to_push = (stack_item *)malloc(sizeof(stack_item))) == NULL)
    {
        return 3;
    }

    // TODO: move to other function
    memcpy(&(item_to_push->data), data, sizeof(code_block_variable_info));
    // TODO: validate strdup
    item_to_push->data.info.name = strdup(item_to_push->data.info.name);

    item_to_push->next = to_push_into->top;
    to_push_into->top = item_to_push;

    return 0;
}

int pop_from_stack(
    stack *to_pop_from,
    code_block_variable_info *data)
{
    stack_item *to_pop;

    if (to_pop_from == NULL)
    {
        return 1;
    }

    if (data == NULL)
    {
        return 2;
    }

    if (to_pop_from->top == NULL)
    {
        return 3;
    }

    memcpy(&(to_pop_from->top->data), data, sizeof(code_block_variable_info));

    to_pop = to_pop_from->top;
    to_pop_from->top = to_pop->next;
    free(to_pop);

    return 0;
}

int peek_stack(
    stack const *to_peek,
    code_block_variable_info *data)
{
    stack_item *to_pop;

    if (to_peek == NULL)
    {
        return 1;
    }

    if (data == NULL)
    {
        return 2;
    }

    if (to_peek->top == NULL)
    {
        return 3;
    }

    memcpy(data, &(to_peek->top->data), sizeof(code_block_variable_info));
    // TODO: validate strdup
    data->info.name = strdup(data->info.name);

    return 0;
}