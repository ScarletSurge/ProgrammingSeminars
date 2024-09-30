#ifndef PROGRAMMINGSEMINARS_UNIDIRECTIONAL_LIST_H
#define PROGRAMMINGSEMINARS_UNIDIRECTIONAL_LIST_H

#include <corecrt.h>

typedef int T;

typedef struct unidirectional_list_item
{
    T data;
    struct unidirectional_list_item *next;
} unidirectional_list_item, *p_unidirectional_list_item;

typedef struct unidirectional_list
{
    p_unidirectional_list_item first;
} unidirectional_list, *p_unidirectional_list;

int create_ul(
    p_unidirectional_list to_create);

int ul_get_values_count(
    unidirectional_list const *);

int ul_insert_value(
    p_unidirectional_list to_insert_into,
    T value,
    size_t target_position);

int ul_remove_value(
    p_unidirectional_list to_remove_from,
    size_t target_position,
    T *removed_value_box);

int ul_traverse_datas(
    p_unidirectional_list to_traverse,
    void (*callback)(T *value_to_traverse));

int ul_traverse_items(
    p_unidirectional_list to_traverse,
    void (*callback)(p_unidirectional_list_item *value_to_traverse));

int clear_ul(
    p_unidirectional_list to_clear);

#endif //PROGRAMMINGSEMINARS_UNIDIRECTIONAL_LIST_H
