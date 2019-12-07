#ifndef RULE_H
#define RULE_H

#include <stdio.h>

#include "utils/writer.h"
#include "utils/ptree.h"

void declare_rule(FILE* file, writer_config_t* config, rule_t* rule);
void write_rule(FILE* file, writer_config_t* config, rule_t* rule);

#endif

