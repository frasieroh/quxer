#ifndef ALTERNATIVE_C
#define ALTERNATIVE_C

#include <stdlib.h>

#include "templates/alternative.h"
#include "templates/templates.h"

void write_alternative(FILE* file, writer_config_t* config, pnode_t* node)
    /*
        // for every child:
1       uint32_t start_<child_id> = start_<id>;
2       rnode_t* result_<child_id> = NULL;
        ... child parser ...
3       if (result_<child_id> != NULL) {
4           result_<id> = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
5           result_<id>->flags = <flags_str>;
6           result_<id>->type = ALTERNATIVE_T;
7           result_<id>->start = start_<id>;
8           result_<id>->end = result_<child_id>->end;
9           result_<id>->num_children = 1;
10          result_<id>->children[0] = result_<child_id>;
11          result_<id>->id = <id>;
12          goto exit_<id>;
        }
        // after
13      exit_<id>:
    */
{
    uint32_t id = node->id;
    pnode_t* child_node;
    uint32_t child_id;
    for (uint32_t i = 0; i < node->num_data; ++i) {
        child_node = node->data.node[i];
        child_id = child_node->id;
        fprintf(file,
/*1*/       "uint32_t start_%u = start_%u;\n"
/*2*/       "rnode_t* result_%u = NULL;\n",
/*1*/       child_id, id,
/*2*/       child_id);
        write_template(file, config, child_node);
        char* flags_str = generate_flags_str(node);
        fprintf(file,
/*3*/       "if (result_%u != NULL) {\n"
/*4*/       "result_%u = malloc(sizeof(rnode_t) + sizeof(rnode_t*));\n"
/*5*/       "result_%u->flags = %s"
/*6*/       "result_%u->type = ALTERNATIVE_T;\n"
/*7*/       "result_%u->start = start_%u;\n"
/*8*/       "result_%u->end = result_%u->end;\n"
/*8*/       "result_%u->num_children = 1;\n"
/*10*/      "result_%u->children[0] = result_%u;\n"
/*11*/      "result_%u->id = %u;\n"
/*12*/      "goto exit_%u;\n"
            "}\n",
/*3*/       child_id,
/*4*/       id,
/*5*/       id, flags_str,
/*6*/       id,
/*7*/       id, id,
/*8*/       id, child_id,
/*9*/       id,
/*10*/      id, child_id,
/*11*/      id, id,
/*12*/      id);
        free(flags_str);
    }
    fprintf(file,
/*13*/  "exit_%u:\n",
/*13*/  id);
    return;
}

#endif

