#ifndef STAR_C
#define STAR_C

#include <stdlib.h>

#include "templates/star.h"
#include "templates/templates.h"

void write_star(FILE* file, writer_config_t* config, pnode_t* node)
    /*
1       uint32_t start_<child_id> = start_<id>;
2       rnode_t* result_<child_id> = NULL;
3       uint32_t num_children_<id> = 0;
4       dyn_arr_t* list_<id> = init_dyn_arr(16);
        do {
5           result_<child_id> = NULL;
            ... child parser ...
6           if (result_<child_id> != NULL) {
7               append_dyn_arr(list_<id>, result_<child id>);
8               start_<child_id> = result_<child_id>->end;
9               ++num_children_<id>;
            }
10      } while (result_<child_id> != NULL);
11      result_<id> = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_<id>);
12      result_<id>->flags = <flags_str>
13      result_<id>->type = STAR_T:
14      result_<id>->start = start_<id>;
15      result_<id>->num_children = num_children_<id>;
16      if (num_children_<id>) {
17          for (uint32 i = 0; i < num_children_<id>; ++i) {
18              result_<id>->children[i] = list_<id>->arr[i];
            }
19          result_<id>->end =
                    ((rnode_t*)list_<id>->arr[num_children_<id> - 1])->end;
        } else {
20          result_<id>->end = start_<id>;
        }
21      result_<id>->id = <id>
22      free_dyn_arr(list_<id>);
    */
{
    uint32_t id = node->id;
    pnode_t* child_node = node->data.node[0];
    uint32_t child_id = child_node->id;
    fprintf(file,
/*1*/   "uint32_t start_%u = start_%u;\n"
/*2*/   "rnode_t* result_%u = NULL;\n"
/*3*/   "uint32_t num_children_%u = 0;\n"
/*4*/   "dyn_arr_t* list_%u = init_dyn_arr(16);\n"
        "do {\n"
/*5*/   "result_%u = NULL;\n",
/*1*/   child_id, id,
/*2*/   child_id,
/*3*/   id,
/*4*/   id,
/*5*/   child_id);
    write_template(file, config, child_node);
    fprintf(file,
/*6*/   "if (result_%u != NULL) {\n"
/*7*/   "    append_dyn_arr(list_%u, result_%u);\n"
/*8*/   "    start_%u = result_%u->end;\n"
/*9*/   "    ++num_children_%u;\n"
        "}\n"
/*10*/  "} while (result_%u != NULL);\n",
/*6*/   child_id,
/*7*/   id, child_id,
/*8*/   child_id, child_id,
/*9*/   id,
/*10*/  child_id);
    char* flags_str = generate_flags_str(node);
    fprintf(file,
/*11*/  "result_%u = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_%u);\n"
/*12*/  "result_%u->flags = %s"
/*13*/  "result_%u->type = STAR_T;\n"
/*14*/  "result_%u->start = start_%u;\n"
/*15*/  "result_%u->num_children = num_children_%u;\n"
/*16*/  "if (num_children_%u) {\n"
/*17*/  "for (uint32_t i = 0; i < num_children_%u; ++i) {\n"
/*18*/  "result_%u->children[i] = list_%u->arr[i];\n"
        "}\n"
/*19*/  "result_%u->end = ((rnode_t*)list_%u->arr[num_children_%u - 1])->end;\n"
        "} else {\n"
/*20*/  "result_%u->end = start_%u;\n"
        "}\n"
/*21*/  "result_%u->id = %u;\n"
/*22*/  "free_dyn_arr(list_%u);\n",
/*11*/  id, id,
/*12*/  id, flags_str,
/*13*/  id,
/*14*/  id, id,
/*15*/  id, id,
/*16*/  id,
/*17*/  id,
/*18*/  id, id,
/*19*/  id, id, id,
/*20*/  id, id,
/*21*/  id, id,
/*22*/  id);
    free(flags_str);
    return;
}

#endif

