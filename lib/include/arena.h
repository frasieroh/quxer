#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>

#include "dyn_arr.h"

typedef enum {
    FROZEN = 0x1,
} arena_elem_flags_t;

typedef struct fixed_boundary_t_ {
    arena_elem_flags_t flags;
    void* fixed;
    struct fixed_boundary_t_* next;
} fixed_boundary_t;

typedef struct alloc_boundary_t_{
    arena_elem_flags_t flags;
    struct alloc_boundary_t_* next;
} alloc_boundary_t; 

typedef struct {
    uint32_t cap;
    union {
        void* fixed;
        fixed_boundary_t* fixed_backing;
        alloc_boundary_t* dynamic;
    } data;
} region_t;

typedef struct {
    fixed_boundary_t* fixed;
    alloc_boundary_t* dynamic;
} arena_ptrs_t;

typedef struct {
    arena_ptrs_t ptrs;
    dyn_arr_t* fixed;
    dyn_arr_t* fixed_backing;
    dyn_arr_t* dynamic;
} arena_t;

arena_t* init_arena(size_t cap);
void free_arena(arena_t* arena);

arena_ptrs_t* arena_prealloc(arena_t* arena, arena_ptrs_t* ret);

void arena_set_cached(arena_t* arena, arena_ptrs_t* prealloc);

void* arena_malloc(arena_t* arena, size_t bytes);

void arena_reset_sp(arena_t* arena, arena_ptrs_t* prealloc);

#endif

