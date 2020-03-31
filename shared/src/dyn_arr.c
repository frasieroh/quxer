#ifndef DYN_ARR_C
#define DYN_ARR_C

#include <stdlib.h>

#include "dyn_arr.h"

dyn_arr_t* init_dyn_arr(uint32_t cap)
{
    dyn_arr_t* list = malloc(sizeof(dyn_arr_t));
    list->arr = malloc(sizeof(void*) * cap);
    list->cap = cap;
    list->len = 0;
    return list;
}

void free_dyn_arr(dyn_arr_t* list)
{
    free(list->arr);
    free(list);
    return;
}

void append_dyn_arr(dyn_arr_t* list, void* element)
{
    if (list->len >= list->cap) {
        list->cap *= 2;
        list->arr = realloc(list->arr, sizeof(void*) * list->cap);
    }
    list->arr[list->len++] = element;
    return;
}

void* pop_dyn_arr(dyn_arr_t* list)
{
    return list->arr[--(list->len)];
}

void* get_dyn_arr(dyn_arr_t* list, uint32_t index)
{
    return list->arr[index];
}

#endif

