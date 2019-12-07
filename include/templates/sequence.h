#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_sequence(FILE* file, writer_config_t* config, pnode_t* node);

#endif

