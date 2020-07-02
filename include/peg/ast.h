#ifndef AST_H
#define AST_H

#include "utils/grammar.h"

typedef enum {
    PNODE_T,
    RULE_T,
    GRAMMAR_T
} ast_type_t;

typedef struct ast_node_t_ {
    ast_type_t type;
    union {
        pnode_t* pnode;
        rule_t* rule;
        grammar_t* grammar;
    } data;
    char* code;
    uint32_t num_children;
    struct ast_node_t_* children[0];
} ast_node_t;

ast_node_t* ast_grammar(ast_node_t** ast_rules, uint32_t num);
ast_node_t* ast_rule(uint8_t* name, ast_node_t* body);
ast_node_t* ast_alt(ast_node_t** first, ast_node_t** rest, uint32_t num);
ast_node_t* ast_seq(ast_node_t** first, ast_node_t** rest, uint32_t num);
ast_node_t* ast_with_code(uint8_t* code, ast_node_t* node);
ast_node_t* ast_and(ast_node_t* node);
ast_node_t* ast_not(ast_node_t* node);
ast_node_t* ast_star(ast_node_t* node);
ast_node_t* ast_plus(ast_node_t* node);
ast_node_t* ast_option(ast_node_t* node);
ast_node_t* ast_capture(ast_node_t* node);
ast_node_t* ast_aliased_nontm(uint8_t* name, uint8_t* alias);
ast_node_t* ast_nontm(uint8_t* name);
ast_node_t* ast_literal(uint8_t* str);
ast_node_t* ast_cclass(uint8_t* str);
ast_node_t* ast_dot();

void free_ast(ast_node_t* node);

#endif

