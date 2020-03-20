#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_helper_macros(FILE* file, writer_config_t* config);

void declare_jump_map_fcns(FILE* file, writer_config_t* config, pnode_t* node);

void write_jump_map_fcns(FILE* file, writer_config_t* config, pnode_t* node);

#endif

