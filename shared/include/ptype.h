#ifndef PTYPE_H
#define PTYPE_H

typedef enum {
    SEQUENCE_T,
    ALTERNATIVE_T,
    STAR_T,
    PLUS_T,
    OPTIONAL_T,
    AND_T,
    NOT_T,
    RANGE_T,
    LITERAL_T,
    NONTERMINAL_T,
} ptype_t;

typedef enum {
    IS_CACHED = 0x1,
    IS_FINAL = 0x2,
    DO_CAPTURE = 0x4,
    SEMANTIC_ACTION = 0x8,
    ALIAS = 0x10
} pnode_flag_t;

#endif

