#ifndef AST_C
#define AST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "peg/ast.h"
#include "internal.h"

static ast_node_t* allocate_ast_node(uint32_t num);
uint8_t parse_escape_sequence(
        uint8_t* str, uint32_t len, uint32_t i, uint8_t* res);

ast_node_t* ast_grammar(ast_node_t** ast_rules, uint32_t num)
{
    ast_node_t* ast_node = allocate_ast_node(num);
    ast_node->type = GRAMMAR_T;
    rule_t** rules = malloc(sizeof(rule_t*) * num);
    for (uint32_t i = 0; i < num; ++i) {
        rules[i] = ast_rules[i]->data.rule;
        ast_node->children[i] = ast_rules[i];
    }
    ast_node->data.grammar = init_grammar(num, rules);
    free(rules);
    return ast_node;
}

ast_node_t* ast_rule(uint8_t* name, ast_node_t* body)
{
    ast_node_t* ast_node = allocate_ast_node(1);
    ast_node->type = RULE_T;
    ast_node->data.rule = init_rule((char*)name, body->data.pnode);
    ast_node->children[0] = body;
    return ast_node;
}

ast_node_t* ast_Alt(ast_node_t** first, ast_node_t** rest, uint32_t num)
{
    ast_node_t** ast_buf = malloc(sizeof(ast_node_t*) * num);
    pnode_t** pnode_buf = malloc(sizeof(pnode_t*) * num);
    ast_buf[0] = *first;
    pnode_buf[0] = (*first)->data.pnode;
    for (uint32_t i = 1; i < num; ++i) {
        ast_buf[i] = rest[i-1];
        pnode_buf[i] = rest[i-1]->data.pnode;
    }
    ast_node_t* ast_node = allocate_ast_node(num);
    ast_node->type = PNODE_T;
    if (num > 1) {
        ast_node->data.pnode = Alt(num, pnode_buf);
    } else {
        ast_node->data.pnode = pnode_buf[0];
    }
    for (uint32_t i = 0; i < num; ++i) {
        ast_node->children[i] = ast_buf[i];
    }
    free(ast_buf);
    free(pnode_buf);
    return ast_node;
}

ast_node_t* ast_Seq(ast_node_t** first, ast_node_t** rest, uint32_t num)
{
    ast_node_t** ast_buf = malloc(sizeof(ast_node_t*) * num);
    ast_buf[0] = *first;
    for (uint32_t i = 1; i < num; ++i) {
        ast_buf[i] = rest[i-1];
    }
    dyn_arrt* list = init_dyn_arr(16);
    for (uint32_t i = 0; i < num; ++i) {
        ast_node_t* ast_node = ast_buf[i];
        pnode_t* node = ast_node->data.pnode;
        append_dyn_arr(list, node);
        if (ast_node->code) {
            pnode_t* fragment;
            uint32_t list_len = list->len;
            if (list_len > 1) {
                fragment = Action(
                        Seq(list_len, (pnode_t**)list->arr), ast_node->code);
            } else {
                fragment = Action(get_dyn_arr(list, 0), ast_node->code);
            }

            for (uint32_t j = 0; j < list_len; ++j) {
                pop_dyn_arr(list);
            }
            append_dyn_arr(list, fragment);
        }
    }
    pnode_t* result_pnode;
    if (list->len > 1) {
        uint32_t list_len = list->len;
        result_pnode = Seq(list_len, (pnode_t**)list->arr);
        for (uint32_t j = 0; j < list_len; ++j) {
            pop_dyn_arr(list);
        }
    } else {
        result_pnode = pop_dyn_arr(list);
    }
    free_dyn_arr(list);
    ast_node_t* ast_node = allocate_ast_node(num);
    ast_node->type = PNODE_T;
    ast_node->data.pnode = result_pnode;
    for (uint32_t i = 0; i < num; ++i) {
        ast_node->children[i] = ast_buf[i];
    }
    free(ast_buf);
    return ast_node;
}

ast_node_t* ast_with_code(uint8_t* code, ast_node_t* node)
{
    node->code = malloc(sizeof(char*) * (strlen((char*)code) + 1));
    strcpy(node->code, (char*)code);
    return node;
}

#define AST_CONSTRUCTOR(NAME, TYPE)                \
ast_node_t* NAME(ast_node_t* node)                 \
{                                                  \
    ast_node_t* ast_node = allocate_ast_node(1);   \
    ast_node->type = PNODE_T;                      \
    ast_node->data.pnode = TYPE(node->data.pnode); \
    ast_node->children[0] = node;                  \
    return ast_node;                               \
}                                                  \

AST_CONSTRUCTOR(ast_And, And)

AST_CONSTRUCTOR(ast_Not, Not)

AST_CONSTRUCTOR(ast_Star, Star)

AST_CONSTRUCTOR(ast_Plus, Plus)

