#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_nonterminal(FILE* file, writer_config_t* config, pnode_t* node);

#endif

