#ifndef EVALMAP_H
#define EVALMAP_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void write_maps(FILE* file, writer_config_t* config, grammar_t* grammar);

#endif

