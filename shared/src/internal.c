#ifndef LIB_C
#define LIB_C

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "internal.h"

dyn_arr_t* init_dyn_arr(uint32_t cap)
{
    dyn_arr_t* list = malloc(sizeof(dyn_arr_t));
    list->arr = malloc(sizeof(void*) * cap);
    list->cap = cap;
    list->len = 0;
    return list;
}

void free_dyn_arr(dyn_arr_t* list)
{
    free(list->arr);
    free(list);
    return;
}

void append_dyn_arr(dyn_arr_t* list, void* element)
{
    if (list->len >= list->cap) {
        list->cap *= 2;
        list->arr = realloc(list->arr, sizeof(void*) * list->cap);
    }
    list->arr[list->len++] = element;
    return;
}

void* pop_dyn_arr(dyn_arr_t* list)
{
    return list->arr[--(list->len)];
}

void* get_dyn_arr(dyn_arr_t* list, uint32_t index)
{
    return list->arr[index];
}

void free_tree(rnode_t* node, pnode_flag_t exclude)
{
    if (!(node->flags & exclude)) {
        for (uint32_t i = 0; i < node->num_children; ++i) {
            free_tree(node->children[i], exclude);
        }
        free(node);
    }
}

void finalize_tree(rnode_t* node)
{
    for (uint32_t i = 0; i < node->num_children; ++i) {
        finalize_tree(node->children[i]);
    }
    node->flags |= IS_FINAL;
}

memo_state_t* init_memo_state(imported_file_t* imported_file,
        uint32_t num_rules)
{
    memo_state_t* state = malloc(sizeof(memo_state_t));
    state->call_dyn_arr = init_dyn_arr(16);
    state->cache_head = NULL;
    state->cache_arr = calloc(sizeof(cached_rnode_t*),
            (imported_file->text_len + 1) * num_rules);
    return state;
}

void free_memo_state(memo_state_t* state)
{
    cached_rnode_t* curr = NULL;
    cached_rnode_t* next = state->cache_head;
    while (next != NULL) {
        curr = next;
        next = next->next;
        if (curr->result && !(curr->result->flags & IS_FINAL)) {
            free_tree(curr->result, IS_FINAL);
        }
        free(curr);
    }
    free_dyn_arr(state->call_dyn_arr);
    free(state->cache_arr);
    free(state);
    return;
}

rnode_t* call_eval(uint32_t id, memo_state_t* state, uint8_t* text,
        uint32_t text_length, uint32_t pos)
{
#ifdef PRINT_TRACE
    printf("evaluating rule %s, pos %d\n", name_map[id], pos);
#endif
    cached_rnode_t** cached_rnode =
            &(state->cache_arr[id * (text_length + 1) + pos]);
    if (!(*cached_rnode)) {
        (*cached_rnode) = malloc(sizeof(cached_rnode_t));
        (*cached_rnode)->flags |= IN_PROGRESS;
        (*cached_rnode)->next = state->cache_head;
        state->cache_head = *cached_rnode;
        append_dyn_arr(state->call_dyn_arr, &id);
        rnode_t* result = eval_map[id](state, text, text_length, pos);
        pop_dyn_arr(state->call_dyn_arr);
        (*cached_rnode)->result = result;
        (*cached_rnode)->flags ^= IN_PROGRESS;
        if (result) {
            (*cached_rnode)->result->flags |= IS_CACHED;
        }
        /*
        if ((*cached_rnode)->flags & LR_DETECTED) {
            return grow_lr(id, state, text, text_length, pos);
        }
        */
#ifdef PRINT_TRACE
        if (result) {
            printf("caching rule %s, pos %d -> %d\n",
                name_map[id], pos, result->end);
        } else {
            printf("caching rule %s, pos %d -> fail\n",
                name_map[id], pos);
        }
#endif
        return result;
    } else if ((*cached_rnode)->flags & IN_PROGRESS) {
        uint32_t top_id = *((uint32_t*)get_dyn_arr(
                state->call_dyn_arr, state->call_dyn_arr->len - 1));
        if (top_id != id) {
            printf("Indirect left recursion: rule %s\n", name_map[id]);
            exit(EXIT_FAILURE);
        } else {
            // direct left recursion
            // (*cached_rnode)->flags |= LR_DETECTED;
            // return NULL;
            printf("Direct left recursion: rule %s\n", name_map[id]);
            exit(EXIT_FAILURE);
        }
    }
#ifdef PRINT_TRACE
    if ((*cached_rnode)->result) {
        printf("recalling rule %s, pos %d -> %d\n",
            name_map[id], pos, (*cached_rnode)->result->end);
    } else {
        printf("recalling rule %s, pos %d -> fail\n",
            name_map[id], pos);
    }
#endif
    return (*cached_rnode)->result;
}

