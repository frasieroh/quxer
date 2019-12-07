#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_optional(FILE* file, writer_config_t* config, pnode_t* node);

#endif

