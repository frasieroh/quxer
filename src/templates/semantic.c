#ifndef SEMANTIC_C
#define SEMANTIC_C

#include "templates/semantic.h"

static void write_alias_bindings(FILE* file, writer_config_t* config,
        pnode_t* node);

void write_helper_macros(FILE* file, writer_config_t* config)
{
    fprintf(file,
        "#define c(x) "
            "(((capture_t*)get_stack(context->capture, x))->str)\n"
        "#define s(x) "
            "(((capture_t*)get_stack(context->capture, x))->start)\n"
        "#define e(x) "
            "(((capture_t*)get_stack(context->capture, x))->end)\n"
        "#define ccount (context->capture->len)\n");
    return;
}

void write_num_nodes(FILE* file, writer_config_t* config, grammar_t* grammar)
{
    fprintf(file,
        "uint32_t num_nodes = %u;\n",
        grammar->num_nodes);
    return;
}

void declare_semantic_actions(FILE* file, writer_config_t* config,
        pnode_t* node)
/*
    ... for each semantic action under the root pnode_t node:
1   void semantic_action_<id>(context_t* context);
*/
{
    if (node->flags & SEMANTIC_ACTION) {
        fprintf(file,
/*1*/       "void semantic_action_%u(context_t* context);\n",
/*1*/       node->id);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                declare_semantic_actions(file, config, node->data.node[i]);
            }
    }
    return;
}
void write_semantic_actions(FILE* file, writer_config_t* config,
        pnode_t* node)
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
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                write_semantic_actions(file, config, node->data.node[i]);
            }
    }
    return;
}

void write_alias_bindings(FILE* file, writer_config_t* config, pnode_t* node)
{
    if (node->flags & ALIAS) {
        fprintf(file,
            "%s* %s = "
                "(%s*)(context->alias[%u]->arr);\n"
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

#endif

