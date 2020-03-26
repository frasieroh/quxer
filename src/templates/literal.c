#ifndef LITERAL_C
#define LITERAL_C

#include <stdlib.h>
#include <string.h>

#include "templates/literal.h"
#include "templates/templates.h"

static char* generate_bytesbuf_string(pnode_t* node);

void write_literal(FILE* file, writer_config_t* config, pnode_t* node)
    /*
0       arena_idx_t prealloc_idx_<id> = arena_prealloc(state->arena);
1       uint8_t bytesbuf_<id>[] = {...}; // charbuf string
2       uint8_t c_<id>;
3       for (uint32_t i_<id> = 0; i_<id> < <len>; ++i_<id>) {
4           c_<id> = bytesbuf_<id>[i_<id>];
5           if (i_<id> + start_<id> < text_length
6                   && c_<id> == text[i_<id> + start_<id>]) {
7               if (i_<id> == <len> - 1) {
8                   result_<id> = arena_malloc(state->arena, prealloc_idx_<id>,
                        sizeof(rnode_t));
9                   result_<id>->flags = <flags_str>
10                  result_<id>->type = LITERAL_T;
11                  result_<id>->start = start_<id>;
12                  result_<id>->end = start_<id> + <len>;
13                  result_<id>->num_children = 0;
14                  result_<id>->id = <id>;
                }
            } else {
15              arena_reset_sp(state->arena, prealloc_idx_<id>);
                break;
            }
        }
    */
{
    uint32_t id = node->id;
    bytes_t* bytes = node->data.bytes[0];
    char* bytesbuf_str = generate_bytesbuf_string(node);
    char* flags_str = generate_flags_str(node);
    fprintf(file,
/*0*/   "arena_idx_t prealloc_idx_%u = arena_prealloc(state->arena);\n"
/*1*/   "%s"
/*2*/   "uint8_t c_%u;\n"
/*3*/   "for (uint32_t i_%u = 0; i_%u < %u; ++i_%u) {\n"
/*4*/   "c_%u = bytesbuf_%u[i_%u];\n"
/*5*/   "if (i_%u + start_%u < text_length\n"
/*6*/   "    && c_%u == text[i_%u + start_%u]) {\n"
/*7*/   "if (i_%u == %u - 1) {\n"
/*8*/   "result_%u = arena_malloc(state->arena, prealloc_idx_%u, "
                "sizeof(rnode_t));\n"
/*9*/   "result_%u->flags = %s"
/*10*/  "result_%u->type = LITERAL_T;\n"
/*11*/  "result_%u->start = start_%u;\n"
/*12*/  "result_%u->end = start_%u + %u;\n"
/*13*/  "result_%u->num_children = 0;\n"
/*14*/  "result_%u->id = %u;\n"
        "}\n"
        "} else {\n"
/*15*/  "arena_reset_sp(state->arena, prealloc_idx_%u);\n"
        "break;\n"
        "}\n"
        "}\n",
/*0*/   id,
/*1*/   bytesbuf_str,
/*2*/   id,
/*3*/   id, id, bytes->len, id,
/*4*/   id, id, id,
/*5*/   id, id,
/*6*/   id, id, id,
/*7*/   id, bytes->len,
/*8*/   id, id,
/*9*/   id, flags_str,
/*10*/  id,
/*11*/  id, id,
/*12*/  id, id, bytes->len,
/*13*/  id,
/*14*/  id, id,
/*15*/  id);
    free(bytesbuf_str);
    free(flags_str);
    return;
}

char* generate_bytesbuf_string(pnode_t* node)
{
    char buf[128];
    bytes_t* bytes = node->data.bytes[0];
    uint32_t id = node->id;
    char* result = calloc(sizeof(char), 1);
    sprintf(buf, "uint8_t bytesbuf_%u[] = {", id);
    append_str(buf, &result);
    for (uint32_t i = 0; i < bytes->len; ++i) {
        sprintf(buf, "%u, ", bytes->arr[i]);
        append_str(buf, &result);
    }
    append_str("};\n", &result);
    return result;
}

#endif

