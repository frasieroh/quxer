#ifndef GRAMMAR_C
#define GRAMMAR_C

#include <stdlib.h>
#include <stdio.h>

#include "utils/grammar.h"

grammar_t* init_grammar(uint32_t num_rules, rule_t** rules)
{
    grammar_t* grammar = malloc(sizeof(grammar_t) + sizeof(rule_t*) * num_rules);
    grammar->num_rules = num_rules;
    for (uint32_t i = 0; i < num_rules; ++i) {
        grammar->rules[i] = rules[i];
    }
    return grammar;
}

void free_grammar(grammar_t* grammar)
{
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        free_rule(grammar->rules[i]);
    }
    free(grammar);
    return;
}

void print_grammar(grammar_t* grammar)
{
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        printf("rule: %s\n", grammar->rules[i]->name);
        print_rule(grammar->rules[i]);
    }
    return;
}

#endif