/*
rnode_t* grow_lr(uint32_t id, memo_state_t* state, uint8_t* text,
        uint32_t text_length, uint32_t pos)
{
#ifdef PRINT_TRACE
    printf("evaluating left-recursive rule %s, pos %d\n", name_map[id], pos);
#endif
    cached_rnode_t** cached_rnode =
            &(state->cache_arr[id * (text_length + 1) + pos]);
    rnode_t* result;
    while (1) {
        append_dyn_arr(state->call_dyn_arr, &id);
        result = eval_map[id](state, text, text_length, pos);
        pop_dyn_arr(state->call_dyn_arr);
        if (!result || result->end <= pos) {
            break;
        }
        (*cached_rnode)->result->flags ^= IS_CACHED;
        free_tree((*cached_rnode)->result, IS_CACHED);
        (*cached_rnode)->result = result;
        (*cached_rnode)->result->flags |= IS_CACHED;
    }
#ifdef PRINT_TRACE
        if (result) {
            printf("caching left-recursive rule %s, pos %d -> %d\n",
                name_map[id], pos, result->end);
        } else {
            printf("caching left-recursive rule %s, pos %d -> fail\n",
                name_map[id], pos);
        }
#endif
    return result;
}
*/

imported_file_t* import_file(char* filename)
{
    FILE* file;
    if ( !(file = fopen(filename, "r") ) ) {
        fprintf(stderr, "Could not open file %s: error code %d\n",
            filename, errno);
        return NULL;
    }
    uint32_t len = 0;
    uint32_t read_size = 1024;
    uint8_t* text = malloc(sizeof(uint8_t) * read_size);
    while (1) {
        uint32_t num_read = fread(text + len, sizeof(uint8_t), read_size, file);
        len = len + num_read;
        if (num_read < read_size) {
            break;
        } else {
            read_size = read_size * 2;
            uint8_t* text_old = text;
            text = malloc(sizeof(uint8_t) * (read_size + len));
            for (uint32_t i = 0; i < len; ++i) {
                text[i] = text_old[i];
            }
            free(text_old);
        }
    }
    if (fclose(file)) {
        fprintf(stderr, "Could not close file %s\n", filename);
        return NULL;
    }
    imported_file_t* imported_file = malloc(sizeof(imported_file_t));
    imported_file->text = text;
    imported_file->text_len = len;
    return imported_file;
}

void free_file(imported_file_t* imported_file)
{
    free(imported_file->text);
    free(imported_file);
    return;
}

void* parse_file(char* filename)
{
    void* semantic_result = NULL;
    imported_file_t* imported_file = import_file(filename);
    memo_state_t* state = init_memo_state(imported_file, num_rules);
    rnode_t* result = call_eval(0, state, imported_file->text, 
            imported_file->text_len, 0);
    if (result) {
        printf("Parse succeeded\n");
        finalize_tree(result);
        free_memo_state(state);
        semantic_result = generate_semantic_result(imported_file->text, result);
        free_tree(result, 0);
    } else {
        printf("Parse failed\n");
        free_memo_state(state);
    }
    free_file(imported_file);
    return semantic_result;
}

capture_t* init_capture(uint8_t* text, uint32_t start, uint32_t end)
{
    capture_t* capture = malloc(sizeof(capture_t));
    capture->start = start;
    capture->end = end;
    capture->str = malloc(sizeof(uint8_t) * (end - start + 1));
    for (uint32_t i = 0; i < end - start; ++i) {
        capture->str[i] = text[start + i];
    }
    capture->str[end - start] = 0;
    return capture;
}

void free_capture(capture_t* capture)
{
    free(capture->str);
    free(capture);
    return;
}

context_t* init_context()
{
    context_t* context = malloc(sizeof(context_t));
    context->capture = init_dyn_arr(16);
    context->alias = malloc(sizeof(dyn_arr_t*) * num_nodes);
    context->result = NULL;
    return context;
}

void free_context(context_t* context)
{
    for (uint32_t i = 0; i < context->capture->len; ++i) {
        free_capture(get_dyn_arr(context->capture, i));
    }
    free_dyn_arr(context->capture);
    for (uint32_t i = 0; i < num_nodes; ++i) {
        // TODO: stop leaking memory here
        // free_dyn_arr(context->alias[i]);
    }
    free(context->alias);
    free(context);
    return;
}

void* generate_semantic_result(uint8_t* text, rnode_t* root)
{
    context_t* context = init_context();
    generate_semantic_result_recursive(context, text, root);
    void* result = context->result;
    free_context(context);
    return result;
}

void generate_semantic_result_recursive(
        context_t* context, uint8_t* text, rnode_t* node)
{
    if (node->flags & SEMANTIC_ACTION) {
        alias_allocs_map[node->id](context);
    }
    if (node->type == NONTERMINAL_T) {
        context_t* inner_context = init_context();
        generate_semantic_result_recursive(
                inner_context, text, node->children[0]);
        if (node->flags & ALIAS) {
            append_dyn_arr(
                    context->alias[node->id], inner_context->result);
        }
        free_context(inner_context);
    } else {
        for (uint32_t i = 0; i < node->num_children; ++i) {
            generate_semantic_result_recursive(
                    context, text, node->children[i]);
        }
    }
    if (node->flags & DO_CAPTURE) {
        append_dyn_arr(
                context->capture,
                init_capture(text, node->start, node->end));
    }
    if (node->flags & SEMANTIC_ACTION) {
        semantic_action_map[node->id](context);
    }
    return;
}

#endif

