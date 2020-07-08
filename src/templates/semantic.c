#ifndef SEMANTIC_C
#define SEMANTIC_C

#include "templates/semantic.h"

static void write_alias_bindings(FILE* file, writer_config_t* config,
        pnode_t* node);

static void write_alias_allocs(FILE* file, writer_config_t* config,
        pnode_t* node);

static void write_alias_frees(FILE* file, writer_config_t* config,
        pnode_t* node);

void write_helper_macros(FILE* file, writer_config_t* config)
{
    fprintf(file,
        "#define c(x) "
            "(((capture_t*)dq_get(context->capture, x))->str)\n"
        "#define s(x) "
            "(((capture_t*)dq_get(context->capture, x))->start)\n"
        "#define e(x) "
            "(((capture_t*)dq_get(context->capture, x))->end)\n"
        "#define ccount (context->capture->len)\n");
    return;
}

void declare_jump_map_fcns(FILE* file, writer_config_t* config,
        pnode_t* node)
/*
    ... for each semantic action under the root pnode_t node:
1   void semantic_action_<id>(context_t* context);
2   void alias_allocs_<id>(context_t* context);
3   void alias_frees_<id>(context_t* context);
*/
{
    if (node->flags & SEMANTIC_ACTION) {
        fprintf(file,
/*1*/       "void semantic_action_%u(context_t* context);\n"
/*2*/       "void alias_allocs_%u(context_t* context);\n"
/*3*/       "void alias_frees_%u(context_t* context);\n",
/*1*/       node->id,
/*2*/       node->id,
/*3*/       node->id);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                declare_jump_map_fcns(file, config, node->data.node[i]);
            }
    }
    return;
}

void write_jump_map_fcns(FILE* file, writer_config_t* config, pnode_t* node)
/*
    ... for each semantic action under the root pnode_t node:
1   void semantic_action_<id>(context_t* context) {
2       <semantic_type> result = NULL;
3       <semantic_type>* <alias1> = context->alias[<id1>]->arr;
        uint32_t count<alias1> = context->alias[<id1>]->len;
        <semantic_type>* <alias2> = context->alias[<id2>]->arr;
        uint32_t count<alias2> = context->alias[<id2>]->len;
        ...
4       <node->code>
        context->result = result;
        return;
    }
5   void alias_allocs_<id>(context_t* context) {
6       context->alias[<id1>] = init_dq(16);
        return;
7   void alias_frees_<id>(context_t* context) {
8       free_dq(context->alias[<id1>];
        return;
*/
{
    if (node->flags & SEMANTIC_ACTION) {
        fprintf(file,
/*1*/       "void semantic_action_%u(context_t* context) {\n"
/*2*/       "%s result = NULL;\n",
/*1*/       node->id,
/*2*/       config->semantic_type);
/*3*/   write_alias_bindings(file, config, node);
        fprintf(file,
/*4*/       "%s\n"
            "context->result = result;\n"
            "return;\n"
            "}\n",
/*4*/       node->code);
        fprintf(file,
/*5*/       "void alias_allocs_%u(context_t* context) {\n",
/*5*/       node->id);
/*6*/   write_alias_allocs(file, config, node);
        fprintf(file,
            "return;\n"
            "}\n");
        fprintf(file,
/*7*/       "void alias_frees_%u(context_t* context) {\n",
/*7*/       node->id);
/*8*/   write_alias_frees(file, config, node);
        fprintf(file,
            "return;\n"
            "}\n");
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                write_jump_map_fcns(file, config, node->data.node[i]);
            }
    }
    return;
}

void write_alias_bindings(FILE* file, writer_config_t* config, pnode_t* node)
{
    if (node->flags & ALIAS) {
        fprintf(file,
            "%s* %s = (%s*)(context->alias[%u]->arr);\n"
            "uint32_t count%s = context->alias[%u]->len;\n",
            config->semantic_type, node->data.string[1],
            config->semantic_type, node->id,
            node->data.string[1], node->id);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                write_alias_bindings(file, config, node->data.node[i]);
            }
    }
    return;
}

void write_alias_allocs(FILE* file, writer_config_t* config,
        pnode_t* node)
{
    if (node->flags & ALIAS) {
        fprintf(file,
            "context->alias[%u] = init_dq(16);\n",
            node->id);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                write_alias_allocs(file, config, node->data.node[i]);
            }
    }
    return;
}

void write_alias_frees(FILE* file, writer_config_t* config,
        pnode_t* node)
{
    if (node->flags & ALIAS) {
        fprintf(file,
            "free_dq(context->alias[%u]);\n",
            node->id);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                write_alias_frees(file, config, node->data.node[i]);
            }
    }
    return;
}

#endif

