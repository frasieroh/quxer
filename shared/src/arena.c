#ifndef ARENA_C
#define ARENA_C

#include <stdlib.h>
#include <stdio.h>

#include "arena.h"

region_t* init_region(size_t cap)
{
    region_t* region = malloc(sizeof(region_t));
    region->arr = calloc(cap, sizeof(arena_boundary_t));
    region->arr[0].next = &(region->arr[cap - 1]);
    region->cap = cap;
    return region;
}

void free_region(region_t* region)
{
    free(region->arr);
    free(region);
    return;
}

arena_t* init_arena(size_t cap)
{
    arena_t* arena = malloc(sizeof(arena_t));
    arena->regions = init_dyn_arr(16);
    region_t* initial_region = init_region(cap);
    append_dyn_arr(arena->regions, initial_region);
    arena->top = initial_region->arr;
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

void* arena_prealloc(arena_t* arena)
{
    return arena->top;
}

void arena_set_cached(arena_t* arena, void* prealloc, void* alloc) 
{
    arena_boundary_t* prealloc_boundary = (arena_boundary_t*)prealloc;
    arena_boundary_t* after_alloc_boundary = 
        ((arena_boundary_t*)alloc - 1)->next;
    prealloc_boundary->next = after_alloc_boundary;
    prealloc_boundary->flags |= FROZEN;
    return;
}

void* arena_malloc(arena_t* arena, size_t bytes)
{
    arena_boundary_t* base = arena->top;
    arena_boundary_t* current = base;
    uint32_t num_cells = 1 + // allocate an extra cell for the end boundary
            (bytes + sizeof(arena_boundary_t) - 1) / sizeof(arena_boundary_t);
    uint32_t allocatable = 0;
    while (allocatable < num_cells) {
        if (current->next == NULL) {
            region_t* last_region = get_dyn_arr(
                    arena->regions, arena->regions->len - 1);
            uint32_t cap = last_region->cap * 2;
            region_t* new_region = init_region(cap);
            append_dyn_arr(arena->regions, new_region);
            current->next = new_region->arr;
            current->flags |= FROZEN;
            base = current->next;
            current = base;
            allocatable = 0;
            continue;
        }
        if (!(current->flags & FROZEN)) {
            allocatable += (uint32_t)(current->next - current)
                / sizeof(arena_boundary_t); 
        } else {
            base = current->next;
            current = base;
            allocatable = 0;
            continue;
        }
        current = current->next;
    }
    arena_boundary_t* next_cell = base + num_cells;
    if (next_cell != current) {
        next_cell->next = current;
        next_cell->flags = 0;
    }
    base->next = next_cell;
    base->flags = 0;
    arena->top = next_cell;
    return base + 1;
}

void arena_reset_sp(arena_t* arena, void* prealloc)
{
    arena->top = prealloc;
    return;
}

#endif

