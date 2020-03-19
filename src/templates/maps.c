#ifndef EVALMAP_C
#define EVALMAP_C

#include <stdlib.h>
#include <string.h>

#include <templates/maps.h>
#include <templates/templates.h>

static char* generate_nt_defs(grammar_t* grammar);
static char* generate_eval_map_str(grammar_t* grammar);
static char* generate_name_map_str(grammar_t* grammar);
static char* generate_action_map_str(grammar_t* grammar);
static char* generate_action_map_str_recursive(pnode_t* node);
static char* generate_alias_allocs_map_str(grammar_t* grammar);
static char* generate_alias_allocs_map_str_recursive(pnode_t* node);

void write_maps(FILE* file, writer_config_t* config, grammar_t* grammar)
/*
1   #define EVAL_<rule 1> 0
    #define EVAL_<rule 2> 1
    ...
2   evalfcn_t eval_map = {<rule 1>, <rule 2> ... };
3   char* name_map = {"rule 1", "rule 2", ...};
4   uint32_t num_rules = <num_rules>;
5   actionfcn_t semantic_action_map[<num_nodes>] = 
        {[<id1>] = semantic_action<id1>, [<id2>] = semantic_action_<id2> ...};
    ...
6   uint32_t num_nodes = <num_nodes>;
7   aliasallocsfcn_t alias_allocs_map[<num_nodes>] =
        {[<id1>] = alias_allocs_<id1>, ... };
*/
{
    char* nt_defs = generate_nt_defs(grammar);
    char* eval_map_str = generate_eval_map_str(grammar);
    char* name_map_str = generate_name_map_str(grammar);
    char* action_map_str = generate_action_map_str(grammar);
    char* alias_allocs_str = generate_alias_allocs_map_str(grammar);
    fprintf(file,
/*1*/   "%s"
/*2*/   "%s"
/*3*/   "%s"
/*4*/   "uint32_t num_rules = %u;\n"
/*5*/   "%s"
/*6*/   "uint32_t num_nodes = %u;\n"
/*7*/   "%s",
/*1*/   nt_defs,
/*2*/   eval_map_str,
/*3*/   name_map_str,
/*4*/   grammar->num_rules,
/*5*/   action_map_str,
/*6*/   grammar->num_nodes,
/*7*/   alias_allocs_str);
    free(nt_defs);
    free(eval_map_str);
    free(name_map_str);
    free(action_map_str);
    free(alias_allocs_str);
    return;
}

char* generate_nt_defs(grammar_t* grammar)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        sprintf(buf, "#define EVAL_%s %u\n", grammar->rules[i]->name, i);
        append_str(buf, &result);
    }
    return result;
}

char* generate_eval_map_str(grammar_t* grammar)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    append_str("evalfcn_t eval_map[] = {", &result);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        sprintf(buf, "eval_%s, ", grammar->rules[i]->name);
        append_str(buf, &result);
    }
    append_str("};\n", &result);
    return result;
}
    
char* generate_name_map_str(grammar_t* grammar)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    append_str("char* name_map[] = {", &result);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        sprintf(buf, "\"%s\", ", grammar->rules[i]->name);
        append_str(buf, &result);
    }
    append_str("};\n", &result);
    return result;
}

char* generate_action_map_str(grammar_t* grammar)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    sprintf(buf, "actionfcn_t semantic_action_map[%u] = {", grammar->num_nodes);
    append_str(buf, &result);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        char* rule_i_segment = generate_action_map_str_recursive(
                grammar->rules[i]->root);
        append_str(rule_i_segment, &result);
        free(rule_i_segment);
    }
    append_str("};\n", &result);
    return result;
}
    
char* generate_action_map_str_recursive(pnode_t* node)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    if (node->flags & SEMANTIC_ACTION) {
        sprintf(buf, "[%u] = semantic_action_%u, ",
            node->id, node->id);
        append_str(buf, &result);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                char* inner_result = generate_action_map_str_recursive(
                        node->data.node[i]);
                append_str(inner_result, &result);
                free(inner_result);
            }
    }
    return result;
}

char* generate_alias_allocs_map_str(grammar_t* grammar)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    sprintf(buf, "aliasallocsfcn_t alias_allocs_map[%u] = {",
            grammar->num_nodes);
    append_str(buf, &result);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        char* rule_i_segment = generate_alias_allocs_map_str_recursive(
                grammar->rules[i]->root);
        append_str(rule_i_segment, &result);
        free(rule_i_segment);
    }
    append_str("};\n", &result);
    return result;
}
    
char* generate_alias_allocs_map_str_recursive(pnode_t* node)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    if (node->flags & SEMANTIC_ACTION) {
        sprintf(buf, "[%u] = alias_allocs_%u, ",
            node->id, node->id);
        append_str(buf, &result);
    }
    switch (node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                char* inner_result = generate_alias_allocs_map_str_recursive(
                        node->data.node[i]);
                append_str(inner_result, &result);
                free(inner_result);
            }
    }
    return result;
}

#endif

