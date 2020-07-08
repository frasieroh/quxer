#ifndef DEQUE_H
#define DEQUE_H

#include <inttypes.h>

typedef struct {
    uint32_t cap;
    uint32_t start;
    uint32_t end;
    uint32_t len;
    void** arr;
} dq_t;

dq_t* init_dq(uint32_t cap);
void dq_push_l(dq_t* dq, void* elem);
void dq_push_r(dq_t* dq, void* elem);
void* dq_pop_l(dq_t* dq);
void* dq_pop_r(dq_t* dq);
void* dq_get(dq_t* dq, uint32_t idx);
void free_dq(dq_t* dq);
uint32_t dq_len(dq_t* dq);

#endif

