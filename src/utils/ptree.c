#ifndef PTREE_C
#define PTREE_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/ptree.h"

static pnode_t* allocate_pnode(uint32_t num_data);
static void free_rule_recursive(pnode_t* node);
static void print_rule_recursive(pnode_t* node, uint32_t depth);

char* ptype_str[] = {
    "SEQUENCE_T",    
    "ALTERNATIVE_T", 
    "STAR_T",
    "PLUS_T",
    "OPTIONAL_T",
    "AND_T",
    "NOT_T",
    "RANGE_T",
    "LITERAL_T",
    "NONTERMINAL_T"
};

rule_t* init_rule(char* name, pnode_t* root)
{
    rule_t* rule = malloc(sizeof(rule_t));
    rule->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(rule->name, name);
    rule->root = root;
    return rule;
}

#define MANY_CONSTRUCTOR(NAME, TYPE)                     \
pnode_t* NAME(uint32_t num_children, pnode_t** children) \
{                                                        \
    pnode_t* node = allocate_pnode(num_children);        \
    node->type = TYPE;                                   \
    node->flags = 0;                                     \
    node->code = NULL;                                   \
    for (uint32_t i = 0; i < num_children; ++i) {        \
        node->data.node[i] = children[i];                \
    }                                                    \
    return node;                                         \
}

MANY_CONSTRUCTOR(Seq, SEQUENCE_T)

MANY_CONSTRUCTOR(Alt, ALTERNATIVE_T)

#define UNARY_CONSTRUCTOR(NAME, TYPE)   \
pnode_t* NAME(pnode_t* child)           \
{                                       \
    pnode_t* node = allocate_pnode(1);  \
    node->type = TYPE;                  \
    node->flags = 0;                    \
    node->code = NULL;                  \
    node->data.node[0] = child;         \
    return node;                        \
}

UNARY_CONSTRUCTOR(Star, STAR_T)

UNARY_CONSTRUCTOR(Plus, PLUS_T)

UNARY_CONSTRUCTOR(Option, OPTIONAL_T)

UNARY_CONSTRUCTOR(And, AND_T)

UNARY_CONSTRUCTOR(Not, NOT_T)

pnode_t* Literal(char* str_bytes)
{
    return LiteralBytes((uint8_t*)str_bytes, strlen(str_bytes));
}

pnode_t* LiteralBytes(uint8_t* bytes, uint32_t len) 
{                                            
    bytes_t* bytes_ret = init_bytes(bytes, len);
    pnode_t* node = allocate_pnode(1);
    node->type = LITERAL_T;
    node->flags = 0;
    node->code = NULL;
    node->data.bytes[0] = bytes_ret;
    return node;
} 

pnode_t* Nontm(char* name)
{
    pnode_t* node = allocate_pnode(1);
    node->type = NONTERMINAL_T;
    node->flags = 0;
    node->code = NULL;
    node->data.string[0] = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(node->data.string[0], name);
    return node;
}

pnode_t* AliasedNontm(char* name, char* alias)
{
    pnode_t* node = allocate_pnode(2);
    node->type = NONTERMINAL_T;
    node->flags = ALIAS;
    node->code = NULL;
    node->data.string[0] = malloc(sizeof(char) * (strlen(name) + 1));
    node->data.string[1] = malloc(sizeof(char) * (strlen(alias) + 1));
    strcpy(node->data.string[0], name);
    strcpy(node->data.string[1], alias);
    return node;
}

pnode_t* Range(uint8_t low, uint8_t high)
{
    range_t* range = init_range(low, high);
    pnode_t* node = allocate_pnode(1);
    node->type = RANGE_T;
    node->flags = 0;
    node->code = NULL;
    node->data.range[0] = range;
    return node;
}

pnode_t* Capture(pnode_t* node)
{
    node->flags |= DO_CAPTURE;
    return node;
}

pnode_t* Action(pnode_t* node, char* code)
{
    node->flags |= SEMANTIC_ACTION;
    node->code = malloc(sizeof(char) * (strlen(code) + 1));
    strcpy(node->code, code);
    return node;
}

bytes_t* init_bytes(uint8_t* bytes, uint32_t len)
{
    bytes_t* bytes_ret = malloc(sizeof(bytes_t));
    uint8_t* arr = malloc(sizeof(uint8_t) * (len + 1));
    for (uint32_t i = 0; i < len; ++i) {
        arr[i] = bytes[i];
    }
    arr[len] = 0; // null terminator
    bytes_ret->arr = arr;
    bytes_ret->len = len;
    return bytes_ret;
}

range_t* init_range(uint8_t low, uint8_t high)
{
    range_t* range = malloc(sizeof(range));
    range->low = low;
    range->high = high;
    return range;
}

void free_bytes(bytes_t* bytes)
{
    free(bytes->arr);
    free(bytes);
    return;
}

void free_rule(rule_t* rule)
{
    free_rule_recursive(rule->root);
    free(rule->name);
    free(rule);
    return;
}

void print_rule(rule_t* rule)
{
    print_rule_recursive(rule->root, 0);
    return;
}

pnode_t* allocate_pnode(uint32_t num_data)
{
    pnode_t* node = malloc(sizeof(pnode_t) + sizeof(void*) * num_data);
    node->num_data = num_data;
    return node;
}

void free_rule_recursive(pnode_t* node)
{
    switch (node->type) {
        case LITERAL_T:
            free_bytes(node->data.bytes[0]);
            break;
        case NONTERMINAL_T:
            free(node->data.string[0]);
            if (node->flags & ALIAS) {
                free(node->data.string[1]);
            }
            break;
        case RANGE_T:
            free(node->data.range[0]);
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                free_rule_recursive(node->data.node[i]);
            }
    }
    if (node->flags & SEMANTIC_ACTION) {
        free(node->code);
    }
    free(node);
    return;
}

void print_rule_recursive(pnode_t* node, uint32_t depth)
{
    #define PRINT_INDENT(DEPTH) \
    printf("%*c", DEPTH, ' ');
    PRINT_INDENT(depth)
    printf("type: %s\n", ptype_str[node->type]);
    if (node->flags & SEMANTIC_ACTION) {
        PRINT_INDENT(depth)
        printf("action: %s\n", node->code);
    }
    switch(node->type) {
        case LITERAL_T:
            PRINT_INDENT(depth)
            printf("literal: %s\n", (char*)node->data.bytes[0]->arr);
            break;
        case NONTERMINAL_T:
            PRINT_INDENT(depth)
            printf("rule: %s\n", node->data.string[0]);
            if (node->flags & ALIAS) {
                PRINT_INDENT(depth)
                printf("alias: %s\n", node->data.string[1]);
            }
            break;
        case RANGE_T:
            PRINT_INDENT(depth)
            range_t* r = node->data.range[0];
            printf("range: %c to %c\n", r->low, r->high);
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                print_rule_recursive(node->data.node[i], depth + 4);
            }
    }
    return;
}

#endif

