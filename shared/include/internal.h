#ifndef LIB_H
#define LIB_H

#include <inttypes.h>
#include <stdlib.h>

#include "ptype.h"

typedef struct rnode_t_ {
    ptype_t type;
    pnode_flag_t flags;
    uint32_t id;
    uint32_t start;
    uint32_t end;
    uint32_t num_children;
    struct rnode_t_* children[0];
} rnode_t;

typedef struct {
    uint32_t cap;
    uint32_t len;
    void** arr;
} dyn_arr_t;

typedef enum {
    IN_PROGRESS = 0x1,
    LR_DETECTED = 0x2,
} cache_flag_t;

typedef struct cached_rnode_t_ {
    rnode_t* result;
    cache_flag_t flags;
    struct cached_rnode_t_* next;
} cached_rnode_t;

typedef struct {
    dyn_arr_t* call_dyn_arr;
    cached_rnode_t* cache_head;
    cached_rnode_t** cache_arr;
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
    dyn_arr_t* capture; // capture->arr[index] -> capture_t*
    dyn_arr_t** alias; // alias[which]->arr[index] -> void*
    void* result;
} context_t;

dyn_arr_t* init_dyn_arr(uint32_t cap);
void free_dyn_arr(dyn_arr_t* list);
void append_dyn_arr(dyn_arr_t* list, void* element);
void* pop_dyn_arr(dyn_arr_t* list);
void* get_dyn_arr(dyn_arr_t* list, uint32_t index);

void free_tree(rnode_t* node, pnode_flag_t exclude);
void finalize_tree(rnode_t* node);

memo_state_t* init_memo_state(
    imported_file_t* imported_file, uint32_t num_rules);
void free_memo_state(memo_state_t* memo_state);

extern char* name_map[];
extern uint32_t num_rules;
extern uint32_t num_nodes;

rnode_t* call_eval(uint32_t, memo_state_t*, uint8_t*, uint32_t, uint32_t);
// rnode_t* grow_lr(uint32_t, memo_state_t*, uint8_t*, uint32_t, uint32_t);
typedef rnode_t* (*evalfcn_t)(memo_state_t*, uint8_t*, uint32_t, uint32_t);
extern evalfcn_t eval_map[];

typedef void (*actionfcn_t)(context_t*);
// extern actionfcn_t semantic_action_map[];

typedef void (*aliasallocsfcn_t)(context_t*);
// extern aliasallocsfcn_t alias_allocs_map[];

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

