#ifndef MAIN_C
#define MAIN_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "internal.h"
#include "utils/grammar.h"
#include "utils/writer.h"

#ifndef BOOTSTRAP
#include "peg/ast.h"
#else
#include "peg/pegspec.h"
#endif

int main(int argc, char** argv)
{
#ifndef BOOTSTRAP
    if (!(argc >= 3)) {
        printf(
            "Usage: quxer infile outfiles_prefix [OPTIONS]\n"
            "Options: -p            Print internal symbolic parser tree"
                " (default: no)\n"
            "         -d type       Define AST node type as \"type\" (default:"
                " void*)\n");
        exit(EXIT_SUCCESS);
    }
    char* infile = argv[1];
    char* outfiles_prefix = argv[2];
    char* ast_type = NULL;
    uint8_t do_print = 0;
    for (uint32_t i = 3; i < argc; ++i) {
        if (!strcmp("-p", argv[i])) {
            do_print = 1;
        } else if (!strcmp("-d", argv[i])) {
            if (!(i + 1 < argc)) {
                fprintf(stderr, "Missing optional argument");
                exit(EXIT_FAILURE);
            }
            ast_type = argv[++i];
        } else {
            fprintf(stderr, "Unknown option %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }
    ast_node_t* result = parse_file(infile);
    if (result) {
        grammar_t* grammar = result->data.grammar;
        free_ast(result);
        if (do_print) {
            print_grammar(grammar);
        }
        writer_config_t* config = init_config(outfiles_prefix, ast_type);
        write_parser(grammar, config);
        free_config(config);
        free_grammar(grammar);
    } else {
        fprintf(stderr, "Failed to parse %s\n", infile);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
#else
    printf("Generating parser.c from metagrammar\n");
    grammar_t* metagrammar = init_metagrammar();
    writer_config_t* config = init_config("parser", "ast_node_t*");
    write_parser(metagrammar, config);
    free_config(config);
    free_grammar(metagrammar);
    exit(EXIT_SUCCESS);
#endif
}

#endif

