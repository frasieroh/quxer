#ifndef ARENA_C
#define ARENA_C

#include <stdlib.h>
#include <stdio.h>

#include "arena.h"

static void* arena_malloc_dynamic(dyn_arr_t* regions, alloc_boundary_t** top,
        uint32_t num_cells);

static void* arena_malloc_fixed(dyn_arr_t* regions, alloc_boundary_t** top,
        uint32_t num_cells);

region_t* init_region(size_t cap)
{
    region_t* region = malloc(sizeof(region_t));
    region->arr = calloc(cap, sizeof(alloc_boundary_t));
    region->arr[0].next = &(region->arr[cap - 1]);
    region->arr[cap - 1].flags |= FROZEN;
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
    arena->thsholds.small = 3;
    arena->thsholds.med   = 4;
    arena->thsholds.large = 8;
    arena->thsholds.huge  = 16;
    arena->regions.small = init_dyn_arr(8);
    arena->regions.med = init_dyn_arr(8);
    arena->regions.large = init_dyn_arr(8);
    arena->regions.huge = init_dyn_arr(8);
    arena->regions.dynamic = init_dyn_arr(8);
    // fixed-allocation regions are + 1 for the boundary at the end
    region_t* region = init_region(cap * (1 + arena->thsholds.small) + 1);
    append_dyn_arr(arena->regions.small, region);
    arena->ptrs.small = region->arr;
    region = init_region(cap * (1 + arena->thsholds.med) + 1);
    append_dyn_arr(arena->regions.med, region);
    arena->ptrs.med = region->arr;
    region = init_region(cap * (1 + arena->thsholds.large) + 1);
    append_dyn_arr(arena->regions.large, region);
    arena->ptrs.large = region->arr;
    region = init_region(cap * (1 + arena->thsholds.huge) + 1);
    append_dyn_arr(arena->regions.huge, region);
    arena->ptrs.huge = region->arr;
    // dynamic-size does not make assumptions about available space,
    // so it's just pretty big
    region = init_region(cap * 2 * arena->thsholds.huge);
    append_dyn_arr(arena->regions.dynamic, region);
    arena->ptrs.dynamic = region->arr;
    return arena;
}

void free_arena(arena_t* arena)
{
    uint32_t region_cnt = arena->regions.small->len;
    for (uint32_t region_idx = 0; region_idx < region_cnt; ++region_idx) {
        free_region(get_dyn_arr(arena->regions.small, region_idx));
    }
    free_dyn_arr(arena->regions.small);
    region_cnt = arena->regions.med->len;
    for (uint32_t region_idx = 0; region_idx < region_cnt; ++region_idx) {
        free_region(get_dyn_arr(arena->regions.med, region_idx));
    }
    free_dyn_arr(arena->regions.med);
    region_cnt = arena->regions.large->len;
    for (uint32_t region_idx = 0; region_idx < region_cnt; ++region_idx) {
        free_region(get_dyn_arr(arena->regions.large, region_idx));
    }
    free_dyn_arr(arena->regions.large);
    region_cnt = arena->regions.huge->len;
    for (uint32_t region_idx = 0; region_idx < region_cnt; ++region_idx) {
        free_region(get_dyn_arr(arena->regions.huge, region_idx));
    }
    free_dyn_arr(arena->regions.huge);
    region_cnt = arena->regions.dynamic->len;
    for (uint32_t region_idx = 0; region_idx < region_cnt; ++region_idx) {
        free_region(get_dyn_arr(arena->regions.dynamic, region_idx));
    }
    free_dyn_arr(arena->regions.dynamic);
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
    if (prealloc->small != arena->ptrs.small) {
        prealloc->small->flags |= FROZEN;
        prealloc->small->next = arena->ptrs.small;
    }
    if (prealloc->med != arena->ptrs.med) {
        prealloc->med->flags |= FROZEN;
        prealloc->med->next = arena->ptrs.med;
    }
    if (prealloc->large != arena->ptrs.large) {
        prealloc->large->flags |= FROZEN;
        prealloc->large->next = arena->ptrs.large;
    }
    if (prealloc->huge != arena->ptrs.huge) {
        prealloc->huge->flags |= FROZEN;
        prealloc->huge->next = arena->ptrs.huge;
    }
    if (prealloc->dynamic != arena->ptrs.dynamic) {
        prealloc->dynamic->flags |= FROZEN;
        prealloc->dynamic->next = arena->ptrs.dynamic;
    }
    return;
}

void* arena_malloc(arena_t* arena, size_t bytes)
{
    if (bytes <= arena->thsholds.small * sizeof(alloc_boundary_t)) {
        return arena_malloc_fixed(arena->regions.small,
                &(arena->ptrs.small), arena->thsholds.small);
    } else if (bytes <= arena->thsholds.med * sizeof(alloc_boundary_t)) { // 2-3 children
        return arena_malloc_fixed(arena->regions.med,
                &(arena->ptrs.med), arena->thsholds.med);
    } else if (bytes <= arena->thsholds.large * sizeof(alloc_boundary_t)) { // 4-9 children
        return arena_malloc_fixed(arena->regions.large,
                &(arena->ptrs.large), arena->thsholds.large);
    } else if (bytes <= arena->thsholds.huge * sizeof(alloc_boundary_t)) { // 9-21 children
        return arena_malloc_fixed(arena->regions.huge,
                &(arena->ptrs.huge), arena->thsholds.huge);
    } else {
        uint32_t num_cells = (bytes + sizeof(alloc_boundary_t) - 1)
                / sizeof(alloc_boundary_t);
        return arena_malloc_dynamic(arena->regions.dynamic,
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
                region_t* new_region = init_region(cap);
                append_dyn_arr(regions, new_region);
                current->next = new_region->arr;
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

void* arena_malloc_fixed(dyn_arr_t* regions, alloc_boundary_t** top,
        uint32_t num_cells)
{
    alloc_boundary_t* base = *top;
    ++num_cells; // allocate an extra cell for the end boundary
    while (1) {
        if (base->next == NULL) {
            if (base->flags & FROZEN) {
                region_t* last_region = get_dyn_arr(regions, regions->len - 1);
                // don't duplicate the end boundary
                uint32_t cap = last_region->cap * 2 - 1;
                region_t* new_region = init_region(cap);
                append_dyn_arr(regions, new_region);
                base->next = new_region->arr;
            } else {
                break;
            }
            base = base->next;
            continue;
        } else if (base->flags & FROZEN) {
            base = base->next;
            continue;
        }
        break;
    }
    *top = base + num_cells;
    return base + 1;
}

#endif

