#ifndef DEQUE_C
#define DEQUE_C

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "deque.h"

static void maybe_grow_dq(dq_t* dq);

dq_t* init_dq(uint32_t cap)
{
    assert(cap > 0);
    dq_t* dq = malloc(sizeof(dq_t));
    dq->cap = cap;
    dq->start = 0;
    dq->end = 0;
    dq->len = 0;
    dq->arr = malloc(sizeof(void*) * cap);
    return dq;
}

void dq_push_l(dq_t* dq, void* elem)
{
    maybe_grow_dq(dq);
    uint32_t before_first_idx = 
            (dq->start + dq->cap - 1) % dq->cap;
    dq->arr[before_first_idx] = elem;
    dq->start = before_first_idx;
    ++(dq->len);
    return;
}

void dq_push_r(dq_t* dq, void* elem)
{
    maybe_grow_dq(dq);
    dq->arr[dq->end] = elem;
    dq->end = (dq->end + 1) % dq->cap;
    ++(dq->len);
    return;
}

void* dq_pop_l(dq_t* dq)
{
    assert(dq->len > 0);
    void* ret = dq->arr[dq->start];
    dq->start = (dq->start + 1) % dq->cap;
    --(dq->len);
    return ret;
}

void* dq_pop_r(dq_t* dq)
{
    assert(dq->len > 0);
    uint32_t last_idx = (dq->end + dq->cap - 1) % dq->cap;
    void* ret = dq->arr[last_idx];
    dq->end = last_idx;
    --(dq->len);
    return ret;
}

void* dq_get(dq_t* dq, uint32_t idx)
{
    assert(dq->len > idx);
    return dq->arr[(dq->start + idx) % dq->cap];
}

void free_dq(dq_t* dq)
{
    free(dq->arr);
    free(dq);
    return;
}

uint32_t dq_len(dq_t* dq)
{
    return dq->len;
}

void maybe_grow_dq(dq_t* dq)
{
    if (dq->len == dq->cap) {
        uint32_t cap = dq->cap;
        uint32_t start = dq->start;
        uint32_t end = dq->end;
        uint32_t len = dq->len;
        void** arr = dq->arr;
        assert(start == end);
        if (start != 0) { // wrap around
            void** new_arr = malloc(sizeof(void*) * cap * 2);
            memcpy(new_arr, arr + start, sizeof(void*) * (cap - start));
            memcpy(new_arr + (cap - start), arr,
                    sizeof(void*) * (len - (cap - start)));
            free(arr);
            dq->cap = cap * 2;
            dq->start = 0;
            dq->end = len;
            dq->arr = new_arr;
        } else {
            dq->arr = realloc(arr, sizeof(void*) * cap * 2);
            dq->cap = cap * 2;
            dq->end = len;
        }
    }
    return;
}

typedef struct {
    int a;
    int b;
} point_t;

#endif

