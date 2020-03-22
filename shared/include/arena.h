#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <inttypes.h>

#include "dyn_arr.h"

typedef enum {
    IS_CACHED = 0x1,
} arena_elem_flags_t;

typedef struct {
    uint32_t offset;
    uint32_t region;
} arena_idx_t;

typedef struct {
    arena_idx_t skip_idx;
    arena_elem_flags_t flags;
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

void arena_elem_set_flags(arena_t* arena, arena_idx_t handle,
        arena_elem_flags_t flags) {

void* arena_malloc(arena_t* arena, arena_idx_t handle, size_t bytes);

void arena_reset_sp(arena_t* arena, arena_idx_t handle);

#endif

