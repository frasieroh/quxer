#ifndef WRITER_C
#define WRITER_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "utils/writer.h"
#include "templates/rule.h"
#include "templates/maps.h"
#include "templates/semantic.h"

static void set_ids(grammar_t* grammar);
static void set_ids_recursive(grammar_t* grammar, pnode_t* node);
static int32_t open_file(char* filename, FILE** file);
static int32_t close_file(char* filename, FILE* file);
static void write_header(FILE* file, writer_config_t* config,
        grammar_t* grammar);
static void write_source(FILE* file, writer_config_t* config,
        grammar_t* grammar);

writer_config_t* init_config(char* filename, char* semantic_type)
{
    writer_config_t* config = malloc(sizeof(writer_config_t));
    config->header_filename = malloc(sizeof(char) * (strlen(filename) + 3));
    config->source_filename = malloc(sizeof(char) * (strlen(filename) + 3));
    strcpy(config->header_filename, filename);
    strcpy(config->source_filename, filename);
    strcat(config->header_filename, ".h");
    strcat(config->source_filename, ".c");
    if (!semantic_type) {
        semantic_type = "void*";
    }
    config->semantic_type =
            malloc(sizeof(char) * (strlen(semantic_type) + 1));
    strcpy(config->semantic_type, semantic_type);
    return config;
}

void free_config(writer_config_t* config) {
    free(config->header_filename);
    free(config->source_filename);
    free(config->semantic_type);
    free(config);
    return;
}

int32_t write_parser(grammar_t* grammar, writer_config_t* config)
{
    set_ids(grammar);
    int32_t ret;
    FILE* file;
    if ( (ret = open_file(config->header_filename, &file) ) ) {
        return ret;
    }
    write_header(file, config, grammar);
    close_file(config->header_filename, file);
    if ( (ret = open_file(config->source_filename, &file) ) ) {
        return ret;
    }
    write_source(file, config, grammar);
    close_file(config->source_filename, file);
    return 0;
}

int32_t open_file(char* filename, FILE** file)
{
    if ( !(*file = fopen(filename, "w") ) ) {
        fprintf(stderr, "Could not open file %s: error code %d\n",
            filename, errno);
        return -1;
    }
    return 0;
}

int32_t close_file(char* filename, FILE* file)
{
    if (fclose(file)) {
        fprintf(stderr, "Could not close file %s\n", filename);
        return -1;
    }
    return 0;
}

void set_ids(grammar_t* grammar)
{
    grammar->num_nodes = 0;
    for (uint32_t i = 0; i < grammar->num_rules; ++i)
    {
        set_ids_recursive(grammar, grammar->rules[i]->root);
    }
    return;
}

void set_ids_recursive(grammar_t* grammar, pnode_t* node)
{
    node->id = (grammar->num_nodes)++;
    switch(node->type) {
        case LITERAL_T:
        case NONTERMINAL_T:
        case RANGE_T:
            break;
        default:
            for (uint32_t i = 0; i < node->num_data; ++i) {
                set_ids_recursive(grammar, node->data.node[i]);
            }
    }
    return;
}

static void write_header(FILE* file, writer_config_t* config,
        grammar_t* grammar)
{
    fprintf(file,
        "#include <inttypes.h>\n"
        "#include \"internal.h\"\n");
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        declare_rule(file, config, grammar->rules[i]);
    }
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        declare_semantic_actions(file, config, grammar->rules[i]->root);
        declare_alias_allocs(file, config, grammar->rules[i]->root);
    }
}

static void write_source(FILE* file, writer_config_t* config,
        grammar_t* grammar)
{
    fprintf(file,
        "#include <stdlib.h>\n"
        "#include <stdio.h>\n"
        "#include \"%s\"\n",
        config->header_filename);
    write_maps(file, config, grammar);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        write_rule(file, config, grammar->rules[i]);
    }
    write_helper_macros(file, config);
    for (uint32_t i = 0; i < grammar->num_rules; ++i) {
        write_semantic_actions(file, config, grammar->rules[i]->root);
        write_alias_allocs(file, config, grammar->rules[i]->root);
    }
}

#endif

