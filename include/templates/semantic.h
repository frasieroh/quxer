#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_helper_macros(FILE* file, writer_config_t* config);

void write_num_nodes(FILE* file, writer_config_t* config, grammar_t* grammar);

void declare_semantic_actions(FILE* file, writer_config_t* config,
        pnode_t* node);

void write_semantic_actions(FILE* file, writer_config_t* config,
        pnode_t* node);

#endif

