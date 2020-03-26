#ifndef OPTIONAL_C
#define OPTIONAL_C

#include <stdlib.h>

#include "templates/optional.h"
#include "templates/templates.h"

void write_optional(FILE* file, writer_config_t* config, pnode_t* node)
/*
0   void* prealloc_idx_<id> = arena_prealloc(state->arena);
1   uint32_t start_<child_id> = start_<id>;
2   rnode_t* result_<child_id> = NULL;
    ... child parser ...
3   if (result_<child_id>) {
4       result_<id> = arena_malloc(state->arena, 
                sizeof(rnode_t) + sizeof(rnode_t*));
5       result_<id>->end = result_<child_id>->end;
6       result_<id>->num_children = 1;
7       result_<id>->children[0] = result_<child_id>
    } else {
8       result_<id> = arena_malloc(state->arena,
                sizeof(rnode_t));
9       result_<id>->end = start_<id>;
10      result_<id>->num_children = 0;
    }
11  result_<id>->type = OPTIONAL_T;
12  result_<id>->flags = <flags_str>;
13  result_<id>->start = start_<id>;
14  result_<id>->id = <id>
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
/*3*/   "if (result_%u) {\n"
/*4*/   "result_%u = arena_malloc(state->arena, "
                "sizeof(rnode_t) + sizeof(rnode_t*));\n"
/*5*/   "result_%u->end = result_%u->end;\n"
/*6*/   "result_%u->num_children = 1;\n"
/*7*/   "result_%u->children[0] = result_%u;\n"
        "} else {\n"
/*8*/   "result_%u = arena_malloc(state->arena, "
                "sizeof(rnode_t));\n"
/*9*/   "result_%u->end = start_%u;\n"
/*10*/  "result_%u->num_children = 0;\n"
        "}\n"
/*11*/  "result_%u->type = OPTIONAL_T;\n"
/*12*/  "result_%u->flags = %s"
/*13*/  "result_%u->start = start_%u;\n"
/*14*/  "result_%u->id = %u;\n",
/*3*/   child_id,
/*4*/   id,
/*5*/   id, child_id,
/*6*/   id,
/*7*/   id, child_id,
/*8*/   id,
/*9*/   id, id,
/*10*/  id,
/*11*/  id,
/*12*/  id, flags_str,
/*13*/  id, id,
/*14*/  id, id);
    free(flags_str);
    return;
}

#endif

