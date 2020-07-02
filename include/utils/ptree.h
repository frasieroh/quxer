#ifndef PTREE_H
#define PTREE_H

#include <inttypes.h>

#include "ptype.h"

extern char* ptype_str[];

typedef struct {
    uint8_t* arr;
    uint32_t len;
} bytes_t;

typedef struct {
    uint8_t low;
    uint8_t high;
} range_t;

typedef struct pnode_t_ {
    ptype_t type;
    pnode_flag_t flags;
    uint32_t id;
    uint32_t num_data;
    char* code;
    union data_t_ {
        struct pnode_t_* node[0];
        range_t* range[0];
        bytes_t* bytes[0];
        char* string[0];
    } data;
} pnode_t;

typedef struct {
    pnode_t* root;
    char* name;
} rule_t;

rule_t* init_rule(char* name, pnode_t* root);

// hold pointers to their child parsers in child
pnode_t* seq(uint32_t num_children, pnode_t** children);
pnode_t* alt(uint32_t num_children, pnode_t** children);
pnode_t* star(pnode_t* child);
pnode_t* plus(pnode_t* child);
pnode_t* option(pnode_t* child);
pnode_t* and(pnode_t* child);
pnode_t* not(pnode_t* child);

// holds the exact string that it accepts in string
pnode_t* literal(char* str_bytes);
pnode_t* literal_bytes(uint8_t* bytes, uint32_t len);

// holds the name of the nonterminal it matches in string
pnode_t* nontm(char* name);
pnode_t* aliased_nontm(char* name, char* alias);

// holds a range of uint8_tacters it accepts in range
pnode_t* range(uint8_t low, uint8_t high);

pnode_t* capture(pnode_t* node);
pnode_t* action(pnode_t* node, char* code);

bytes_t* init_bytes(uint8_t* bytes, uint32_t len);
range_t* init_range(uint8_t low, uint8_t high);

void print_bytes(bytes_t* string);
void free_bytes(bytes_t* string);

void free_rule(rule_t* rule);
void print_rule(rule_t* rule);

#endif

