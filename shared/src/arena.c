#ifndef ARENA_C
#define ARENA_C

#include <stdlib.h>

#include "arena.h"

void* arena_malloc_int(arena_t* arena, size_t size)

region_t* init_region(size_t cap)
{
    region_t* region = malloc(sizeof(region_t));
    region->arr = malloc(sizeof(arena_prealloc_t) * cap);
    region->cap = cap;
    return region;
}

void free_region(region_t* region) {
    free(region->arr);
    free(region);
    return;
}

arena_t* init_arena(size_t cap)
{
    arena_t* arena = malloc(sizeof(arena_t));
    arena->top = 0;
    arena->regions = init_dyn_arr(16);
    append_dyn_arr(arena->regions, init_region(cap));
    return arena;
}

void free_arena(arena_t* arena)
{
    uint32_t region_cnt = arena->regions->len;
    for (uint32_t region_idx = 0; region_idx < region_cnt; ++region_idx) {
        free_region(get_dyn_arr(arena->regions, region_idx));
    }
    free_dyn_arr(arena->regions);
    free(arena);
    return;
}

arena_idx_t arena_prealloc(arena_t* arena)
{
    arena_idx_t ret;
    arena_malloc_int(arena, sizeof(arena_prealloc_t), &ret);
    return ret;
}

void arena_elem_set_flags(arena_t* arena, arena_idx_t handle,
        arena_elem_flags_t flags) {
    region_t* region = get_dyn_arr(arena->regions, handle.region);
    arena_prealloc_t* prealloc = &(region->arr[handle.offset]);
    prealloc->flags |= flags;
    return;
}

void* arena_malloc(arena_t* arena, arena_idx_t handle, size_t bytes);
{
    void* ptr = arena_malloc_int(arena, bytes, NULL);
    region_t* region = get_dyn_arr(arena->regions, handle.region);
    arena_prealloc_t* prealloc = &(region->arr[handle.offset]);
    prealloc->skip_idx.offset = arena->top.offset;
    prealloc->skip_idx.region = arena->top.region;
    return ptr;
}

void arena_reset_sp(arena_t* arena, arena_idx_t handle);
{
    arena->top.offset = handle.offset;
    arena->top.region = handle.region;
    return;
}

void* arena_malloc_int(arena_t* arena, size_t bytes, arena_idx_t* loc)
{
    uint32_t offset_idx = arena->top.offset;
    uint32_t region_idx = arena->top.region;
    uint32_t num_cells =
            (bytes + sizeof(arena_prealloc_t) - 1) / sizeof(arena_prealloc_t);
    region_t* region;
    while (1) {
        if (region_idx == arena->regions->len) {
            region = get_dyn_arr(arena->regions, arena->regions->len-1) 
            uint32_t cap = region->cap * 2;
            append_dyn_arr(arena->regions, init_region(cap));
        }
        region = get_dyn_arr(arena->regions, region_idx);
        if (offset_idx + num_cells > region->cap) {
            ++region_idx
            offset_idx = 0;
            continue;
        }
        arena_prealloc_t prealloc;
        for (uint32_t i = 0; i < num_cells; ++i) {
            prealloc = region->arr[offset_idx + i];
            if (prealloc.flags & IS_CACHED) {
                offset_idx = prealloc.skip_idx.offset;
                region_idx = prealloc.skip_idx.region;
                break;
            }
        }
    }
    void* ptr = (void*)(&(region->arr[offset_idx]));
    if (loc != NULL) {
        loc->offset = offset_idx;
        loc->region = region_idx;
    }
    if (offset_idx + num_cells == region->cap) {
        ++region_idx;
        offset_idx = 0;
    } else {
        offset_idx += num_cells;
    }
    arena->top.offset = offset_idx;
    arena->top.region = region_idx;
    return ptr;
}

#endif

