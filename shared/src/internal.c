#ifndef LIB_C
#define LIB_C

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "internal.h"

// void free_tree(rnode_t* node, pnode_flag_t exclude)
// {
//     if (!(node->flags & exclude)) {
//         for (uint32_t i = 0; i < node->num_children; ++i) {
//             free_tree(node->children[i], exclude);
//         }
//         free(node);
//     }
// }
// 
// void finalize_tree(rnode_t* node)
// {
//     for (uint32_t i = 0; i < node->num_children; ++i) {
//         finalize_tree(node->children[i]);
//     }
//     node->flags |= IS_FINAL;
// }

memo_state_t* init_memo_state(imported_file_t* imported_file,
        uint32_t num_rules)
{
    memo_state_t* state = malloc(sizeof(memo_state_t));
    state->call_dyn_arr = init_dyn_arr(16);
    // state->cache_head = NULL;
    state->cache_arr = calloc(sizeof(cached_rnode_t),
             (imported_file->text_len + 1) * num_rules);
    state->arena = init_arena(1024);
    return state;
}

void free_memo_state(memo_state_t* state)
{
    // cached_rnode_t* curr = NULL;
    // cached_rnode_t* next = state->cache_head;
    // while (next != NULL) {
    //     curr = next;
    //     next = next->next;
    //     if (curr->result && !(curr->result->flags & IS_FINAL)) {
    //         free_tree(curr->result, IS_FINAL);
    //     }
    //     free(curr);
    // }
    free_dyn_arr(state->call_dyn_arr);
    free(state->cache_arr);
    free_arena(state->arena);
    free(state);
    return;
}

rnode_t* call_eval(uint32_t id, memo_state_t* state, uint8_t* text,
        uint32_t text_length, uint32_t pos)
{
#ifdef PRINT_TRACE
    printf("Cvaluating rule %s, pos %d\n", name_map[id], pos);
#endif
    // cached_rnode_t** cached_rnode =
    //         &(state->cache_arr[id * (text_length + 1) + pos]);
    cached_rnode_t* cached_rnode = 
            &(state->cache_arr[id * (text_length + 1) + pos]);
    if (!(cached_rnode->flags & IS_VALID)) {
        cached_rnode->flags |= IN_PROGRESS;
        append_dyn_arr(state->call_dyn_arr, &id);
        eval_return_t ret;
        eval_map[id](state, text, text_length, pos, &ret);
        pop_dyn_arr(state->call_dyn_arr);
        rnode_t* result = ret.alloc;
        cached_rnode->result = result;
        cached_rnode->flags ^= IN_PROGRESS;
#ifdef PRINT_TRACE
        if (result) {
            printf("Caching rule %s, pos %d -> %d\n",
                name_map[id], pos, result->end);
        } else {
            printf("Caching rule %s, pos %d -> fail\n",
                name_map[id], pos);
        }
#endif
        if (result) {
            arena_set_cached(state->arena, ret.prealloc, result);
        }
        cached_rnode->flags |= IS_VALID;
        return result;
    } else if (cached_rnode->flags & IN_PROGRESS) {
         uint32_t top_id = *((uint32_t*)get_dyn_arr(
                 state->call_dyn_arr, state->call_dyn_arr->len - 1));
         if (top_id != id) {
             printf("Indirect left recursion: rule %s\n", name_map[id]);
             exit(EXIT_FAILURE);
         } else {
             printf("Direct left recursion: rule %s\n", name_map[id]);
             exit(EXIT_FAILURE);
         }
     }
#ifdef PRINT_TRACE
     if (cached_rnode->result) {
         printf("Recalling rule %s, pos %d -> %d\n",
             name_map[id], pos, cached_rnode->result->end);
     } else {
         printf("Recalling rule %s, pos %d -> fail\n",
             name_map[id], pos);
     }
#endif
    return cached_rnode->result;
}

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
        // finalize_tree(result);
        // free_memo_state(state);
        semantic_result = generate_semantic_result(imported_file->text, result);
        //free_tree(result, 0);
    } else {
        printf("Parse failed\n");
        //free_memo_state(state);
    }
    free_memo_state(state);
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
        (node_jump_map[node->id].alias_allocs)(context);
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
        (node_jump_map[node->id].action)(context);
        (node_jump_map[node->id].alias_frees)(context);
    }
    return;
}

#endif

