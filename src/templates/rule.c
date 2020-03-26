#ifndef RULE_C
#define RULE_C

#include "templates/templates.h"
#include "templates/rule.h"

void declare_rule(FILE* file, writer_config_t* config, rule_t* rule)
/*
1   void eval_<name>(memo_state_t* state, char* text,
                       uint32_t text_length, uint32_t pos);
*/
{
    char* name = rule->name;
    fprintf(file,
/*1*/   "void eval_%s(memo_state_t* state, uint8_t* text, "
                "uint32_t text_length, uint32_t pos, eval_return_t* ret);\n",
/*1*/   name);
    return;
}

void write_rule(FILE* file, writer_config_t* config, rule_t* rule)
/*
1   void eval_<name>(memo_state_t* state, char* text,
            uint32_t text_length, uint32_t pos, eval_return_t* ret) {
2       uint32_t start_<root id> = pos;
3       rnode_t* result_<root_id> = NULL;
        // child parser
4       ret->prealloc = prealloc_idx_<root_id>;
5       ret->alloc = result_<root_id>;
        return;
    }
*/
{
    uint32_t root_id = rule->root->id;
    char* name = rule->name;
    fprintf(file,
/*1*/   "void eval_%s(memo_state_t* state, uint8_t* text, "
                "uint32_t text_length, uint32_t pos, eval_return_t* ret) {\n"
/*2*/   "uint32_t start_%u = pos;\n"
/*3*/   "rnode_t* result_%u = NULL;\n",
/*1*/   name,
/*2*/   root_id,
/*3*/   root_id);
    write_template(file, config, rule->root);
    fprintf(file,
/*4*/   "ret->prealloc = prealloc_idx_%u;\n"
/*5*/   "ret->alloc = result_%u;\n"
        "return;\n"
        "}\n",
/*4*/    root_id,
/*5*/    root_id);
    return;
}

#endif

