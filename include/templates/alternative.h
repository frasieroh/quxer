#ifndef ALTERNATIVE_H
#define ALTERNATIVE_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_alternative(FILE* file, writer_config_t* config, pnode_t* node);

#endif

