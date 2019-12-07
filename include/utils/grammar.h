#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "utils/ptree.h"

typedef struct {
    uint32_t num_rules;
    uint32_t num_nodes;
    rule_t* rules[0];
} grammar_t;

grammar_t* init_grammar(uint32_t num_rules, rule_t** rules);
void free_grammar(grammar_t* grammar);
void print_grammar(grammar_t* grammar);

#endif

