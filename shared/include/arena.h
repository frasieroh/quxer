#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>

#include "dyn_arr.h"

typedef enum {
    IS_VALID = 0x1,
    IS_CACHED = 0x2,
    IS_IN_PROGRESS = 0x4 // to detect left recursion
} arena_elem_flags_t;

typedef struct {
    uint32_t offset;
    uint32_t region;
} arena_idx_t;

typedef struct {
    arena_idx_t skip_idx;
    arena_elem_flags_t flags;
    void* alloc;
} arena_prealloc_t; 

typedef struct {
    uint32_t cap;
    arena_prealloc_t* arr;
} region_t;

typedef struct {
    arena_idx_t top;
    dyn_arr_t* regions; 
} arena_t;

region_t* init_region(size_t cap);
void free_region(region_t* region);

arena_t* init_arena(size_t cap);
void free_arena(arena_t* arena);

arena_idx_t arena_prealloc(arena_t* arena);
arena_prealloc_t* arena_get_prealloc(arena_t* arena, arena_idx_t);

void arena_elem_set_flags(arena_t* arena, arena_idx_t handle,
        arena_elem_flags_t flags);
void arena_elem_unset_flags(arena_t* arena, arena_idx_t handle,
        arena_elem_flags_t flags);

void* arena_malloc(arena_t* arena, arena_idx_t handle, size_t bytes);

void arena_reset_sp(arena_t* arena, arena_idx_t handle);

#endif

