#ifndef LIB_H
#define LIB_H

#include <inttypes.h>
#include <stdlib.h>

#include "ptype.h"
#include "deque.h"
#include "arena.h"

typedef struct rnode_t_ {
    ptype_t type;
    pnode_flag_t flags;
    uint32_t id;
    uint32_t start;
    uint32_t end;
    uint32_t num_children;
    struct rnode_t_* children[0];
} rnode_t;

typedef enum {
    IN_PROGRESS = 0x1,
    IS_VALID = 0x2
} cache_flag_t;

typedef struct {
    cache_flag_t flags;
    rnode_t* result;
} cached_rnode_t;

typedef struct {
    dq_t* callstack;
    cached_rnode_t* cache_arr;
    arena_t* arena;
} memo_state_t;

typedef struct {
    uint8_t* text;
    uint32_t text_len;
} imported_file_t;

typedef struct {
    uint32_t start;
    uint32_t end;
    uint8_t* str;
} capture_t;

typedef struct {
    dq_t* capture; // capture->arr[index] -> capture_t*
    dq_t** alias; // alias[which]->arr[index] -> void*
    void* result;
} context_t;

typedef struct {
    arena_ptrs_t prealloc;
    rnode_t* result;
} eval_return_t;

memo_state_t* init_memo_state(
    imported_file_t* imported_file, uint32_t num_rules);
void free_memo_state(memo_state_t* memo_state);

extern char* name_map[];
extern uint32_t num_rules;
extern uint32_t num_nodes;

rnode_t* call_eval(uint32_t, memo_state_t*, uint8_t*, uint32_t, uint32_t);
typedef void (*evalfcn_t)(memo_state_t*, uint8_t*, uint32_t, uint32_t,
        eval_return_t*);
extern evalfcn_t eval_map[];

typedef void (*actionfcn_t)(context_t*);

typedef void (*aliasallocsfcn_t)(context_t*);

typedef void (*aliasfreesfcn_t)(context_t*);

typedef struct {
    actionfcn_t action;
    aliasallocsfcn_t alias_allocs;
    aliasfreesfcn_t alias_frees;
} node_jump_map_member_t;

extern node_jump_map_member_t node_jump_map[];

imported_file_t* import_file(char* filename);
void free_file(imported_file_t* imported_file);
void* parse_file(char* filename);

capture_t* init_capture(uint8_t* text, uint32_t start, uint32_t end);
void free_capture(capture_t* capture);

context_t* init_context();
void free_context(context_t* context);

void* generate_semantic_result(uint8_t* text, rnode_t* root);
void generate_semantic_result_recursive(
        context_t* context, uint8_t* text, rnode_t* node);

#endif
