#ifndef RANGE_H
#define RANGE_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_range(FILE* file, writer_config_t* config, pnode_t* node);

#endif

