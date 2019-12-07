#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>

#include "utils/grammar.h"

typedef struct {
    char* semantic_type;
    char* header_filename;
    char* source_filename;
} writer_config_t;

writer_config_t* init_config(char* filename, char* semantic_type);
void free_config(writer_config_t* config);

int32_t write_parser(grammar_t* grammar, writer_config_t* config);

#endif

