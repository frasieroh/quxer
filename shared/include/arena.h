#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>

#include "dyn_arr.h"

typedef enum {
    FROZEN = 0x1,
} arena_elem_flags_t;

typedef struct alloc_boundary_t_{
    arena_elem_flags_t flags;
    struct alloc_boundary_t_* next;
} alloc_boundary_t; 

typedef struct {
    uint32_t cap;
    alloc_boundary_t* arr;
} region_t;

typedef struct {
    alloc_boundary_t* small;
    alloc_boundary_t* med;
    alloc_boundary_t* large;
    alloc_boundary_t* huge;
    alloc_boundary_t* dynamic;
} arena_ptrs_t;

typedef struct {
    uint32_t small;
    uint32_t med;
    uint32_t large;
    uint32_t huge;
} arena_thsholds_t;

typedef struct {
    dyn_arr_t* small;
    dyn_arr_t* med;
    dyn_arr_t* large;
    dyn_arr_t* huge;
    dyn_arr_t* dynamic;
} arena_regions_t;

typedef struct {
    arena_ptrs_t ptrs;
    arena_thsholds_t thsholds;
    arena_regions_t regions;
} arena_t;

region_t* init_region(size_t cap);
void free_region(region_t* region);

arena_t* init_arena(size_t cap);
void free_arena(arena_t* arena);

arena_ptrs_t* arena_prealloc(arena_t* arena, arena_ptrs_t* ret);

void arena_set_cached(arena_t* arena, arena_ptrs_t* prealloc);

void* arena_malloc(arena_t* arena, size_t bytes);

void arena_reset_sp(arena_t* arena, arena_ptrs_t* prealloc);

#endif