AST_CONSTRUCTOR(ast_Option, Option)

ast_node_t* ast_Capture(ast_node_t* node)
{
    Capture(node->data.pnode);
    return node;
}

ast_node_t* ast_AliasedNontm(uint8_t* name, uint8_t* alias)
{
    ast_node_t* ast_node = allocate_ast_node(0);
    ast_node->type = PNODE_T;
    ast_node->data.pnode = AliasedNontm((char*)name, (char*)alias);
    return ast_node;
}

ast_node_t* ast_Nontm(uint8_t* name)
{
    ast_node_t* ast_node = allocate_ast_node(0);
    ast_node->type = PNODE_T;
    ast_node->data.pnode = Nontm((char*)name);
    return ast_node;
}

ast_node_t* ast_Literal(uint8_t* str)
{
    uint32_t len = strlen((char*)str);
    uint32_t true_len = 0;
    uint8_t* buf = malloc(sizeof(uint8_t) * (len + 1));
    for (uint32_t i = 0; i < len; ++i) {
        uint8_t c = 0;
        uint8_t ret = parse_escape_sequence(str, len, i, &c);
        if (ret) {
            buf[true_len++] = c;
            ++i;
        } else {
            buf[true_len++] = str[i];
        }
    }
    buf[true_len] = 0;
    ast_node_t* ast_node = allocate_ast_node(0);
    ast_node->type = PNODE_T;
    ast_node->data.pnode = LiteralBytes(buf, true_len);
    free(buf);
    return ast_node;
}

ast_node_t* ast_CClass(uint8_t* str)
{
    uint32_t len = strlen((char*)str);
    dyn_arrt* list = init_dyn_arr(16);
    for (uint32_t i = 0; i < len; ++i) {
        uint8_t c1 = 0;
        uint8_t ret = parse_escape_sequence(str, len, i, &c1);
        // if escape sequence, advance i an extra character
        if (ret) {
            ++i;
        } else {
            c1 = str[i];
            if (c1 == '-') {
                printf("Unescaped range delimiter: %s\n", str);
                exit(EXIT_FAILURE);
            }
        }
        if (i < len - 2 && str[i + 1] == '-') {
            uint8_t c2 = 0;
            ret = parse_escape_sequence(str, len, i + 2, &c2);
            // advance extra character 
            if (ret) {
                ++i;
            } else {
                c2 = str[i+2];
                if (c2 == '-') {
                    printf("Unescaped range delimiter: %s\n", str);
                    exit(EXIT_FAILURE);
                }
            }
            if (c1 < c2) {
                append_dyn_arr(list, Range(c1, c2));
            } else {
                append_dyn_arr(list, Range(c2, c1));
            }
            i = i + 2; // consumed 2 additional characters
        } else {
            append_dyn_arr(list, LiteralBytes(&c1, 1));
        }
    }
    ast_node_t* ast_node = allocate_ast_node(0);
    ast_node->type = PNODE_T;
    ast_node->data.pnode = Alt(list->len, (pnode_t**)(list->arr));
    free_dyn_arr(list);
    return ast_node;
}

ast_node_t* ast_dot()
{
    ast_node_t* ast_node = allocate_ast_node(0);
    ast_node->type = PNODE_T;
    ast_node->data.pnode = Range(0, 255);
    return ast_node;
}

void free_ast(ast_node_t* node)
{
    for (uint32_t i = 0; i < node->num_children; ++i) {
        free_ast(node->children[i]);
    }
    if (node->code) {
        free(node->code);
    }
    free(node);
}

ast_node_t* allocate_ast_node(uint32_t num)
{
    ast_node_t* ast_node =
            malloc(sizeof(ast_node_t) + sizeof(ast_node_t*) * num);
    ast_node->num_children = num;
    ast_node->code = NULL;
    return ast_node;
}

uint8_t parse_escape_sequence(
        uint8_t* str, uint32_t len, uint32_t i, uint8_t* res)
{
    if (str[i] == '\\') {
        if (i < len - 1) {
            switch(str[i+1]) {
                case 'r':
                    *res = '\r';
                    return 1;
                case 'n':
                    *res = '\n';
                    return 1;
                case 't':
                    *res = '\t';
                    return 1;
                case '?':
                    *res = '\?';
                    return 1;
                case '\"':
                    *res = '\"';
                    return 1;
                case '\'':
                    *res = '\'';
                    return 1;
                case '\0':
                    *res = '\0';
                    return 1;
                case '\\':
                    *res = '\\';
                    return 1;
                case '-':
                    *res = '-';
                    return 1;
                default:
                    printf("Undefined escape sequence: \\%c\n", str[i+1]);
                    exit(EXIT_FAILURE);
            }
        } else {
            printf("Improperly placed backslash: %s\n", str);
            exit(EXIT_FAILURE);
        }
    } else {
        return 0;
    }
}

#endif

