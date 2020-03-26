#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>

#include "dyn_arr.h"

typedef enum {
    FROZEN = 0x1
} arena_elem_flags_t;

typedef struct arena_boundary_t_{
    arena_elem_flags_t flags;
    struct arena_boundary_t_* next;
} arena_boundary_t; 

typedef struct {
    uint32_t cap;
    arena_boundary_t* arr;
} region_t;

typedef struct {
    arena_boundary_t* top;
    dyn_arr_t* regions; 
} arena_t;

region_t* init_region(size_t cap);
void free_region(region_t* region);

arena_t* init_arena(size_t cap);
void free_arena(arena_t* arena);

void* arena_prealloc(arena_t* arena);

void arena_set_cached(arena_t* arena, void* prealloc, void* alloc);

void* arena_malloc(arena_t* arena, size_t bytes);

void arena_reset_sp(arena_t* arena, void* prealloc);

#endif

