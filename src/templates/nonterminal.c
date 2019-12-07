#ifndef NONTERMINAL_C
#define NONTERMINAL_C

#include <stdlib.h>

#include "templates/nonterminal.h"
#include "templates/templates.h"

void write_nonterminal(FILE* file, writer_config_t* config, pnode_t* node)
/*
1   rnode_t* result_<id>_nt = call_eval(EVAL_%s, state, text, text_length, start_%u);
2   if (result_<id>_nt) {
3       result_<id> = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
4       result_<id>->flags = <flags_str>
5       result_<id>->type = NONTERMINAL_T;
6       result_<id>->start = start_<id>;
7       result_<id>->end = result_<id>_nt->end;
8       result_<id>->num_children = 1;
9       result_<id>->children[0] = result_<id>_nt;
10      result_<id>->id = <id>;
    }
*/
{
    uint32_t id = node->id;
    char* name = node->data.string[0];
    char* flags_str = generate_flags_str(node);
    fprintf(file,
/*1*/   "rnode_t* result_%u_nt = call_eval(EVAL_%s, state, text, text_length,"
                " start_%u);\n"
/*2*/   "if (result_%u_nt) {\n"
/*3*/   "result_%u = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);\n"
/*4*/   "result_%u->flags = %s"
/*5*/   "result_%u->type = NONTERMINAL_T;\n"
/*6*/   "result_%u->start = start_%u;\n"
/*7*/   "result_%u->end = result_%u_nt->end;\n"
/*8*/   "result_%u->num_children = 1;\n"
/*9*/   "result_%u->children[0] = result_%u_nt;\n"
/*10*/  "result_%u->id = %u;\n"
        "}\n",
/*1*/   id, name, id,
/*2*/   id,
/*3*/   id,
/*4*/   id, flags_str,
/*5*/   id,
/*6*/   id, id,
/*7*/   id, id,
/*8*/   id,
/*9*/   id, id,
/*10*/  id, id);
    free(flags_str);
    return;
}

#endif

