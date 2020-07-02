#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <inttypes.h>

typedef struct {
    uint32_t cap;
    uint32_t len;
    void** arr;
} dyn_arr_t;

dyn_arr_t* init_dyn_arr(uint32_t cap);
void free_dyn_arr(dyn_arr_t* list);
void append_dyn_arr(dyn_arr_t* list, void* element);
void* pop_dyn_arr(dyn_arr_t* list);
void* get_dyn_arr(dyn_arr_t* list, uint32_t index);

#endif

