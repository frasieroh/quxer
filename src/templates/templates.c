#ifndef TEMPLATES_C
#define TEMPLATES_C

#include <stdlib.h>
#include <string.h>

#include "templates/templates.h"
#include "templates/sequence.h"
#include "templates/alternative.h"
#include "templates/star.h"
#include "templates/plus.h"
#include "templates/optional.h"
#include "templates/and.h"
#include "templates/not.h"
#include "templates/range.h"
#include "templates/literal.h"
#include "templates/nonterminal.h"

void write_template(FILE* file, writer_config_t* config, pnode_t* node)
{
    switch(node->type) {
        case SEQUENCE_T: write_sequence(file, config, node); break;
        case ALTERNATIVE_T: write_alternative(file, config, node); break;
        case STAR_T: write_star(file, config, node); break;
        case PLUS_T: write_plus(file, config, node); break;
        case OPTIONAL_T: write_optional(file, config, node); break;
        case AND_T: write_and(file, config, node); break;
        case NOT_T: write_not(file, config, node); break;
        case RANGE_T: write_range(file, config, node); break;
        case LITERAL_T: write_literal(file, config, node); break;
        case NONTERMINAL_T: write_nonterminal(file, config, node); break;
    }
    return;
}

char* generate_flags_str(pnode_t* node)
{
    char buf[128];
    char* result = calloc(sizeof(char), 1);
    if (node->flags & DO_CAPTURE) {
        strcpy(buf, "DO_CAPTURE | ");
        append_str(buf, &result);
    }
    if (node->flags & SEMANTIC_ACTION) {
        strcpy(buf, "SEMANTIC_ACTION | ");
        append_str(buf, &result);
    }
    if (node->flags & ALIAS) {
        strcpy(buf, "ALIAS | ");
        append_str(buf, &result);
    }
    append_str("0;\n", &result);
    return result;
}

void append_str(char* buf, char** result)
{
    *result = realloc(
            *result, sizeof(char) * (strlen(*result) + strlen(buf) + 1));
    strcat(*result, buf);
    return;
}

#endif

