#ifndef WRITERS_H
#define WRITERS_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_template(FILE* file, writer_config_t* config, pnode_t* node);

void append_str(char* buf, char** result);

char* generate_flags_str(pnode_t* node);

#endif

