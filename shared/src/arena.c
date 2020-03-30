#ifndef ARENA_C
#define ARENA_C

#include <stdlib.h>
#include <stdio.h>

#include "arena.h"

#define FIXED_ALLOC_SIZE 48 // 3 children

static void* arena_malloc_dynamic(dyn_arr_t* regions, alloc_boundary_t** top,
        uint32_t num_cells);

static void* arena_malloc_fixed(dyn_arr_t* regions, dyn_arr_t* backings,
        fixed_boundary_t** top);

static region_t* init_fixed_region(uint32_t cap);

static region_t* init_fixed_backing_region(region_t* fixed_region);

static region_t* init_dynamic_region(uint32_t cap);

static void free_region(region_t* region);

arena_t* init_arena(size_t cap)
{
    arena_t* arena = malloc(sizeof(arena_t));
    arena->fixed = init_dyn_arr(8);
    arena->fixed_backing = init_dyn_arr(8);
    arena->dynamic = init_dyn_arr(8);
    region_t* fixed_region = init_fixed_region(cap);
    region_t* fixed_backing_region = init_fixed_backing_region(fixed_region);
    region_t* dynamic_region = init_dynamic_region(cap);
    append_dyn_arr(arena->fixed, fixed_region);
    append_dyn_arr(arena->fixed_backing, fixed_backing_region);
    append_dyn_arr(arena->dynamic, dynamic_region);
    arena->ptrs.fixed = fixed_backing_region->data.fixed_backing;
    arena->ptrs.dynamic = dynamic_region->data.dynamic;
    return arena;
}

void free_arena(arena_t* arena)
{
    uint32_t region_cnt = arena->fixed->len;
    for (uint32_t i = 0; i < region_cnt; ++i) {
        free_region(get_dyn_arr(arena->fixed, i));
    }
    free_dyn_arr(arena->fixed);
    region_cnt = arena->fixed_backing->len;
    for (uint32_t i = 0; i < region_cnt; ++i) {
        free_region(get_dyn_arr(arena->fixed_backing, i));
    }
    free_dyn_arr(arena->fixed_backing);
    region_cnt = arena->dynamic->len;
    for (uint32_t i = 0; i < region_cnt; ++i) {
        free_region(get_dyn_arr(arena->dynamic, i));
    }
    free_dyn_arr(arena->dynamic);
    free(arena);
    return;
}

arena_ptrs_t* arena_prealloc(arena_t* arena, arena_ptrs_t* ret)
{
    *ret = arena->ptrs;
    return ret;
}

void arena_set_cached(arena_t* arena, arena_ptrs_t* prealloc) 
{
    if (prealloc->fixed != arena->ptrs.fixed) {
        prealloc->fixed->flags |= FROZEN;
        prealloc->fixed->next = arena->ptrs.fixed;
    }
    if (prealloc->dynamic != arena->ptrs.dynamic) {
        prealloc->dynamic->flags |= FROZEN;
        prealloc->dynamic->next = arena->ptrs.dynamic;
    }
    return;
}

void* arena_malloc(arena_t* arena, size_t bytes)
{
    if (bytes <= FIXED_ALLOC_SIZE) {
        return arena_malloc_fixed(arena->fixed, arena->fixed_backing,
                &(arena->ptrs.fixed));
    } else {
        uint32_t num_cells = (bytes + sizeof(alloc_boundary_t) - 1)
                / sizeof(alloc_boundary_t);
        return arena_malloc_dynamic(arena->dynamic,
                &(arena->ptrs.dynamic), num_cells);
    }
}

void arena_reset_sp(arena_t* arena, arena_ptrs_t* prealloc)
{
    arena->ptrs = *prealloc;
    return;
}

void* arena_malloc_dynamic(dyn_arr_t* regions, alloc_boundary_t** top,
        uint32_t num_cells)
{
    alloc_boundary_t* base = *top;
    alloc_boundary_t* current = base;
    uint32_t allocatable = 0;
    ++num_cells; // allocate an extra cell for the end boundary
    while (allocatable < num_cells) {
        if (current->flags & FROZEN) {
            if (current->next == NULL) {
                region_t* last_region = get_dyn_arr(regions, regions->len - 1);
                uint32_t cap = last_region->cap * 2;
                region_t* new_region = init_dynamic_region(cap);
                append_dyn_arr(regions, new_region);
                current->next = new_region->data.dynamic;
            }
            base = current->next;
            current = base;
            allocatable = 0;
            continue;
        }
        allocatable += (uint32_t)(current->next - current)
            / sizeof(alloc_boundary_t); 
        current = current->next;
    }
    alloc_boundary_t* next_cell = base + num_cells;
    if (current - next_cell > 192) { // min size for dynamic allocation
        next_cell->next = current;
        next_cell->flags = 0;
        base->next = next_cell;
        *top = next_cell;
    } else {
        base->next = current;
        *top = current;
    }
    base->flags = 0;
    return base + 1;
}

void* arena_malloc_fixed(dyn_arr_t* regions, dyn_arr_t* backings,
        fixed_boundary_t** top)
{
    fixed_boundary_t* base = *top;
    while (1) {
        if (base->flags & FROZEN) {
            if (base->next == NULL) {
                region_t* last_region = get_dyn_arr(regions, regions->len - 1);
                uint32_t cap = last_region->cap * 2;
                region_t* new_region = init_fixed_region(cap);
                region_t* new_backing = init_fixed_backing_region(new_region);
                append_dyn_arr(regions, new_region);
                append_dyn_arr(backings, new_backing);
                base->next = new_backing->data.fixed_backing;
            }
            base = base->next;
            continue;
        }
        break;
    }
    void* ptr = base->fixed;
    *top = base + 1;
    (*top)->fixed = (void*)((char*)ptr + FIXED_ALLOC_SIZE);
    return ptr;
}

void free_region(region_t* region)
{
    free((void*)(region->data.fixed));
    free(region);
    return;
}

region_t* init_fixed_region(uint32_t cap)
{
    region_t* fixed_region = malloc(sizeof(region_t));
    fixed_region->data.fixed = calloc(cap, FIXED_ALLOC_SIZE);
    fixed_region->cap = cap;
    return fixed_region;
}

region_t* init_fixed_backing_region(region_t* fixed_region)
{
    uint32_t cap = fixed_region->cap + 1;
    region_t* backing_region = malloc(sizeof(region_t));
    backing_region->data.fixed_backing = calloc(cap, sizeof(fixed_boundary_t));
    backing_region->cap = cap;
    backing_region->data.fixed_backing[0].fixed =
        fixed_region->data.fixed;
    backing_region->data.fixed_backing[cap - 1].flags |= FROZEN;
    return backing_region;
}

region_t* init_dynamic_region(uint32_t cap)
{
    region_t* dynamic_region = malloc(sizeof(region_t));
    dynamic_region->data.dynamic = calloc(cap, sizeof(alloc_boundary_t));
    dynamic_region->cap = cap;
    dynamic_region->data.dynamic[0].next = 
        &(dynamic_region->data.dynamic[cap - 1]);
    dynamic_region->data.dynamic[cap - 1].flags |= FROZEN;
    return dynamic_region;
}

#endif

