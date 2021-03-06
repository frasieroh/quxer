#ifndef RANGE_C
#define RANGE_C

#include <stdlib.h>

#include "templates/range.h"
#include "templates/templates.h"

void write_range(FILE* file, writer_config_t* config, pnode_t* node)
/*
1   if (start_<id> < text_length) {
2       uint8_t c_<id> = text[start_<id>];
3       if (c_<id> >= <low> && c_<id> <= <high>) {
4           result_<id> = malloc(sizeof(rnode_t));
5           result_<id>->flags = <flags_str>
6           result_<id>->type = RANGE_T;
7           result_<id>->start = start_<id>;
8           result_<id>->end = start_<id> + 1;
9           result_<id>->num_children = 0;
10          result_<id>->id = <id>
        }
    }
*/
{
    uint32_t id = node->id;
    range_t* range = node->data.range[0];
    char* flags_str = generate_flags_str(node);
    fprintf(file,
/*1*/   "if (start_%u < text_length) {\n"
/*2*/   "uint8_t c_%u = text[start_%u];\n"
/*3*/   "if (c_%u >= %u && c_%u <= %u) {\n"
/*4*/   "result_%u = malloc(sizeof(rnode_t));\n"
/*5*/   "result_%u->flags = %s"
/*6*/   "result_%u->type = RANGE_T;\n"
/*7*/   "result_%u->start = start_%u;\n"
/*8*/   "result_%u->end = start_%u + 1;\n"
/*9*/   "result_%u->num_children = 0;\n"
/*10*/  "result_%u->id = %u;\n"
        "}\n"
        "}\n",
/*1*/   id,
/*2*/   id, id,
/*3*/   id, range->low, id, range->high,
/*4*/   id,
/*5*/   id, flags_str,
/*6*/   id,
/*7*/   id, id,
/*8*/   id, id,
/*9*/   id,
/*10*/  id, id);
    free(flags_str);
    return;
}

#endif

