#ifndef SEQUENCE_C
#define SEQUENCE_C

#include <stdlib.h>
#include <string.h>

#include "templates/sequence.h"
#include "templates/templates.h"

// static char* generate_free_trees_string(pnode_t* node, uint32_t how_many);
static char* generate_set_children_string(pnode_t* node);

void write_sequence(FILE* file, writer_config_t* config, pnode_t* node)
    /*
0       arena_ptrs_t prealloc_idx_<id> = *arena_prealloc(
                state->arena, &prealloc_idx_<id>);
1       uint32_t current_position_<id> = start_<id>;
        // for every child:
2       uint32_t start_<child_id> = current_position_<id>;
3       rnode_t* result_<child_id> = NULL;
        ... child parser ...
4       if (result_<child_id> == NULL) {
A           arena_reset_sp(state->arena, &prealloc_idx_<id>);
5           goto exit_<id>;
        }
6       current_working_<id> = result_<child_id>->end;
        // then (all children have succeeded):
7       result_<id> = arena_malloc(state->arena,
                sizeof(rnode_t) + sizeof(rnode_t*) * <node->num_data>);
8       result_<id>->flags = <flags_str>
9       result_<id>->type = SEQUENCE_T;
10      result_<id>->start = start_<id>;
11      result_<id>->end = result_<last_child_id>->end;
12      result_<id>->num_children = <node->num_children>;
        result_<id>->children[0] = result_<child_0_id>;
        result_<id>->children[1] = result_<child_1_id>;
s2      ...
13      result_<id>->id = <id>
14      exit_<id>:
    */
{
    uint32_t id = node->id;
    pnode_t* child_node;
    uint32_t child_id;
    fprintf(file,
/*0*/    "arena_ptrs_t prealloc_idx_%u = *arena_prealloc("
                "state->arena, &prealloc_idx_%u);\n"
/*1*/    "uint32_t current_position_%u = start_%u;\n",
/*0*/    id, id,
/*1*/    id, id);
    for (uint32_t i = 0; i < node->num_data; ++i) {
        child_node = node->data.node[i];
        child_id = child_node->id;
        // set up start and return values
        fprintf(file,
/*2*/       "uint32_t start_%u = current_position_%u;\n"
/*3*/       "rnode_t* result_%u = NULL;\n",
/*2*/       child_id, id,
/*3*/       child_id);
        write_template(file, config, child_node);
        fprintf(file,
/*4*/       "if (result_%u == NULL) {\n"
/*A*/       "arena_reset_sp(state->arena, &prealloc_idx_%u);\n"
/*5*/       "goto exit_%u;\n"
            "}\n",
/*4*/       child_id,
/*A*/       id,
/*5*/       id);
        fprintf(file,
/*6*/       "current_position_%u = result_%u->end;\n",
/*6*/       id, child_id);
    }
    char* set_children_string = generate_set_children_string(node);
    char* flags_str = generate_flags_str(node);
    uint32_t last_child_id = node->data.node[node->num_data - 1]->id;
    fprintf(file,
/*7*/   "result_%u = arena_malloc(state->arena, "
                "sizeof(rnode_t) + sizeof(rnode_t*) * %u);\n"
/*8*/   "result_%u->flags = %s"
/*9*/   "result_%u->type = SEQUENCE_T;\n"
/*10*/  "result_%u->start = start_%u;\n"
/*11*/  "result_%u->end = result_%u->end;\n"
/*12*/  "result_%u->num_children = %u;\n"
/*s2*/  "%s"
/*13*/  "result_%u->id = %u;\n"
/*14*/  "exit_%u:\n",
/*7*/   id, node->num_data,
/*8*/   id, flags_str,
/*9*/   id,
/*10*/  id, id,
/*11*/  id, last_child_id,
/*12*/  id, node->num_data,
/*s2*/  set_children_string,
/*13*/  id, id,
/*14*/  id);
    free(set_children_string);
    free(flags_str);
    return;
}

// char* generate_free_trees_string(pnode_t* node, uint32_t how_many)
// {
//     char buf[128];
//     char* result = calloc(sizeof(char), 1); 
//     uint32_t child_id;
//     for (uint32_t i = 0; i < how_many; ++i) {
//         child_id = node->data.node[i]->id;
//         sprintf(buf, "free_tree(result_%u, IS_CACHED);\n", child_id);
//         append_str(buf, &result);
//     }
//     return result;
// }

char* generate_set_children_string(pnode_t* node)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    uint32_t id = node->id;
    uint32_t child_id;
    for (uint32_t i = 0; i < node->num_data; ++i) {
        child_id = node->data.node[i]->id;
        sprintf(buf, "result_%u->children[%u] = result_%u;\n",
            id, i, child_id);
        append_str(buf, &result);
    }
    return result;
}

#endif

