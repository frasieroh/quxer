#ifndef NOT_C
#define NOT_C

#include <stdlib.h>

#include "templates/not.h"
#include "templates/templates.h"

void write_not(FILE* file, writer_config_t* config, pnode_t* node)
/*
0   void* prealloc_idx_<id> = arena_prealloc(state->arena);
1   uint32_t start_<child_id> = start_<id>;
2   rnode_t* result_<child_id> = NULL;
    ... child parser ...
3   if (!result_<child_id>) {
4       result_<id> = arena_malloc(state->arena,
                sizeof(rnode_t));
5       result_<id>->flags = <flags_str>
6       result_<id>->type = NOT_T;
7       result_<id>->start = start_<id>;
8       result_<id>->end = start_<id>;
9       result_<id>->num_children = 0;
10      result_<id>->id = <id>
    } else {
11      arena_reset_sp(state->arena, prealloc_idx_<id>)
    }
*/
{
    uint32_t id = node->id;
    pnode_t* child_node = node->data.node[0];
    uint32_t child_id = child_node->id;
    fprintf(file,
/*0*/   "void* prealloc_idx_%u = arena_prealloc(state->arena);\n"
/*1*/   "uint32_t start_%u = start_%u;\n"
/*2*/   "rnode_t* result_%u = NULL;\n",
/*0*/   id,
/*1*/   child_id, id,
/*2*/   child_id);
    write_template(file, config, child_node);
    char* flags_str = generate_flags_str(node);
    fprintf(file,
/*3*/   "if (!result_%u) {\n"
/*4*/   "result_%u = arena_malloc(state->arena, "
            "sizeof(rnode_t));\n"
/*5*/   "result_%u->flags = %s"
/*6*/   "result_%u->type = NOT_T;\n"
/*7*/   "result_%u->start = start_%u;\n"
/*8*/   "result_%u->end = start_%u;\n"
/*9*/   "result_%u->num_children = 0;\n"
/*10*/  "result_%u->id = %u;\n"
        "} else {\n"
/*11*/  "arena_reset_sp(state->arena, prealloc_idx_%u);\n"
        "}\n",
/*3*/   child_id,
/*4*/   id, 
/*5*/   id, flags_str,
/*6*/   id,
/*7*/   id, id,
/*8*/   id, id,
/*9*/   id,
/*10*/  id, id,
/*11*/  id);
    free(flags_str);
    return;
}

#endif

