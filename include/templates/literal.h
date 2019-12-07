#ifndef LITERAL_H
#define LITERAL_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_literal(FILE* file, writer_config_t* config, pnode_t* node);

#endif

