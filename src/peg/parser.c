#include <stdlib.h>
#include <stdio.h>
#include "peg/parser.h"
#include "peg/ast.h"
#define EVAL_grammar 0
#define EVAL_ws 1
#define EVAL_wsp 2
#define EVAL_rule 3
#define EVAL_name 4
#define EVAL_body 5
#define EVAL_alt 6
#define EVAL_seq 7
#define EVAL_operator 8
#define EVAL_prefix 9
#define EVAL_and 10
#define EVAL_not 11
#define EVAL_postfix 12
#define EVAL_star 13
#define EVAL_plus 14
#define EVAL_option 15
#define EVAL_group 16
#define EVAL_final 17
#define EVAL_nonterminal 18
#define EVAL_literal 19
#define EVAL_cclass 20
#define EVAL_code 21
#define EVAL_dot 22
evalfcn_t eval_map[] = {eval_grammar, eval_ws, eval_wsp, eval_rule, eval_name, eval_body, eval_alt, eval_seq, eval_operator, eval_prefix, eval_and, eval_not, eval_postfix, eval_star, eval_plus, eval_option, eval_group, eval_final, eval_nonterminal, eval_literal, eval_cclass, eval_code, eval_dot, };
char* name_map[] = {"grammar", "ws", "wsp", "rule", "name", "body", "alt", "seq", "operator", "prefix", "and", "not", "postfix", "star", "plus", "option", "group", "final", "nonterminal", "literal", "cclass", "code", "dot", };
uint32_t num_rules = 23;
actionfcn_t semantic_action_map[165] = {[0] = semantic_action_0, [18] = semantic_action_18, [31] = semantic_action_31, [32] = semantic_action_32, [40] = semantic_action_40, [47] = semantic_action_47, [54] = semantic_action_54, [61] = semantic_action_61, [69] = semantic_action_69, [73] = semantic_action_73, [80] = semantic_action_80, [84] = semantic_action_84, [88] = semantic_action_88, [96] = semantic_action_96, [102] = semantic_action_102, [108] = semantic_action_108, [110] = semantic_action_110, [111] = semantic_action_111, [112] = semantic_action_112, [113] = semantic_action_113, [115] = semantic_action_115, [121] = semantic_action_121, [122] = semantic_action_122, [136] = semantic_action_136, [164] = semantic_action_164, };
uint32_t num_nodes = 165;
aliasallocsfcn_t alias_allocs_map[165] = {[0] = alias_allocs_0, [18] = alias_allocs_18, [31] = alias_allocs_31, [32] = alias_allocs_32, [40] = alias_allocs_40, [47] = alias_allocs_47, [54] = alias_allocs_54, [61] = alias_allocs_61, [69] = alias_allocs_69, [73] = alias_allocs_73, [80] = alias_allocs_80, [84] = alias_allocs_84, [88] = alias_allocs_88, [96] = alias_allocs_96, [102] = alias_allocs_102, [108] = alias_allocs_108, [110] = alias_allocs_110, [111] = alias_allocs_111, [112] = alias_allocs_112, [113] = alias_allocs_113, [115] = alias_allocs_115, [121] = alias_allocs_121, [122] = alias_allocs_122, [136] = alias_allocs_136, [164] = alias_allocs_164, };
rnode_t* eval_grammar(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_0 = pos;
rnode_t* result_0 = NULL;
uint32_t current_position_0 = start_0;
uint32_t start_1 = current_position_0;
rnode_t* result_1 = NULL;
uint32_t start_2 = start_1;
rnode_t* result_2 = NULL;
uint32_t num_children_1 = 0;
stack_t* list_1 = init_stack(64);
do {
result_2 = NULL;
uint32_t current_position_2 = start_2;
uint32_t start_3 = current_position_2;
rnode_t* result_3 = NULL;
rnode_t* result_3_nt = call_eval(EVAL_ws, state, text, text_length, start_3);
if (result_3_nt) {
result_3 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_3->flags = 0;
result_3->type = NONTERMINAL_T;
result_3->start = start_3;
result_3->end = result_3_nt->end;
result_3->num_children = 1;
result_3->children[0] = result_3_nt;
result_3->id = 3;
}
if (result_3 == NULL) {
goto exit_2;
}
current_position_2 = result_3->end;
uint32_t start_4 = current_position_2;
rnode_t* result_4 = NULL;
rnode_t* result_4_nt = call_eval(EVAL_rule, state, text, text_length, start_4);
if (result_4_nt) {
result_4 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_4->flags = ALIAS | 0;
result_4->type = NONTERMINAL_T;
result_4->start = start_4;
result_4->end = result_4_nt->end;
result_4->num_children = 1;
result_4->children[0] = result_4_nt;
result_4->id = 4;
}
if (result_4 == NULL) {
free_tree(result_3, IS_CACHED);
goto exit_2;
}
current_position_2 = result_4->end;
result_2 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_2->flags = 0;
result_2->type = SEQUENCE_T;
result_2->start = start_2;
result_2->end = result_4->end;
result_2->num_children = 2;
result_2->children[0] = result_3;
result_2->children[1] = result_4;
result_2->id = 2;
exit_2:
if (result_2 != NULL) {
    append_stack(list_1, result_2);
    start_2 = result_2->end;
    ++num_children_1;
}
} while (result_2 != NULL);
if (num_children_1) {
result_1 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_1);
result_1->flags = 0;
result_1->type = PLUS_T;
result_1->start = start_1;
result_1->num_children = num_children_1;
for (uint32_t i = 0; i < num_children_1; ++i) {
result_1->children[i] = list_1->arr[i];
}
result_1->end = ((rnode_t*)list_1->arr[num_children_1 - 1])->end;
result_1->id = 1;
}
free_stack(list_1);
if (result_1 == NULL) {
goto exit_0;
}
current_position_0 = result_1->end;
uint32_t start_5 = current_position_0;
rnode_t* result_5 = NULL;
rnode_t* result_5_nt = call_eval(EVAL_ws, state, text, text_length, start_5);
if (result_5_nt) {
result_5 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_5->flags = 0;
result_5->type = NONTERMINAL_T;
result_5->start = start_5;
result_5->end = result_5_nt->end;
result_5->num_children = 1;
result_5->children[0] = result_5_nt;
result_5->id = 5;
}
if (result_5 == NULL) {
free_tree(result_1, IS_CACHED);
goto exit_0;
}
current_position_0 = result_5->end;
uint32_t start_6 = current_position_0;
rnode_t* result_6 = NULL;
uint32_t start_7 = start_6;
rnode_t* result_7 = NULL;
if (start_7 < text_length) {
uint8_t c_7 = text[start_7];
if (c_7 >= 0 && c_7 <= 255) {
result_7 = malloc(sizeof(rnode_t));
result_7->flags = 0;
result_7->type = RANGE_T;
result_7->start = start_7;
result_7->end = start_7 + 1;
result_7->num_children = 0;
result_7->id = 7;
}
}
if (!result_7) {
result_6 = malloc(sizeof(rnode_t));
result_6->flags = 0;
result_6->type = NOT_T;
result_6->start = start_6;
result_6->end = start_6;
result_6->num_children = 0;
result_6->id = 6;
} else {
free_tree(result_7, IS_CACHED);
}
if (result_6 == NULL) {
free_tree(result_1, IS_CACHED);
free_tree(result_5, IS_CACHED);
goto exit_0;
}
current_position_0 = result_6->end;
result_0 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_0->flags = SEMANTIC_ACTION | 0;
result_0->type = SEQUENCE_T;
result_0->start = start_0;
result_0->end = result_6->end;
result_0->num_children = 3;
result_0->children[0] = result_1;
result_0->children[1] = result_5;
result_0->children[2] = result_6;
result_0->id = 0;
exit_0:
return result_0;
}
rnode_t* eval_ws(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_8 = pos;
rnode_t* result_8 = NULL;
uint32_t start_9 = start_8;
rnode_t* result_9 = NULL;
uint32_t num_children_8 = 0;
stack_t* list_8 = init_stack(64);
do {
result_9 = NULL;
uint32_t start_10 = start_9;
rnode_t* result_10 = NULL;
uint8_t bytesbuf_10[] = {32, };
uint8_t c_10;
for (uint32_t i_10 = 0; i_10 < 1; ++i_10) {
c_10 = bytesbuf_10[i_10];
if (i_10 + start_10 < text_length
    && c_10 == text[i_10 + start_10]) {
if (i_10 == 1 - 1) {
result_10 = malloc(sizeof(rnode_t));
result_10->flags = 0;
result_10->type = LITERAL_T;
result_10->start = start_10;
result_10->end = start_10 + 1;
result_10->num_children = 0;
result_10->id = 10;
}
} else {
break;
}
}
if (result_10 != NULL) {
result_9 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_9->flags = 0;
result_9->type = ALTERNATIVE_T;
result_9->start = start_9;
result_9->end = result_10->end;
result_9->num_children = 1;
result_9->children[0] = result_10;
result_9->id = 9;
goto exit_9;
}
uint32_t start_11 = start_9;
rnode_t* result_11 = NULL;
uint8_t bytesbuf_11[] = {10, };
uint8_t c_11;
for (uint32_t i_11 = 0; i_11 < 1; ++i_11) {
c_11 = bytesbuf_11[i_11];
if (i_11 + start_11 < text_length
    && c_11 == text[i_11 + start_11]) {
if (i_11 == 1 - 1) {
result_11 = malloc(sizeof(rnode_t));
result_11->flags = 0;
result_11->type = LITERAL_T;
result_11->start = start_11;
result_11->end = start_11 + 1;
result_11->num_children = 0;
result_11->id = 11;
}
} else {
break;
}
}
if (result_11 != NULL) {
result_9 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_9->flags = 0;
result_9->type = ALTERNATIVE_T;
result_9->start = start_9;
result_9->end = result_11->end;
result_9->num_children = 1;
result_9->children[0] = result_11;
result_9->id = 9;
goto exit_9;
}
uint32_t start_12 = start_9;
rnode_t* result_12 = NULL;
uint8_t bytesbuf_12[] = {9, };
uint8_t c_12;
for (uint32_t i_12 = 0; i_12 < 1; ++i_12) {
c_12 = bytesbuf_12[i_12];
if (i_12 + start_12 < text_length
    && c_12 == text[i_12 + start_12]) {
if (i_12 == 1 - 1) {
result_12 = malloc(sizeof(rnode_t));
result_12->flags = 0;
result_12->type = LITERAL_T;
result_12->start = start_12;
result_12->end = start_12 + 1;
result_12->num_children = 0;
result_12->id = 12;
}
} else {
break;
}
}
if (result_12 != NULL) {
result_9 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_9->flags = 0;
result_9->type = ALTERNATIVE_T;
result_9->start = start_9;
result_9->end = result_12->end;
result_9->num_children = 1;
result_9->children[0] = result_12;
result_9->id = 9;
goto exit_9;
}
exit_9:
if (result_9 != NULL) {
    append_stack(list_8, result_9);
    start_9 = result_9->end;
    ++num_children_8;
}
} while (result_9 != NULL);
result_8 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_8);
result_8->flags = 0;
result_8->type = STAR_T;
result_8->start = start_8;
result_8->num_children = num_children_8;
if (num_children_8) {
for (uint32_t i = 0; i < num_children_8; ++i) {
result_8->children[i] = list_8->arr[i];
}
result_8->end = ((rnode_t*)list_8->arr[num_children_8 - 1])->end;
} else {
result_8->end = start_8;
}
result_8->id = 8;
free_stack(list_8);
return result_8;
}
rnode_t* eval_wsp(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_13 = pos;
rnode_t* result_13 = NULL;
uint32_t start_14 = start_13;
rnode_t* result_14 = NULL;
uint32_t num_children_13 = 0;
stack_t* list_13 = init_stack(64);
do {
result_14 = NULL;
uint32_t start_15 = start_14;
rnode_t* result_15 = NULL;
uint8_t bytesbuf_15[] = {32, };
uint8_t c_15;
for (uint32_t i_15 = 0; i_15 < 1; ++i_15) {
c_15 = bytesbuf_15[i_15];
if (i_15 + start_15 < text_length
    && c_15 == text[i_15 + start_15]) {
if (i_15 == 1 - 1) {
result_15 = malloc(sizeof(rnode_t));
result_15->flags = 0;
result_15->type = LITERAL_T;
result_15->start = start_15;
result_15->end = start_15 + 1;
result_15->num_children = 0;
result_15->id = 15;
}
} else {
break;
}
}
if (result_15 != NULL) {
result_14 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_14->flags = 0;
result_14->type = ALTERNATIVE_T;
result_14->start = start_14;
result_14->end = result_15->end;
result_14->num_children = 1;
result_14->children[0] = result_15;
result_14->id = 14;
goto exit_14;
}
uint32_t start_16 = start_14;
rnode_t* result_16 = NULL;
uint8_t bytesbuf_16[] = {10, };
uint8_t c_16;
for (uint32_t i_16 = 0; i_16 < 1; ++i_16) {
c_16 = bytesbuf_16[i_16];
if (i_16 + start_16 < text_length
    && c_16 == text[i_16 + start_16]) {
if (i_16 == 1 - 1) {
result_16 = malloc(sizeof(rnode_t));
result_16->flags = 0;
result_16->type = LITERAL_T;
result_16->start = start_16;
result_16->end = start_16 + 1;
result_16->num_children = 0;
result_16->id = 16;
}
} else {
break;
}
}
if (result_16 != NULL) {
result_14 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_14->flags = 0;
result_14->type = ALTERNATIVE_T;
result_14->start = start_14;
result_14->end = result_16->end;
result_14->num_children = 1;
result_14->children[0] = result_16;
result_14->id = 14;
goto exit_14;
}
uint32_t start_17 = start_14;
rnode_t* result_17 = NULL;
uint8_t bytesbuf_17[] = {9, };
uint8_t c_17;
for (uint32_t i_17 = 0; i_17 < 1; ++i_17) {
c_17 = bytesbuf_17[i_17];
if (i_17 + start_17 < text_length
    && c_17 == text[i_17 + start_17]) {
if (i_17 == 1 - 1) {
result_17 = malloc(sizeof(rnode_t));
result_17->flags = 0;
result_17->type = LITERAL_T;
result_17->start = start_17;
result_17->end = start_17 + 1;
result_17->num_children = 0;
result_17->id = 17;
}
} else {
break;
}
}
if (result_17 != NULL) {
result_14 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_14->flags = 0;
result_14->type = ALTERNATIVE_T;
result_14->start = start_14;
result_14->end = result_17->end;
result_14->num_children = 1;
result_14->children[0] = result_17;
result_14->id = 14;
goto exit_14;
}
exit_14:
if (result_14 != NULL) {
    append_stack(list_13, result_14);
    start_14 = result_14->end;
    ++num_children_13;
}
} while (result_14 != NULL);
if (num_children_13) {
result_13 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_13);
result_13->flags = 0;
result_13->type = PLUS_T;
result_13->start = start_13;
result_13->num_children = num_children_13;
for (uint32_t i = 0; i < num_children_13; ++i) {
result_13->children[i] = list_13->arr[i];
}
result_13->end = ((rnode_t*)list_13->arr[num_children_13 - 1])->end;
result_13->id = 13;
}
free_stack(list_13);
return result_13;
}
rnode_t* eval_rule(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_18 = pos;
rnode_t* result_18 = NULL;
uint32_t current_position_18 = start_18;
uint32_t start_19 = current_position_18;
rnode_t* result_19 = NULL;
uint8_t bytesbuf_19[] = {126, };
uint8_t c_19;
for (uint32_t i_19 = 0; i_19 < 1; ++i_19) {
c_19 = bytesbuf_19[i_19];
if (i_19 + start_19 < text_length
    && c_19 == text[i_19 + start_19]) {
if (i_19 == 1 - 1) {
result_19 = malloc(sizeof(rnode_t));
result_19->flags = 0;
result_19->type = LITERAL_T;
result_19->start = start_19;
result_19->end = start_19 + 1;
result_19->num_children = 0;
result_19->id = 19;
}
} else {
break;
}
}
if (result_19 == NULL) {
goto exit_18;
}
current_position_18 = result_19->end;
uint32_t start_20 = current_position_18;
rnode_t* result_20 = NULL;
rnode_t* result_20_nt = call_eval(EVAL_name, state, text, text_length, start_20);
if (result_20_nt) {
result_20 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_20->flags = DO_CAPTURE | 0;
result_20->type = NONTERMINAL_T;
result_20->start = start_20;
result_20->end = result_20_nt->end;
result_20->num_children = 1;
result_20->children[0] = result_20_nt;
result_20->id = 20;
}
if (result_20 == NULL) {
free_tree(result_19, IS_CACHED);
goto exit_18;
}
current_position_18 = result_20->end;
uint32_t start_21 = current_position_18;
rnode_t* result_21 = NULL;
rnode_t* result_21_nt = call_eval(EVAL_ws, state, text, text_length, start_21);
if (result_21_nt) {
result_21 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_21->flags = 0;
result_21->type = NONTERMINAL_T;
result_21->start = start_21;
result_21->end = result_21_nt->end;
result_21->num_children = 1;
result_21->children[0] = result_21_nt;
result_21->id = 21;
}
if (result_21 == NULL) {
free_tree(result_19, IS_CACHED);
free_tree(result_20, IS_CACHED);
goto exit_18;
}
current_position_18 = result_21->end;
uint32_t start_22 = current_position_18;
rnode_t* result_22 = NULL;
uint8_t bytesbuf_22[] = {61, };
uint8_t c_22;
for (uint32_t i_22 = 0; i_22 < 1; ++i_22) {
c_22 = bytesbuf_22[i_22];
if (i_22 + start_22 < text_length
    && c_22 == text[i_22 + start_22]) {
if (i_22 == 1 - 1) {
result_22 = malloc(sizeof(rnode_t));
result_22->flags = 0;
result_22->type = LITERAL_T;
result_22->start = start_22;
result_22->end = start_22 + 1;
result_22->num_children = 0;
result_22->id = 22;
}
} else {
break;
}
}
if (result_22 == NULL) {
free_tree(result_19, IS_CACHED);
free_tree(result_20, IS_CACHED);
free_tree(result_21, IS_CACHED);
goto exit_18;
}
current_position_18 = result_22->end;
uint32_t start_23 = current_position_18;
rnode_t* result_23 = NULL;
rnode_t* result_23_nt = call_eval(EVAL_ws, state, text, text_length, start_23);
if (result_23_nt) {
result_23 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_23->flags = 0;
result_23->type = NONTERMINAL_T;
result_23->start = start_23;
result_23->end = result_23_nt->end;
result_23->num_children = 1;
result_23->children[0] = result_23_nt;
result_23->id = 23;
}
if (result_23 == NULL) {
free_tree(result_19, IS_CACHED);
free_tree(result_20, IS_CACHED);
free_tree(result_21, IS_CACHED);
free_tree(result_22, IS_CACHED);
goto exit_18;
}
current_position_18 = result_23->end;
uint32_t start_24 = current_position_18;
rnode_t* result_24 = NULL;
rnode_t* result_24_nt = call_eval(EVAL_body, state, text, text_length, start_24);
if (result_24_nt) {
result_24 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_24->flags = ALIAS | 0;
result_24->type = NONTERMINAL_T;
result_24->start = start_24;
result_24->end = result_24_nt->end;
result_24->num_children = 1;
result_24->children[0] = result_24_nt;
result_24->id = 24;
}
if (result_24 == NULL) {
free_tree(result_19, IS_CACHED);
free_tree(result_20, IS_CACHED);
free_tree(result_21, IS_CACHED);
free_tree(result_22, IS_CACHED);
free_tree(result_23, IS_CACHED);
goto exit_18;
}
current_position_18 = result_24->end;
result_18 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 6);
result_18->flags = SEMANTIC_ACTION | 0;
result_18->type = SEQUENCE_T;
result_18->start = start_18;
result_18->end = result_24->end;
result_18->num_children = 6;
result_18->children[0] = result_19;
result_18->children[1] = result_20;
result_18->children[2] = result_21;
result_18->children[3] = result_22;
result_18->children[4] = result_23;
result_18->children[5] = result_24;
result_18->id = 18;
exit_18:
return result_18;
}
rnode_t* eval_name(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_25 = pos;
rnode_t* result_25 = NULL;
uint32_t start_26 = start_25;
rnode_t* result_26 = NULL;
uint32_t num_children_25 = 0;
stack_t* list_25 = init_stack(64);
do {
result_26 = NULL;
uint32_t start_27 = start_26;
rnode_t* result_27 = NULL;
if (start_27 < text_length) {
uint8_t c_27 = text[start_27];
if (c_27 >= 65 && c_27 <= 90) {
result_27 = malloc(sizeof(rnode_t));
result_27->flags = 0;
result_27->type = RANGE_T;
result_27->start = start_27;
result_27->end = start_27 + 1;
result_27->num_children = 0;
result_27->id = 27;
}
}
if (result_27 != NULL) {
result_26 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_26->flags = 0;
result_26->type = ALTERNATIVE_T;
result_26->start = start_26;
result_26->end = result_27->end;
result_26->num_children = 1;
result_26->children[0] = result_27;
result_26->id = 26;
goto exit_26;
}
uint32_t start_28 = start_26;
rnode_t* result_28 = NULL;
if (start_28 < text_length) {
uint8_t c_28 = text[start_28];
if (c_28 >= 97 && c_28 <= 122) {
result_28 = malloc(sizeof(rnode_t));
result_28->flags = 0;
result_28->type = RANGE_T;
result_28->start = start_28;
result_28->end = start_28 + 1;
result_28->num_children = 0;
result_28->id = 28;
}
}
if (result_28 != NULL) {
result_26 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_26->flags = 0;
result_26->type = ALTERNATIVE_T;
result_26->start = start_26;
result_26->end = result_28->end;
result_26->num_children = 1;
result_26->children[0] = result_28;
result_26->id = 26;
goto exit_26;
}
uint32_t start_29 = start_26;
rnode_t* result_29 = NULL;
if (start_29 < text_length) {
uint8_t c_29 = text[start_29];
if (c_29 >= 48 && c_29 <= 57) {
result_29 = malloc(sizeof(rnode_t));
result_29->flags = 0;
result_29->type = RANGE_T;
result_29->start = start_29;
result_29->end = start_29 + 1;
result_29->num_children = 0;
result_29->id = 29;
}
}
if (result_29 != NULL) {
result_26 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_26->flags = 0;
result_26->type = ALTERNATIVE_T;
result_26->start = start_26;
result_26->end = result_29->end;
result_26->num_children = 1;
result_26->children[0] = result_29;
result_26->id = 26;
goto exit_26;
}
uint32_t start_30 = start_26;
rnode_t* result_30 = NULL;
uint8_t bytesbuf_30[] = {95, };
uint8_t c_30;
for (uint32_t i_30 = 0; i_30 < 1; ++i_30) {
c_30 = bytesbuf_30[i_30];
if (i_30 + start_30 < text_length
    && c_30 == text[i_30 + start_30]) {
if (i_30 == 1 - 1) {
result_30 = malloc(sizeof(rnode_t));
result_30->flags = 0;
result_30->type = LITERAL_T;
result_30->start = start_30;
result_30->end = start_30 + 1;
result_30->num_children = 0;
result_30->id = 30;
}
} else {
break;
}
}
if (result_30 != NULL) {
result_26 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_26->flags = 0;
result_26->type = ALTERNATIVE_T;
result_26->start = start_26;
result_26->end = result_30->end;
result_26->num_children = 1;
result_26->children[0] = result_30;
result_26->id = 26;
goto exit_26;
}
exit_26:
if (result_26 != NULL) {
    append_stack(list_25, result_26);
    start_26 = result_26->end;
    ++num_children_25;
}
} while (result_26 != NULL);
if (num_children_25) {
result_25 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_25);
result_25->flags = 0;
result_25->type = PLUS_T;
result_25->start = start_25;
result_25->num_children = num_children_25;
for (uint32_t i = 0; i < num_children_25; ++i) {
result_25->children[i] = list_25->arr[i];
}
result_25->end = ((rnode_t*)list_25->arr[num_children_25 - 1])->end;
result_25->id = 25;
}
free_stack(list_25);
return result_25;
}
rnode_t* eval_body(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_31 = pos;
rnode_t* result_31 = NULL;
rnode_t* result_31_nt = call_eval(EVAL_alt, state, text, text_length, start_31);
if (result_31_nt) {
result_31 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_31->flags = SEMANTIC_ACTION | ALIAS | 0;
result_31->type = NONTERMINAL_T;
result_31->start = start_31;
result_31->end = result_31_nt->end;
result_31->num_children = 1;
result_31->children[0] = result_31_nt;
result_31->id = 31;
}
return result_31;
}
rnode_t* eval_alt(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_32 = pos;
rnode_t* result_32 = NULL;
uint32_t current_position_32 = start_32;
uint32_t start_33 = current_position_32;
rnode_t* result_33 = NULL;
rnode_t* result_33_nt = call_eval(EVAL_seq, state, text, text_length, start_33);
if (result_33_nt) {
result_33 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_33->flags = ALIAS | 0;
result_33->type = NONTERMINAL_T;
result_33->start = start_33;
result_33->end = result_33_nt->end;
result_33->num_children = 1;
result_33->children[0] = result_33_nt;
result_33->id = 33;
}
if (result_33 == NULL) {
goto exit_32;
}
current_position_32 = result_33->end;
uint32_t start_34 = current_position_32;
rnode_t* result_34 = NULL;
uint32_t start_35 = start_34;
rnode_t* result_35 = NULL;
uint32_t num_children_34 = 0;
stack_t* list_34 = init_stack(64);
do {
result_35 = NULL;
uint32_t current_position_35 = start_35;
uint32_t start_36 = current_position_35;
rnode_t* result_36 = NULL;
rnode_t* result_36_nt = call_eval(EVAL_ws, state, text, text_length, start_36);
if (result_36_nt) {
result_36 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_36->flags = 0;
result_36->type = NONTERMINAL_T;
result_36->start = start_36;
result_36->end = result_36_nt->end;
result_36->num_children = 1;
result_36->children[0] = result_36_nt;
result_36->id = 36;
}
if (result_36 == NULL) {
goto exit_35;
}
current_position_35 = result_36->end;
uint32_t start_37 = current_position_35;
rnode_t* result_37 = NULL;
uint8_t bytesbuf_37[] = {47, };
uint8_t c_37;
for (uint32_t i_37 = 0; i_37 < 1; ++i_37) {
c_37 = bytesbuf_37[i_37];
if (i_37 + start_37 < text_length
    && c_37 == text[i_37 + start_37]) {
if (i_37 == 1 - 1) {
result_37 = malloc(sizeof(rnode_t));
result_37->flags = 0;
result_37->type = LITERAL_T;
result_37->start = start_37;
result_37->end = start_37 + 1;
result_37->num_children = 0;
result_37->id = 37;
}
} else {
break;
}
}
if (result_37 == NULL) {
free_tree(result_36, IS_CACHED);
goto exit_35;
}
current_position_35 = result_37->end;
uint32_t start_38 = current_position_35;
rnode_t* result_38 = NULL;
rnode_t* result_38_nt = call_eval(EVAL_ws, state, text, text_length, start_38);
if (result_38_nt) {
result_38 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_38->flags = 0;
result_38->type = NONTERMINAL_T;
result_38->start = start_38;
result_38->end = result_38_nt->end;
result_38->num_children = 1;
result_38->children[0] = result_38_nt;
result_38->id = 38;
}
if (result_38 == NULL) {
free_tree(result_36, IS_CACHED);
free_tree(result_37, IS_CACHED);
goto exit_35;
}
current_position_35 = result_38->end;
uint32_t start_39 = current_position_35;
rnode_t* result_39 = NULL;
rnode_t* result_39_nt = call_eval(EVAL_seq, state, text, text_length, start_39);
if (result_39_nt) {
result_39 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_39->flags = ALIAS | 0;
result_39->type = NONTERMINAL_T;
result_39->start = start_39;
result_39->end = result_39_nt->end;
result_39->num_children = 1;
result_39->children[0] = result_39_nt;
result_39->id = 39;
}
if (result_39 == NULL) {
free_tree(result_36, IS_CACHED);
free_tree(result_37, IS_CACHED);
free_tree(result_38, IS_CACHED);
goto exit_35;
}
current_position_35 = result_39->end;
result_35 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 4);
result_35->flags = 0;
result_35->type = SEQUENCE_T;
result_35->start = start_35;
result_35->end = result_39->end;
result_35->num_children = 4;
result_35->children[0] = result_36;
result_35->children[1] = result_37;
result_35->children[2] = result_38;
result_35->children[3] = result_39;
result_35->id = 35;
exit_35:
if (result_35 != NULL) {
    append_stack(list_34, result_35);
    start_35 = result_35->end;
    ++num_children_34;
}
} while (result_35 != NULL);
result_34 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_34);
result_34->flags = 0;
result_34->type = STAR_T;
result_34->start = start_34;
result_34->num_children = num_children_34;
if (num_children_34) {
for (uint32_t i = 0; i < num_children_34; ++i) {
result_34->children[i] = list_34->arr[i];
}
result_34->end = ((rnode_t*)list_34->arr[num_children_34 - 1])->end;
} else {
result_34->end = start_34;
}
result_34->id = 34;
free_stack(list_34);
if (result_34 == NULL) {
free_tree(result_33, IS_CACHED);
goto exit_32;
}
current_position_32 = result_34->end;
result_32 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_32->flags = SEMANTIC_ACTION | 0;
result_32->type = SEQUENCE_T;
result_32->start = start_32;
result_32->end = result_34->end;
result_32->num_children = 2;
result_32->children[0] = result_33;
result_32->children[1] = result_34;
result_32->id = 32;
exit_32:
return result_32;
}
rnode_t* eval_seq(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_40 = pos;
rnode_t* result_40 = NULL;
uint32_t current_position_40 = start_40;
uint32_t start_41 = current_position_40;
rnode_t* result_41 = NULL;
rnode_t* result_41_nt = call_eval(EVAL_operator, state, text, text_length, start_41);
if (result_41_nt) {
result_41 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_41->flags = ALIAS | 0;
result_41->type = NONTERMINAL_T;
result_41->start = start_41;
result_41->end = result_41_nt->end;
result_41->num_children = 1;
result_41->children[0] = result_41_nt;
result_41->id = 41;
}
if (result_41 == NULL) {
goto exit_40;
}
current_position_40 = result_41->end;
uint32_t start_42 = current_position_40;
rnode_t* result_42 = NULL;
uint32_t start_43 = start_42;
rnode_t* result_43 = NULL;
uint32_t num_children_42 = 0;
stack_t* list_42 = init_stack(64);
do {
result_43 = NULL;
uint32_t current_position_43 = start_43;
uint32_t start_44 = current_position_43;
rnode_t* result_44 = NULL;
rnode_t* result_44_nt = call_eval(EVAL_wsp, state, text, text_length, start_44);
if (result_44_nt) {
result_44 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_44->flags = 0;
result_44->type = NONTERMINAL_T;
result_44->start = start_44;
result_44->end = result_44_nt->end;
result_44->num_children = 1;
result_44->children[0] = result_44_nt;
result_44->id = 44;
}
if (result_44 == NULL) {
goto exit_43;
}
current_position_43 = result_44->end;
uint32_t start_45 = current_position_43;
rnode_t* result_45 = NULL;
rnode_t* result_45_nt = call_eval(EVAL_operator, state, text, text_length, start_45);
if (result_45_nt) {
result_45 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_45->flags = ALIAS | 0;
result_45->type = NONTERMINAL_T;
result_45->start = start_45;
result_45->end = result_45_nt->end;
result_45->num_children = 1;
result_45->children[0] = result_45_nt;
result_45->id = 45;
}
if (result_45 == NULL) {
free_tree(result_44, IS_CACHED);
goto exit_43;
}
current_position_43 = result_45->end;
result_43 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_43->flags = 0;
result_43->type = SEQUENCE_T;
result_43->start = start_43;
result_43->end = result_45->end;
result_43->num_children = 2;
result_43->children[0] = result_44;
result_43->children[1] = result_45;
result_43->id = 43;
exit_43:
if (result_43 != NULL) {
    append_stack(list_42, result_43);
    start_43 = result_43->end;
    ++num_children_42;
}
} while (result_43 != NULL);
result_42 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_42);
result_42->flags = 0;
result_42->type = STAR_T;
result_42->start = start_42;
result_42->num_children = num_children_42;
if (num_children_42) {
for (uint32_t i = 0; i < num_children_42; ++i) {
result_42->children[i] = list_42->arr[i];
}
result_42->end = ((rnode_t*)list_42->arr[num_children_42 - 1])->end;
} else {
result_42->end = start_42;
}
result_42->id = 42;
free_stack(list_42);
if (result_42 == NULL) {
free_tree(result_41, IS_CACHED);
goto exit_40;
}
current_position_40 = result_42->end;
result_40 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_40->flags = SEMANTIC_ACTION | 0;
result_40->type = SEQUENCE_T;
result_40->start = start_40;
result_40->end = result_42->end;
result_40->num_children = 2;
result_40->children[0] = result_41;
result_40->children[1] = result_42;
result_40->id = 40;
exit_40:
return result_40;
}
rnode_t* eval_operator(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_46 = pos;
rnode_t* result_46 = NULL;
uint32_t start_47 = start_46;
rnode_t* result_47 = NULL;
uint32_t current_position_47 = start_47;
uint32_t start_48 = current_position_47;
rnode_t* result_48 = NULL;
rnode_t* result_48_nt = call_eval(EVAL_prefix, state, text, text_length, start_48);
if (result_48_nt) {
result_48 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_48->flags = ALIAS | 0;
result_48->type = NONTERMINAL_T;
result_48->start = start_48;
result_48->end = result_48_nt->end;
result_48->num_children = 1;
result_48->children[0] = result_48_nt;
result_48->id = 48;
}
if (result_48 == NULL) {
goto exit_47;
}
current_position_47 = result_48->end;
uint32_t start_49 = current_position_47;
rnode_t* result_49 = NULL;
uint32_t start_50 = start_49;
rnode_t* result_50 = NULL;
uint32_t start_51 = start_50;
rnode_t* result_51 = NULL;
uint32_t current_position_51 = start_51;
uint32_t start_52 = current_position_51;
rnode_t* result_52 = NULL;
rnode_t* result_52_nt = call_eval(EVAL_ws, state, text, text_length, start_52);
if (result_52_nt) {
result_52 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_52->flags = 0;
result_52->type = NONTERMINAL_T;
result_52->start = start_52;
result_52->end = result_52_nt->end;
result_52->num_children = 1;
result_52->children[0] = result_52_nt;
result_52->id = 52;
}
if (result_52 == NULL) {
goto exit_51;
}
current_position_51 = result_52->end;
uint32_t start_53 = current_position_51;
rnode_t* result_53 = NULL;
rnode_t* result_53_nt = call_eval(EVAL_code, state, text, text_length, start_53);
if (result_53_nt) {
result_53 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_53->flags = DO_CAPTURE | 0;
result_53->type = NONTERMINAL_T;
result_53->start = start_53;
result_53->end = result_53_nt->end;
result_53->num_children = 1;
result_53->children[0] = result_53_nt;
result_53->id = 53;
}
if (result_53 == NULL) {
free_tree(result_52, IS_CACHED);
goto exit_51;
}
current_position_51 = result_53->end;
result_51 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_51->flags = 0;
result_51->type = SEQUENCE_T;
result_51->start = start_51;
result_51->end = result_53->end;
result_51->num_children = 2;
result_51->children[0] = result_52;
result_51->children[1] = result_53;
result_51->id = 51;
exit_51:
if (result_51) {
result_50 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_50->end = result_51->end;
result_50->num_children = 1;
result_50->children[0] = result_51;
} else {
result_50 = malloc(sizeof(rnode_t));
result_50->end = start_50;
result_50->num_children = 0;
}
result_50->type = OPTIONAL_T;
result_50->flags = 0;
result_50->start = start_50;
result_50->id = 50;
if (result_50) {
result_49 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_49->end = result_50->end;
result_49->num_children = 1;
result_49->children[0] = result_50;
} else {
result_49 = malloc(sizeof(rnode_t));
result_49->end = start_49;
result_49->num_children = 0;
}
result_49->type = OPTIONAL_T;
result_49->flags = 0;
result_49->start = start_49;
result_49->id = 49;
if (result_49 == NULL) {
free_tree(result_48, IS_CACHED);
goto exit_47;
}
current_position_47 = result_49->end;
result_47 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_47->flags = SEMANTIC_ACTION | 0;
result_47->type = SEQUENCE_T;
result_47->start = start_47;
result_47->end = result_49->end;
result_47->num_children = 2;
result_47->children[0] = result_48;
result_47->children[1] = result_49;
result_47->id = 47;
exit_47:
if (result_47 != NULL) {
result_46 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_46->flags = 0;
result_46->type = ALTERNATIVE_T;
result_46->start = start_46;
result_46->end = result_47->end;
result_46->num_children = 1;
result_46->children[0] = result_47;
result_46->id = 46;
goto exit_46;
}
uint32_t start_54 = start_46;
rnode_t* result_54 = NULL;
uint32_t current_position_54 = start_54;
uint32_t start_55 = current_position_54;
rnode_t* result_55 = NULL;
rnode_t* result_55_nt = call_eval(EVAL_postfix, state, text, text_length, start_55);
if (result_55_nt) {
result_55 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_55->flags = ALIAS | 0;
result_55->type = NONTERMINAL_T;
result_55->start = start_55;
result_55->end = result_55_nt->end;
result_55->num_children = 1;
result_55->children[0] = result_55_nt;
result_55->id = 55;
}
if (result_55 == NULL) {
goto exit_54;
}
current_position_54 = result_55->end;
uint32_t start_56 = current_position_54;
rnode_t* result_56 = NULL;
uint32_t start_57 = start_56;
rnode_t* result_57 = NULL;
uint32_t start_58 = start_57;
rnode_t* result_58 = NULL;
uint32_t current_position_58 = start_58;
uint32_t start_59 = current_position_58;
rnode_t* result_59 = NULL;
rnode_t* result_59_nt = call_eval(EVAL_ws, state, text, text_length, start_59);
if (result_59_nt) {
result_59 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_59->flags = 0;
result_59->type = NONTERMINAL_T;
result_59->start = start_59;
result_59->end = result_59_nt->end;
result_59->num_children = 1;
result_59->children[0] = result_59_nt;
result_59->id = 59;
}
if (result_59 == NULL) {
goto exit_58;
}
current_position_58 = result_59->end;
uint32_t start_60 = current_position_58;
rnode_t* result_60 = NULL;
rnode_t* result_60_nt = call_eval(EVAL_code, state, text, text_length, start_60);
if (result_60_nt) {
result_60 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_60->flags = DO_CAPTURE | 0;
result_60->type = NONTERMINAL_T;
result_60->start = start_60;
result_60->end = result_60_nt->end;
result_60->num_children = 1;
result_60->children[0] = result_60_nt;
result_60->id = 60;
}
if (result_60 == NULL) {
free_tree(result_59, IS_CACHED);
goto exit_58;
}
current_position_58 = result_60->end;
result_58 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_58->flags = 0;
result_58->type = SEQUENCE_T;
result_58->start = start_58;
result_58->end = result_60->end;
result_58->num_children = 2;
result_58->children[0] = result_59;
result_58->children[1] = result_60;
result_58->id = 58;
exit_58:
if (result_58) {
result_57 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_57->end = result_58->end;
result_57->num_children = 1;
result_57->children[0] = result_58;
} else {
result_57 = malloc(sizeof(rnode_t));
result_57->end = start_57;
result_57->num_children = 0;
}
result_57->type = OPTIONAL_T;
result_57->flags = 0;
result_57->start = start_57;
result_57->id = 57;
if (result_57) {
result_56 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_56->end = result_57->end;
result_56->num_children = 1;
result_56->children[0] = result_57;
} else {
result_56 = malloc(sizeof(rnode_t));
result_56->end = start_56;
result_56->num_children = 0;
}
result_56->type = OPTIONAL_T;
result_56->flags = 0;
result_56->start = start_56;
result_56->id = 56;
if (result_56 == NULL) {
free_tree(result_55, IS_CACHED);
goto exit_54;
}
current_position_54 = result_56->end;
result_54 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_54->flags = SEMANTIC_ACTION | 0;
result_54->type = SEQUENCE_T;
result_54->start = start_54;
result_54->end = result_56->end;
result_54->num_children = 2;
result_54->children[0] = result_55;
result_54->children[1] = result_56;
result_54->id = 54;
exit_54:
if (result_54 != NULL) {
result_46 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_46->flags = 0;
result_46->type = ALTERNATIVE_T;
result_46->start = start_46;
result_46->end = result_54->end;
result_46->num_children = 1;
result_46->children[0] = result_54;
result_46->id = 46;
goto exit_46;
}
uint32_t start_61 = start_46;
rnode_t* result_61 = NULL;
uint32_t current_position_61 = start_61;
uint32_t start_62 = current_position_61;
rnode_t* result_62 = NULL;
rnode_t* result_62_nt = call_eval(EVAL_group, state, text, text_length, start_62);
if (result_62_nt) {
result_62 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_62->flags = ALIAS | 0;
result_62->type = NONTERMINAL_T;
result_62->start = start_62;
result_62->end = result_62_nt->end;
result_62->num_children = 1;
result_62->children[0] = result_62_nt;
result_62->id = 62;
}
if (result_62 == NULL) {
goto exit_61;
}
current_position_61 = result_62->end;
uint32_t start_63 = current_position_61;
rnode_t* result_63 = NULL;
uint32_t start_64 = start_63;
rnode_t* result_64 = NULL;
uint32_t start_65 = start_64;
rnode_t* result_65 = NULL;
uint32_t current_position_65 = start_65;
uint32_t start_66 = current_position_65;
rnode_t* result_66 = NULL;
rnode_t* result_66_nt = call_eval(EVAL_ws, state, text, text_length, start_66);
if (result_66_nt) {
result_66 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_66->flags = 0;
result_66->type = NONTERMINAL_T;
result_66->start = start_66;
result_66->end = result_66_nt->end;
result_66->num_children = 1;
result_66->children[0] = result_66_nt;
result_66->id = 66;
}
if (result_66 == NULL) {
goto exit_65;
}
current_position_65 = result_66->end;
uint32_t start_67 = current_position_65;
rnode_t* result_67 = NULL;
rnode_t* result_67_nt = call_eval(EVAL_code, state, text, text_length, start_67);
if (result_67_nt) {
result_67 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_67->flags = DO_CAPTURE | 0;
result_67->type = NONTERMINAL_T;
result_67->start = start_67;
result_67->end = result_67_nt->end;
result_67->num_children = 1;
result_67->children[0] = result_67_nt;
result_67->id = 67;
}
if (result_67 == NULL) {
free_tree(result_66, IS_CACHED);
goto exit_65;
}
current_position_65 = result_67->end;
result_65 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_65->flags = 0;
result_65->type = SEQUENCE_T;
result_65->start = start_65;
result_65->end = result_67->end;
result_65->num_children = 2;
result_65->children[0] = result_66;
result_65->children[1] = result_67;
result_65->id = 65;
exit_65:
if (result_65) {
result_64 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_64->end = result_65->end;
result_64->num_children = 1;
result_64->children[0] = result_65;
} else {
result_64 = malloc(sizeof(rnode_t));
result_64->end = start_64;
result_64->num_children = 0;
}
result_64->type = OPTIONAL_T;
result_64->flags = 0;
result_64->start = start_64;
result_64->id = 64;
if (result_64) {
result_63 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_63->end = result_64->end;
result_63->num_children = 1;
result_63->children[0] = result_64;
} else {
result_63 = malloc(sizeof(rnode_t));
result_63->end = start_63;
result_63->num_children = 0;
}
result_63->type = OPTIONAL_T;
result_63->flags = 0;
result_63->start = start_63;
result_63->id = 63;
if (result_63 == NULL) {
free_tree(result_62, IS_CACHED);
goto exit_61;
}
current_position_61 = result_63->end;
result_61 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_61->flags = SEMANTIC_ACTION | 0;
result_61->type = SEQUENCE_T;
result_61->start = start_61;
result_61->end = result_63->end;
result_61->num_children = 2;
result_61->children[0] = result_62;
result_61->children[1] = result_63;
result_61->id = 61;
exit_61:
if (result_61 != NULL) {
result_46 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_46->flags = 0;
result_46->type = ALTERNATIVE_T;
result_46->start = start_46;
result_46->end = result_61->end;
result_46->num_children = 1;
result_46->children[0] = result_61;
result_46->id = 46;
goto exit_46;
}
exit_46:
return result_46;
}
rnode_t* eval_prefix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_68 = pos;
rnode_t* result_68 = NULL;
uint32_t start_69 = start_68;
rnode_t* result_69 = NULL;
uint32_t current_position_69 = start_69;
uint32_t start_70 = current_position_69;
rnode_t* result_70 = NULL;
rnode_t* result_70_nt = call_eval(EVAL_and, state, text, text_length, start_70);
if (result_70_nt) {
result_70 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_70->flags = 0;
result_70->type = NONTERMINAL_T;
result_70->start = start_70;
result_70->end = result_70_nt->end;
result_70->num_children = 1;
result_70->children[0] = result_70_nt;
result_70->id = 70;
}
if (result_70 == NULL) {
goto exit_69;
}
current_position_69 = result_70->end;
uint32_t start_71 = current_position_69;
rnode_t* result_71 = NULL;
rnode_t* result_71_nt = call_eval(EVAL_ws, state, text, text_length, start_71);
if (result_71_nt) {
result_71 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_71->flags = 0;
result_71->type = NONTERMINAL_T;
result_71->start = start_71;
result_71->end = result_71_nt->end;
result_71->num_children = 1;
result_71->children[0] = result_71_nt;
result_71->id = 71;
}
if (result_71 == NULL) {
free_tree(result_70, IS_CACHED);
goto exit_69;
}
current_position_69 = result_71->end;
uint32_t start_72 = current_position_69;
rnode_t* result_72 = NULL;
rnode_t* result_72_nt = call_eval(EVAL_group, state, text, text_length, start_72);
if (result_72_nt) {
result_72 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_72->flags = ALIAS | 0;
result_72->type = NONTERMINAL_T;
result_72->start = start_72;
result_72->end = result_72_nt->end;
result_72->num_children = 1;
result_72->children[0] = result_72_nt;
result_72->id = 72;
}
if (result_72 == NULL) {
free_tree(result_70, IS_CACHED);
free_tree(result_71, IS_CACHED);
goto exit_69;
}
current_position_69 = result_72->end;
result_69 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_69->flags = SEMANTIC_ACTION | 0;
result_69->type = SEQUENCE_T;
result_69->start = start_69;
result_69->end = result_72->end;
result_69->num_children = 3;
result_69->children[0] = result_70;
result_69->children[1] = result_71;
result_69->children[2] = result_72;
result_69->id = 69;
exit_69:
if (result_69 != NULL) {
result_68 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_68->flags = 0;
result_68->type = ALTERNATIVE_T;
result_68->start = start_68;
result_68->end = result_69->end;
result_68->num_children = 1;
result_68->children[0] = result_69;
result_68->id = 68;
goto exit_68;
}
uint32_t start_73 = start_68;
rnode_t* result_73 = NULL;
uint32_t current_position_73 = start_73;
uint32_t start_74 = current_position_73;
rnode_t* result_74 = NULL;
rnode_t* result_74_nt = call_eval(EVAL_not, state, text, text_length, start_74);
if (result_74_nt) {
result_74 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_74->flags = 0;
result_74->type = NONTERMINAL_T;
result_74->start = start_74;
result_74->end = result_74_nt->end;
result_74->num_children = 1;
result_74->children[0] = result_74_nt;
result_74->id = 74;
}
if (result_74 == NULL) {
goto exit_73;
}
current_position_73 = result_74->end;
uint32_t start_75 = current_position_73;
rnode_t* result_75 = NULL;
rnode_t* result_75_nt = call_eval(EVAL_ws, state, text, text_length, start_75);
if (result_75_nt) {
result_75 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_75->flags = 0;
result_75->type = NONTERMINAL_T;
result_75->start = start_75;
result_75->end = result_75_nt->end;
result_75->num_children = 1;
result_75->children[0] = result_75_nt;
result_75->id = 75;
}
if (result_75 == NULL) {
free_tree(result_74, IS_CACHED);
goto exit_73;
}
current_position_73 = result_75->end;
uint32_t start_76 = current_position_73;
rnode_t* result_76 = NULL;
rnode_t* result_76_nt = call_eval(EVAL_group, state, text, text_length, start_76);
if (result_76_nt) {
result_76 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_76->flags = ALIAS | 0;
result_76->type = NONTERMINAL_T;
result_76->start = start_76;
result_76->end = result_76_nt->end;
result_76->num_children = 1;
result_76->children[0] = result_76_nt;
result_76->id = 76;
}
if (result_76 == NULL) {
free_tree(result_74, IS_CACHED);
free_tree(result_75, IS_CACHED);
goto exit_73;
}
current_position_73 = result_76->end;
result_73 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_73->flags = SEMANTIC_ACTION | 0;
result_73->type = SEQUENCE_T;
result_73->start = start_73;
result_73->end = result_76->end;
result_73->num_children = 3;
result_73->children[0] = result_74;
result_73->children[1] = result_75;
result_73->children[2] = result_76;
result_73->id = 73;
exit_73:
if (result_73 != NULL) {
result_68 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_68->flags = 0;
result_68->type = ALTERNATIVE_T;
result_68->start = start_68;
result_68->end = result_73->end;
result_68->num_children = 1;
result_68->children[0] = result_73;
result_68->id = 68;
goto exit_68;
}
exit_68:
return result_68;
}
rnode_t* eval_and(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_77 = pos;
rnode_t* result_77 = NULL;
uint8_t bytesbuf_77[] = {38, };
uint8_t c_77;
for (uint32_t i_77 = 0; i_77 < 1; ++i_77) {
c_77 = bytesbuf_77[i_77];
if (i_77 + start_77 < text_length
    && c_77 == text[i_77 + start_77]) {
if (i_77 == 1 - 1) {
result_77 = malloc(sizeof(rnode_t));
result_77->flags = 0;
result_77->type = LITERAL_T;
result_77->start = start_77;
result_77->end = start_77 + 1;
result_77->num_children = 0;
result_77->id = 77;
}
} else {
break;
}
}
return result_77;
}
rnode_t* eval_not(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_78 = pos;
rnode_t* result_78 = NULL;
uint8_t bytesbuf_78[] = {33, };
uint8_t c_78;
for (uint32_t i_78 = 0; i_78 < 1; ++i_78) {
c_78 = bytesbuf_78[i_78];
if (i_78 + start_78 < text_length
    && c_78 == text[i_78 + start_78]) {
if (i_78 == 1 - 1) {
result_78 = malloc(sizeof(rnode_t));
result_78->flags = 0;
result_78->type = LITERAL_T;
result_78->start = start_78;
result_78->end = start_78 + 1;
result_78->num_children = 0;
result_78->id = 78;
}
} else {
break;
}
}
return result_78;
}
rnode_t* eval_postfix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_79 = pos;
rnode_t* result_79 = NULL;
uint32_t start_80 = start_79;
rnode_t* result_80 = NULL;
uint32_t current_position_80 = start_80;
uint32_t start_81 = current_position_80;
rnode_t* result_81 = NULL;
rnode_t* result_81_nt = call_eval(EVAL_group, state, text, text_length, start_81);
if (result_81_nt) {
result_81 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_81->flags = ALIAS | 0;
result_81->type = NONTERMINAL_T;
result_81->start = start_81;
result_81->end = result_81_nt->end;
result_81->num_children = 1;
result_81->children[0] = result_81_nt;
result_81->id = 81;
}
if (result_81 == NULL) {
goto exit_80;
}
current_position_80 = result_81->end;
uint32_t start_82 = current_position_80;
rnode_t* result_82 = NULL;
rnode_t* result_82_nt = call_eval(EVAL_ws, state, text, text_length, start_82);
if (result_82_nt) {
result_82 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_82->flags = 0;
result_82->type = NONTERMINAL_T;
result_82->start = start_82;
result_82->end = result_82_nt->end;
result_82->num_children = 1;
result_82->children[0] = result_82_nt;
result_82->id = 82;
}
if (result_82 == NULL) {
free_tree(result_81, IS_CACHED);
goto exit_80;
}
current_position_80 = result_82->end;
uint32_t start_83 = current_position_80;
rnode_t* result_83 = NULL;
rnode_t* result_83_nt = call_eval(EVAL_star, state, text, text_length, start_83);
if (result_83_nt) {
result_83 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_83->flags = 0;
result_83->type = NONTERMINAL_T;
result_83->start = start_83;
result_83->end = result_83_nt->end;
result_83->num_children = 1;
result_83->children[0] = result_83_nt;
result_83->id = 83;
}
if (result_83 == NULL) {
free_tree(result_81, IS_CACHED);
free_tree(result_82, IS_CACHED);
goto exit_80;
}
current_position_80 = result_83->end;
result_80 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_80->flags = SEMANTIC_ACTION | 0;
result_80->type = SEQUENCE_T;
result_80->start = start_80;
result_80->end = result_83->end;
result_80->num_children = 3;
result_80->children[0] = result_81;
result_80->children[1] = result_82;
result_80->children[2] = result_83;
result_80->id = 80;
exit_80:
if (result_80 != NULL) {
result_79 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_79->flags = 0;
result_79->type = ALTERNATIVE_T;
result_79->start = start_79;
result_79->end = result_80->end;
result_79->num_children = 1;
result_79->children[0] = result_80;
result_79->id = 79;
goto exit_79;
}
uint32_t start_84 = start_79;
rnode_t* result_84 = NULL;
uint32_t current_position_84 = start_84;
uint32_t start_85 = current_position_84;
rnode_t* result_85 = NULL;
rnode_t* result_85_nt = call_eval(EVAL_group, state, text, text_length, start_85);
if (result_85_nt) {
result_85 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_85->flags = ALIAS | 0;
result_85->type = NONTERMINAL_T;
result_85->start = start_85;
result_85->end = result_85_nt->end;
result_85->num_children = 1;
result_85->children[0] = result_85_nt;
result_85->id = 85;
}
if (result_85 == NULL) {
goto exit_84;
}
current_position_84 = result_85->end;
uint32_t start_86 = current_position_84;
rnode_t* result_86 = NULL;
rnode_t* result_86_nt = call_eval(EVAL_ws, state, text, text_length, start_86);
if (result_86_nt) {
result_86 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_86->flags = 0;
result_86->type = NONTERMINAL_T;
result_86->start = start_86;
result_86->end = result_86_nt->end;
result_86->num_children = 1;
result_86->children[0] = result_86_nt;
result_86->id = 86;
}
if (result_86 == NULL) {
free_tree(result_85, IS_CACHED);
goto exit_84;
}
current_position_84 = result_86->end;
uint32_t start_87 = current_position_84;
rnode_t* result_87 = NULL;
rnode_t* result_87_nt = call_eval(EVAL_plus, state, text, text_length, start_87);
if (result_87_nt) {
result_87 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_87->flags = 0;
result_87->type = NONTERMINAL_T;
result_87->start = start_87;
result_87->end = result_87_nt->end;
result_87->num_children = 1;
result_87->children[0] = result_87_nt;
result_87->id = 87;
}
if (result_87 == NULL) {
free_tree(result_85, IS_CACHED);
free_tree(result_86, IS_CACHED);
goto exit_84;
}
current_position_84 = result_87->end;
result_84 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_84->flags = SEMANTIC_ACTION | 0;
result_84->type = SEQUENCE_T;
result_84->start = start_84;
result_84->end = result_87->end;
result_84->num_children = 3;
result_84->children[0] = result_85;
result_84->children[1] = result_86;
result_84->children[2] = result_87;
result_84->id = 84;
exit_84:
if (result_84 != NULL) {
result_79 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_79->flags = 0;
result_79->type = ALTERNATIVE_T;
result_79->start = start_79;
result_79->end = result_84->end;
result_79->num_children = 1;
result_79->children[0] = result_84;
result_79->id = 79;
goto exit_79;
}
uint32_t start_88 = start_79;
rnode_t* result_88 = NULL;
uint32_t current_position_88 = start_88;
uint32_t start_89 = current_position_88;
rnode_t* result_89 = NULL;
rnode_t* result_89_nt = call_eval(EVAL_group, state, text, text_length, start_89);
if (result_89_nt) {
result_89 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_89->flags = ALIAS | 0;
result_89->type = NONTERMINAL_T;
result_89->start = start_89;
result_89->end = result_89_nt->end;
result_89->num_children = 1;
result_89->children[0] = result_89_nt;
result_89->id = 89;
}
if (result_89 == NULL) {
goto exit_88;
}
current_position_88 = result_89->end;
uint32_t start_90 = current_position_88;
rnode_t* result_90 = NULL;
rnode_t* result_90_nt = call_eval(EVAL_ws, state, text, text_length, start_90);
if (result_90_nt) {
result_90 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_90->flags = 0;
result_90->type = NONTERMINAL_T;
result_90->start = start_90;
result_90->end = result_90_nt->end;
result_90->num_children = 1;
result_90->children[0] = result_90_nt;
result_90->id = 90;
}
if (result_90 == NULL) {
free_tree(result_89, IS_CACHED);
goto exit_88;
}
current_position_88 = result_90->end;
uint32_t start_91 = current_position_88;
rnode_t* result_91 = NULL;
rnode_t* result_91_nt = call_eval(EVAL_option, state, text, text_length, start_91);
if (result_91_nt) {
result_91 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_91->flags = 0;
result_91->type = NONTERMINAL_T;
result_91->start = start_91;
result_91->end = result_91_nt->end;
result_91->num_children = 1;
result_91->children[0] = result_91_nt;
result_91->id = 91;
}
if (result_91 == NULL) {
free_tree(result_89, IS_CACHED);
free_tree(result_90, IS_CACHED);
goto exit_88;
}
current_position_88 = result_91->end;
result_88 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_88->flags = SEMANTIC_ACTION | 0;
result_88->type = SEQUENCE_T;
result_88->start = start_88;
result_88->end = result_91->end;
result_88->num_children = 3;
result_88->children[0] = result_89;
result_88->children[1] = result_90;
result_88->children[2] = result_91;
result_88->id = 88;
exit_88:
if (result_88 != NULL) {
result_79 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_79->flags = 0;
result_79->type = ALTERNATIVE_T;
result_79->start = start_79;
result_79->end = result_88->end;
result_79->num_children = 1;
result_79->children[0] = result_88;
result_79->id = 79;
goto exit_79;
}
exit_79:
return result_79;
}
rnode_t* eval_star(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_92 = pos;
rnode_t* result_92 = NULL;
uint8_t bytesbuf_92[] = {42, };
uint8_t c_92;
for (uint32_t i_92 = 0; i_92 < 1; ++i_92) {
c_92 = bytesbuf_92[i_92];
if (i_92 + start_92 < text_length
    && c_92 == text[i_92 + start_92]) {
if (i_92 == 1 - 1) {
result_92 = malloc(sizeof(rnode_t));
result_92->flags = 0;
result_92->type = LITERAL_T;
result_92->start = start_92;
result_92->end = start_92 + 1;
result_92->num_children = 0;
result_92->id = 92;
}
} else {
break;
}
}
return result_92;
}
rnode_t* eval_plus(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_93 = pos;
rnode_t* result_93 = NULL;
uint8_t bytesbuf_93[] = {43, };
uint8_t c_93;
for (uint32_t i_93 = 0; i_93 < 1; ++i_93) {
c_93 = bytesbuf_93[i_93];
if (i_93 + start_93 < text_length
    && c_93 == text[i_93 + start_93]) {
if (i_93 == 1 - 1) {
result_93 = malloc(sizeof(rnode_t));
result_93->flags = 0;
result_93->type = LITERAL_T;
result_93->start = start_93;
result_93->end = start_93 + 1;
result_93->num_children = 0;
result_93->id = 93;
}
} else {
break;
}
}
return result_93;
}
rnode_t* eval_option(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_94 = pos;
rnode_t* result_94 = NULL;
uint8_t bytesbuf_94[] = {63, };
uint8_t c_94;
for (uint32_t i_94 = 0; i_94 < 1; ++i_94) {
c_94 = bytesbuf_94[i_94];
if (i_94 + start_94 < text_length
    && c_94 == text[i_94 + start_94]) {
if (i_94 == 1 - 1) {
result_94 = malloc(sizeof(rnode_t));
result_94->flags = 0;
result_94->type = LITERAL_T;
result_94->start = start_94;
result_94->end = start_94 + 1;
result_94->num_children = 0;
result_94->id = 94;
}
} else {
break;
}
}
return result_94;
}
rnode_t* eval_group(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_95 = pos;
rnode_t* result_95 = NULL;
uint32_t start_96 = start_95;
rnode_t* result_96 = NULL;
uint32_t current_position_96 = start_96;
uint32_t start_97 = current_position_96;
rnode_t* result_97 = NULL;
uint8_t bytesbuf_97[] = {40, };
uint8_t c_97;
for (uint32_t i_97 = 0; i_97 < 1; ++i_97) {
c_97 = bytesbuf_97[i_97];
if (i_97 + start_97 < text_length
    && c_97 == text[i_97 + start_97]) {
if (i_97 == 1 - 1) {
result_97 = malloc(sizeof(rnode_t));
result_97->flags = 0;
result_97->type = LITERAL_T;
result_97->start = start_97;
result_97->end = start_97 + 1;
result_97->num_children = 0;
result_97->id = 97;
}
} else {
break;
}
}
if (result_97 == NULL) {
goto exit_96;
}
current_position_96 = result_97->end;
uint32_t start_98 = current_position_96;
rnode_t* result_98 = NULL;
rnode_t* result_98_nt = call_eval(EVAL_ws, state, text, text_length, start_98);
if (result_98_nt) {
result_98 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_98->flags = 0;
result_98->type = NONTERMINAL_T;
result_98->start = start_98;
result_98->end = result_98_nt->end;
result_98->num_children = 1;
result_98->children[0] = result_98_nt;
result_98->id = 98;
}
if (result_98 == NULL) {
free_tree(result_97, IS_CACHED);
goto exit_96;
}
current_position_96 = result_98->end;
uint32_t start_99 = current_position_96;
rnode_t* result_99 = NULL;
rnode_t* result_99_nt = call_eval(EVAL_body, state, text, text_length, start_99);
if (result_99_nt) {
result_99 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_99->flags = ALIAS | 0;
result_99->type = NONTERMINAL_T;
result_99->start = start_99;
result_99->end = result_99_nt->end;
result_99->num_children = 1;
result_99->children[0] = result_99_nt;
result_99->id = 99;
}
if (result_99 == NULL) {
free_tree(result_97, IS_CACHED);
free_tree(result_98, IS_CACHED);
goto exit_96;
}
current_position_96 = result_99->end;
uint32_t start_100 = current_position_96;
rnode_t* result_100 = NULL;
rnode_t* result_100_nt = call_eval(EVAL_ws, state, text, text_length, start_100);
if (result_100_nt) {
result_100 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_100->flags = 0;
result_100->type = NONTERMINAL_T;
result_100->start = start_100;
result_100->end = result_100_nt->end;
result_100->num_children = 1;
result_100->children[0] = result_100_nt;
result_100->id = 100;
}
if (result_100 == NULL) {
free_tree(result_97, IS_CACHED);
free_tree(result_98, IS_CACHED);
free_tree(result_99, IS_CACHED);
goto exit_96;
}
current_position_96 = result_100->end;
uint32_t start_101 = current_position_96;
rnode_t* result_101 = NULL;
uint8_t bytesbuf_101[] = {41, };
uint8_t c_101;
for (uint32_t i_101 = 0; i_101 < 1; ++i_101) {
c_101 = bytesbuf_101[i_101];
if (i_101 + start_101 < text_length
    && c_101 == text[i_101 + start_101]) {
if (i_101 == 1 - 1) {
result_101 = malloc(sizeof(rnode_t));
result_101->flags = 0;
result_101->type = LITERAL_T;
result_101->start = start_101;
result_101->end = start_101 + 1;
result_101->num_children = 0;
result_101->id = 101;
}
} else {
break;
}
}
if (result_101 == NULL) {
free_tree(result_97, IS_CACHED);
free_tree(result_98, IS_CACHED);
free_tree(result_99, IS_CACHED);
free_tree(result_100, IS_CACHED);
goto exit_96;
}
current_position_96 = result_101->end;
result_96 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 5);
result_96->flags = SEMANTIC_ACTION | 0;
result_96->type = SEQUENCE_T;
result_96->start = start_96;
result_96->end = result_101->end;
result_96->num_children = 5;
result_96->children[0] = result_97;
result_96->children[1] = result_98;
result_96->children[2] = result_99;
result_96->children[3] = result_100;
result_96->children[4] = result_101;
result_96->id = 96;
exit_96:
if (result_96 != NULL) {
result_95 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_95->flags = 0;
result_95->type = ALTERNATIVE_T;
result_95->start = start_95;
result_95->end = result_96->end;
result_95->num_children = 1;
result_95->children[0] = result_96;
result_95->id = 95;
goto exit_95;
}
uint32_t start_102 = start_95;
rnode_t* result_102 = NULL;
uint32_t current_position_102 = start_102;
uint32_t start_103 = current_position_102;
rnode_t* result_103 = NULL;
uint8_t bytesbuf_103[] = {60, };
uint8_t c_103;
for (uint32_t i_103 = 0; i_103 < 1; ++i_103) {
c_103 = bytesbuf_103[i_103];
if (i_103 + start_103 < text_length
    && c_103 == text[i_103 + start_103]) {
if (i_103 == 1 - 1) {
result_103 = malloc(sizeof(rnode_t));
result_103->flags = 0;
result_103->type = LITERAL_T;
result_103->start = start_103;
result_103->end = start_103 + 1;
result_103->num_children = 0;
result_103->id = 103;
}
} else {
break;
}
}
if (result_103 == NULL) {
goto exit_102;
}
current_position_102 = result_103->end;
uint32_t start_104 = current_position_102;
rnode_t* result_104 = NULL;
rnode_t* result_104_nt = call_eval(EVAL_ws, state, text, text_length, start_104);
if (result_104_nt) {
result_104 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_104->flags = 0;
result_104->type = NONTERMINAL_T;
result_104->start = start_104;
result_104->end = result_104_nt->end;
result_104->num_children = 1;
result_104->children[0] = result_104_nt;
result_104->id = 104;
}
if (result_104 == NULL) {
free_tree(result_103, IS_CACHED);
goto exit_102;
}
current_position_102 = result_104->end;
uint32_t start_105 = current_position_102;
rnode_t* result_105 = NULL;
rnode_t* result_105_nt = call_eval(EVAL_body, state, text, text_length, start_105);
if (result_105_nt) {
result_105 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_105->flags = ALIAS | 0;
result_105->type = NONTERMINAL_T;
result_105->start = start_105;
result_105->end = result_105_nt->end;
result_105->num_children = 1;
result_105->children[0] = result_105_nt;
result_105->id = 105;
}
if (result_105 == NULL) {
free_tree(result_103, IS_CACHED);
free_tree(result_104, IS_CACHED);
goto exit_102;
}
current_position_102 = result_105->end;
uint32_t start_106 = current_position_102;
rnode_t* result_106 = NULL;
rnode_t* result_106_nt = call_eval(EVAL_ws, state, text, text_length, start_106);
if (result_106_nt) {
result_106 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_106->flags = 0;
result_106->type = NONTERMINAL_T;
result_106->start = start_106;
result_106->end = result_106_nt->end;
result_106->num_children = 1;
result_106->children[0] = result_106_nt;
result_106->id = 106;
}
if (result_106 == NULL) {
free_tree(result_103, IS_CACHED);
free_tree(result_104, IS_CACHED);
free_tree(result_105, IS_CACHED);
goto exit_102;
}
current_position_102 = result_106->end;
uint32_t start_107 = current_position_102;
rnode_t* result_107 = NULL;
uint8_t bytesbuf_107[] = {62, };
uint8_t c_107;
for (uint32_t i_107 = 0; i_107 < 1; ++i_107) {
c_107 = bytesbuf_107[i_107];
if (i_107 + start_107 < text_length
    && c_107 == text[i_107 + start_107]) {
if (i_107 == 1 - 1) {
result_107 = malloc(sizeof(rnode_t));
result_107->flags = 0;
result_107->type = LITERAL_T;
result_107->start = start_107;
result_107->end = start_107 + 1;
result_107->num_children = 0;
result_107->id = 107;
}
} else {
break;
}
}
if (result_107 == NULL) {
free_tree(result_103, IS_CACHED);
free_tree(result_104, IS_CACHED);
free_tree(result_105, IS_CACHED);
free_tree(result_106, IS_CACHED);
goto exit_102;
}
current_position_102 = result_107->end;
result_102 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 5);
result_102->flags = SEMANTIC_ACTION | 0;
result_102->type = SEQUENCE_T;
result_102->start = start_102;
result_102->end = result_107->end;
result_102->num_children = 5;
result_102->children[0] = result_103;
result_102->children[1] = result_104;
result_102->children[2] = result_105;
result_102->children[3] = result_106;
result_102->children[4] = result_107;
result_102->id = 102;
exit_102:
if (result_102 != NULL) {
result_95 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_95->flags = 0;
result_95->type = ALTERNATIVE_T;
result_95->start = start_95;
result_95->end = result_102->end;
result_95->num_children = 1;
result_95->children[0] = result_102;
result_95->id = 95;
goto exit_95;
}
uint32_t start_108 = start_95;
rnode_t* result_108 = NULL;
rnode_t* result_108_nt = call_eval(EVAL_final, state, text, text_length, start_108);
if (result_108_nt) {
result_108 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_108->flags = SEMANTIC_ACTION | ALIAS | 0;
result_108->type = NONTERMINAL_T;
result_108->start = start_108;
result_108->end = result_108_nt->end;
result_108->num_children = 1;
result_108->children[0] = result_108_nt;
result_108->id = 108;
}
if (result_108 != NULL) {
result_95 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_95->flags = 0;
result_95->type = ALTERNATIVE_T;
result_95->start = start_95;
result_95->end = result_108->end;
result_95->num_children = 1;
result_95->children[0] = result_108;
result_95->id = 95;
goto exit_95;
}
exit_95:
return result_95;
}
rnode_t* eval_final(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_109 = pos;
rnode_t* result_109 = NULL;
uint32_t start_110 = start_109;
rnode_t* result_110 = NULL;
rnode_t* result_110_nt = call_eval(EVAL_nonterminal, state, text, text_length, start_110);
if (result_110_nt) {
result_110 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_110->flags = SEMANTIC_ACTION | ALIAS | 0;
result_110->type = NONTERMINAL_T;
result_110->start = start_110;
result_110->end = result_110_nt->end;
result_110->num_children = 1;
result_110->children[0] = result_110_nt;
result_110->id = 110;
}
if (result_110 != NULL) {
result_109 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_109->flags = 0;
result_109->type = ALTERNATIVE_T;
result_109->start = start_109;
result_109->end = result_110->end;
result_109->num_children = 1;
result_109->children[0] = result_110;
result_109->id = 109;
goto exit_109;
}
uint32_t start_111 = start_109;
rnode_t* result_111 = NULL;
rnode_t* result_111_nt = call_eval(EVAL_literal, state, text, text_length, start_111);
if (result_111_nt) {
result_111 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_111->flags = SEMANTIC_ACTION | ALIAS | 0;
result_111->type = NONTERMINAL_T;
result_111->start = start_111;
result_111->end = result_111_nt->end;
result_111->num_children = 1;
result_111->children[0] = result_111_nt;
result_111->id = 111;
}
if (result_111 != NULL) {
result_109 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_109->flags = 0;
result_109->type = ALTERNATIVE_T;
result_109->start = start_109;
result_109->end = result_111->end;
result_109->num_children = 1;
result_109->children[0] = result_111;
result_109->id = 109;
goto exit_109;
}
uint32_t start_112 = start_109;
rnode_t* result_112 = NULL;
rnode_t* result_112_nt = call_eval(EVAL_cclass, state, text, text_length, start_112);
if (result_112_nt) {
result_112 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_112->flags = SEMANTIC_ACTION | ALIAS | 0;
result_112->type = NONTERMINAL_T;
result_112->start = start_112;
result_112->end = result_112_nt->end;
result_112->num_children = 1;
result_112->children[0] = result_112_nt;
result_112->id = 112;
}
if (result_112 != NULL) {
result_109 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_109->flags = 0;
result_109->type = ALTERNATIVE_T;
result_109->start = start_109;
result_109->end = result_112->end;
result_109->num_children = 1;
result_109->children[0] = result_112;
result_109->id = 109;
goto exit_109;
}
uint32_t start_113 = start_109;
rnode_t* result_113 = NULL;
rnode_t* result_113_nt = call_eval(EVAL_dot, state, text, text_length, start_113);
if (result_113_nt) {
result_113 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_113->flags = SEMANTIC_ACTION | ALIAS | 0;
result_113->type = NONTERMINAL_T;
result_113->start = start_113;
result_113->end = result_113_nt->end;
result_113->num_children = 1;
result_113->children[0] = result_113_nt;
result_113->id = 113;
}
if (result_113 != NULL) {
result_109 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_109->flags = 0;
result_109->type = ALTERNATIVE_T;
result_109->start = start_109;
result_109->end = result_113->end;
result_109->num_children = 1;
result_109->children[0] = result_113;
result_109->id = 109;
goto exit_109;
}
exit_109:
return result_109;
}
rnode_t* eval_nonterminal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_114 = pos;
rnode_t* result_114 = NULL;
uint32_t start_115 = start_114;
rnode_t* result_115 = NULL;
uint32_t current_position_115 = start_115;
uint32_t start_116 = current_position_115;
rnode_t* result_116 = NULL;
rnode_t* result_116_nt = call_eval(EVAL_name, state, text, text_length, start_116);
if (result_116_nt) {
result_116 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_116->flags = DO_CAPTURE | 0;
result_116->type = NONTERMINAL_T;
result_116->start = start_116;
result_116->end = result_116_nt->end;
result_116->num_children = 1;
result_116->children[0] = result_116_nt;
result_116->id = 116;
}
if (result_116 == NULL) {
goto exit_115;
}
current_position_115 = result_116->end;
uint32_t start_117 = current_position_115;
rnode_t* result_117 = NULL;
rnode_t* result_117_nt = call_eval(EVAL_ws, state, text, text_length, start_117);
if (result_117_nt) {
result_117 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_117->flags = 0;
result_117->type = NONTERMINAL_T;
result_117->start = start_117;
result_117->end = result_117_nt->end;
result_117->num_children = 1;
result_117->children[0] = result_117_nt;
result_117->id = 117;
}
if (result_117 == NULL) {
free_tree(result_116, IS_CACHED);
goto exit_115;
}
current_position_115 = result_117->end;
uint32_t start_118 = current_position_115;
rnode_t* result_118 = NULL;
uint8_t bytesbuf_118[] = {58, };
uint8_t c_118;
for (uint32_t i_118 = 0; i_118 < 1; ++i_118) {
c_118 = bytesbuf_118[i_118];
if (i_118 + start_118 < text_length
    && c_118 == text[i_118 + start_118]) {
if (i_118 == 1 - 1) {
result_118 = malloc(sizeof(rnode_t));
result_118->flags = 0;
result_118->type = LITERAL_T;
result_118->start = start_118;
result_118->end = start_118 + 1;
result_118->num_children = 0;
result_118->id = 118;
}
} else {
break;
}
}
if (result_118 == NULL) {
free_tree(result_116, IS_CACHED);
free_tree(result_117, IS_CACHED);
goto exit_115;
}
current_position_115 = result_118->end;
uint32_t start_119 = current_position_115;
rnode_t* result_119 = NULL;
rnode_t* result_119_nt = call_eval(EVAL_ws, state, text, text_length, start_119);
if (result_119_nt) {
result_119 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_119->flags = 0;
result_119->type = NONTERMINAL_T;
result_119->start = start_119;
result_119->end = result_119_nt->end;
result_119->num_children = 1;
result_119->children[0] = result_119_nt;
result_119->id = 119;
}
if (result_119 == NULL) {
free_tree(result_116, IS_CACHED);
free_tree(result_117, IS_CACHED);
free_tree(result_118, IS_CACHED);
goto exit_115;
}
current_position_115 = result_119->end;
uint32_t start_120 = current_position_115;
rnode_t* result_120 = NULL;
rnode_t* result_120_nt = call_eval(EVAL_name, state, text, text_length, start_120);
if (result_120_nt) {
result_120 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_120->flags = DO_CAPTURE | 0;
result_120->type = NONTERMINAL_T;
result_120->start = start_120;
result_120->end = result_120_nt->end;
result_120->num_children = 1;
result_120->children[0] = result_120_nt;
result_120->id = 120;
}
if (result_120 == NULL) {
free_tree(result_116, IS_CACHED);
free_tree(result_117, IS_CACHED);
free_tree(result_118, IS_CACHED);
free_tree(result_119, IS_CACHED);
goto exit_115;
}
current_position_115 = result_120->end;
result_115 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 5);
result_115->flags = SEMANTIC_ACTION | 0;
result_115->type = SEQUENCE_T;
result_115->start = start_115;
result_115->end = result_120->end;
result_115->num_children = 5;
result_115->children[0] = result_116;
result_115->children[1] = result_117;
result_115->children[2] = result_118;
result_115->children[3] = result_119;
result_115->children[4] = result_120;
result_115->id = 115;
exit_115:
if (result_115 != NULL) {
result_114 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_114->flags = 0;
result_114->type = ALTERNATIVE_T;
result_114->start = start_114;
result_114->end = result_115->end;
result_114->num_children = 1;
result_114->children[0] = result_115;
result_114->id = 114;
goto exit_114;
}
uint32_t start_121 = start_114;
rnode_t* result_121 = NULL;
rnode_t* result_121_nt = call_eval(EVAL_name, state, text, text_length, start_121);
if (result_121_nt) {
result_121 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_121->flags = DO_CAPTURE | SEMANTIC_ACTION | 0;
result_121->type = NONTERMINAL_T;
result_121->start = start_121;
result_121->end = result_121_nt->end;
result_121->num_children = 1;
result_121->children[0] = result_121_nt;
result_121->id = 121;
}
if (result_121 != NULL) {
result_114 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_114->flags = 0;
result_114->type = ALTERNATIVE_T;
result_114->start = start_114;
result_114->end = result_121->end;
result_114->num_children = 1;
result_114->children[0] = result_121;
result_114->id = 114;
goto exit_114;
}
exit_114:
return result_114;
}
rnode_t* eval_literal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_122 = pos;
rnode_t* result_122 = NULL;
uint32_t current_position_122 = start_122;
uint32_t start_123 = current_position_122;
rnode_t* result_123 = NULL;
uint8_t bytesbuf_123[] = {34, };
uint8_t c_123;
for (uint32_t i_123 = 0; i_123 < 1; ++i_123) {
c_123 = bytesbuf_123[i_123];
if (i_123 + start_123 < text_length
    && c_123 == text[i_123 + start_123]) {
if (i_123 == 1 - 1) {
result_123 = malloc(sizeof(rnode_t));
result_123->flags = 0;
result_123->type = LITERAL_T;
result_123->start = start_123;
result_123->end = start_123 + 1;
result_123->num_children = 0;
result_123->id = 123;
}
} else {
break;
}
}
if (result_123 == NULL) {
goto exit_122;
}
current_position_122 = result_123->end;
uint32_t start_124 = current_position_122;
rnode_t* result_124 = NULL;
uint32_t start_125 = start_124;
rnode_t* result_125 = NULL;
uint32_t num_children_124 = 0;
stack_t* list_124 = init_stack(64);
do {
result_125 = NULL;
uint32_t start_126 = start_125;
rnode_t* result_126 = NULL;
uint32_t current_position_126 = start_126;
uint32_t start_127 = current_position_126;
rnode_t* result_127 = NULL;
uint32_t start_128 = start_127;
rnode_t* result_128 = NULL;
uint8_t bytesbuf_128[] = {92, };
uint8_t c_128;
for (uint32_t i_128 = 0; i_128 < 1; ++i_128) {
c_128 = bytesbuf_128[i_128];
if (i_128 + start_128 < text_length
    && c_128 == text[i_128 + start_128]) {
if (i_128 == 1 - 1) {
result_128 = malloc(sizeof(rnode_t));
result_128->flags = 0;
result_128->type = LITERAL_T;
result_128->start = start_128;
result_128->end = start_128 + 1;
result_128->num_children = 0;
result_128->id = 128;
}
} else {
break;
}
}
if (result_128) {
result_127 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_127->flags = 0;
result_127->type = AND_T;
result_127->start = start_127;
result_127->end = start_127;
result_127->num_children = 1;
result_127->children[0] = result_128;
result_127->id = 127;
}
if (result_127 == NULL) {
goto exit_126;
}
current_position_126 = result_127->end;
uint32_t start_129 = current_position_126;
rnode_t* result_129 = NULL;
if (start_129 < text_length) {
uint8_t c_129 = text[start_129];
if (c_129 >= 0 && c_129 <= 255) {
result_129 = malloc(sizeof(rnode_t));
result_129->flags = 0;
result_129->type = RANGE_T;
result_129->start = start_129;
result_129->end = start_129 + 1;
result_129->num_children = 0;
result_129->id = 129;
}
}
if (result_129 == NULL) {
free_tree(result_127, IS_CACHED);
goto exit_126;
}
current_position_126 = result_129->end;
uint32_t start_130 = current_position_126;
rnode_t* result_130 = NULL;
if (start_130 < text_length) {
uint8_t c_130 = text[start_130];
if (c_130 >= 0 && c_130 <= 255) {
result_130 = malloc(sizeof(rnode_t));
result_130->flags = 0;
result_130->type = RANGE_T;
result_130->start = start_130;
result_130->end = start_130 + 1;
result_130->num_children = 0;
result_130->id = 130;
}
}
if (result_130 == NULL) {
free_tree(result_127, IS_CACHED);
free_tree(result_129, IS_CACHED);
goto exit_126;
}
current_position_126 = result_130->end;
result_126 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_126->flags = 0;
result_126->type = SEQUENCE_T;
result_126->start = start_126;
result_126->end = result_130->end;
result_126->num_children = 3;
result_126->children[0] = result_127;
result_126->children[1] = result_129;
result_126->children[2] = result_130;
result_126->id = 126;
exit_126:
if (result_126 != NULL) {
result_125 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_125->flags = 0;
result_125->type = ALTERNATIVE_T;
result_125->start = start_125;
result_125->end = result_126->end;
result_125->num_children = 1;
result_125->children[0] = result_126;
result_125->id = 125;
goto exit_125;
}
uint32_t start_131 = start_125;
rnode_t* result_131 = NULL;
uint32_t current_position_131 = start_131;
uint32_t start_132 = current_position_131;
rnode_t* result_132 = NULL;
uint32_t start_133 = start_132;
rnode_t* result_133 = NULL;
uint8_t bytesbuf_133[] = {34, };
uint8_t c_133;
for (uint32_t i_133 = 0; i_133 < 1; ++i_133) {
c_133 = bytesbuf_133[i_133];
if (i_133 + start_133 < text_length
    && c_133 == text[i_133 + start_133]) {
if (i_133 == 1 - 1) {
result_133 = malloc(sizeof(rnode_t));
result_133->flags = 0;
result_133->type = LITERAL_T;
result_133->start = start_133;
result_133->end = start_133 + 1;
result_133->num_children = 0;
result_133->id = 133;
}
} else {
break;
}
}
if (!result_133) {
result_132 = malloc(sizeof(rnode_t));
result_132->flags = 0;
result_132->type = NOT_T;
result_132->start = start_132;
result_132->end = start_132;
result_132->num_children = 0;
result_132->id = 132;
} else {
free_tree(result_133, IS_CACHED);
}
if (result_132 == NULL) {
goto exit_131;
}
current_position_131 = result_132->end;
uint32_t start_134 = current_position_131;
rnode_t* result_134 = NULL;
if (start_134 < text_length) {
uint8_t c_134 = text[start_134];
if (c_134 >= 0 && c_134 <= 255) {
result_134 = malloc(sizeof(rnode_t));
result_134->flags = 0;
result_134->type = RANGE_T;
result_134->start = start_134;
result_134->end = start_134 + 1;
result_134->num_children = 0;
result_134->id = 134;
}
}
if (result_134 == NULL) {
free_tree(result_132, IS_CACHED);
goto exit_131;
}
current_position_131 = result_134->end;
result_131 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_131->flags = 0;
result_131->type = SEQUENCE_T;
result_131->start = start_131;
result_131->end = result_134->end;
result_131->num_children = 2;
result_131->children[0] = result_132;
result_131->children[1] = result_134;
result_131->id = 131;
exit_131:
if (result_131 != NULL) {
result_125 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_125->flags = 0;
result_125->type = ALTERNATIVE_T;
result_125->start = start_125;
result_125->end = result_131->end;
result_125->num_children = 1;
result_125->children[0] = result_131;
result_125->id = 125;
goto exit_125;
}
exit_125:
if (result_125 != NULL) {
    append_stack(list_124, result_125);
    start_125 = result_125->end;
    ++num_children_124;
}
} while (result_125 != NULL);
result_124 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_124);
result_124->flags = DO_CAPTURE | 0;
result_124->type = STAR_T;
result_124->start = start_124;
result_124->num_children = num_children_124;
if (num_children_124) {
for (uint32_t i = 0; i < num_children_124; ++i) {
result_124->children[i] = list_124->arr[i];
}
result_124->end = ((rnode_t*)list_124->arr[num_children_124 - 1])->end;
} else {
result_124->end = start_124;
}
result_124->id = 124;
free_stack(list_124);
if (result_124 == NULL) {
free_tree(result_123, IS_CACHED);
goto exit_122;
}
current_position_122 = result_124->end;
uint32_t start_135 = current_position_122;
rnode_t* result_135 = NULL;
uint8_t bytesbuf_135[] = {34, };
uint8_t c_135;
for (uint32_t i_135 = 0; i_135 < 1; ++i_135) {
c_135 = bytesbuf_135[i_135];
if (i_135 + start_135 < text_length
    && c_135 == text[i_135 + start_135]) {
if (i_135 == 1 - 1) {
result_135 = malloc(sizeof(rnode_t));
result_135->flags = 0;
result_135->type = LITERAL_T;
result_135->start = start_135;
result_135->end = start_135 + 1;
result_135->num_children = 0;
result_135->id = 135;
}
} else {
break;
}
}
if (result_135 == NULL) {
free_tree(result_123, IS_CACHED);
free_tree(result_124, IS_CACHED);
goto exit_122;
}
current_position_122 = result_135->end;
result_122 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_122->flags = SEMANTIC_ACTION | 0;
result_122->type = SEQUENCE_T;
result_122->start = start_122;
result_122->end = result_135->end;
result_122->num_children = 3;
result_122->children[0] = result_123;
result_122->children[1] = result_124;
result_122->children[2] = result_135;
result_122->id = 122;
exit_122:
return result_122;
}
rnode_t* eval_cclass(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_136 = pos;
rnode_t* result_136 = NULL;
uint32_t current_position_136 = start_136;
uint32_t start_137 = current_position_136;
rnode_t* result_137 = NULL;
uint8_t bytesbuf_137[] = {91, };
uint8_t c_137;
for (uint32_t i_137 = 0; i_137 < 1; ++i_137) {
c_137 = bytesbuf_137[i_137];
if (i_137 + start_137 < text_length
    && c_137 == text[i_137 + start_137]) {
if (i_137 == 1 - 1) {
result_137 = malloc(sizeof(rnode_t));
result_137->flags = 0;
result_137->type = LITERAL_T;
result_137->start = start_137;
result_137->end = start_137 + 1;
result_137->num_children = 0;
result_137->id = 137;
}
} else {
break;
}
}
if (result_137 == NULL) {
goto exit_136;
}
current_position_136 = result_137->end;
uint32_t start_138 = current_position_136;
rnode_t* result_138 = NULL;
uint32_t start_139 = start_138;
rnode_t* result_139 = NULL;
uint32_t num_children_138 = 0;
stack_t* list_138 = init_stack(64);
do {
result_139 = NULL;
uint32_t start_140 = start_139;
rnode_t* result_140 = NULL;
uint32_t current_position_140 = start_140;
uint32_t start_141 = current_position_140;
rnode_t* result_141 = NULL;
uint32_t start_142 = start_141;
rnode_t* result_142 = NULL;
uint8_t bytesbuf_142[] = {92, };
uint8_t c_142;
for (uint32_t i_142 = 0; i_142 < 1; ++i_142) {
c_142 = bytesbuf_142[i_142];
if (i_142 + start_142 < text_length
    && c_142 == text[i_142 + start_142]) {
if (i_142 == 1 - 1) {
result_142 = malloc(sizeof(rnode_t));
result_142->flags = 0;
result_142->type = LITERAL_T;
result_142->start = start_142;
result_142->end = start_142 + 1;
result_142->num_children = 0;
result_142->id = 142;
}
} else {
break;
}
}
if (result_142) {
result_141 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_141->flags = 0;
result_141->type = AND_T;
result_141->start = start_141;
result_141->end = start_141;
result_141->num_children = 1;
result_141->children[0] = result_142;
result_141->id = 141;
}
if (result_141 == NULL) {
goto exit_140;
}
current_position_140 = result_141->end;
uint32_t start_143 = current_position_140;
rnode_t* result_143 = NULL;
if (start_143 < text_length) {
uint8_t c_143 = text[start_143];
if (c_143 >= 0 && c_143 <= 255) {
result_143 = malloc(sizeof(rnode_t));
result_143->flags = 0;
result_143->type = RANGE_T;
result_143->start = start_143;
result_143->end = start_143 + 1;
result_143->num_children = 0;
result_143->id = 143;
}
}
if (result_143 == NULL) {
free_tree(result_141, IS_CACHED);
goto exit_140;
}
current_position_140 = result_143->end;
uint32_t start_144 = current_position_140;
rnode_t* result_144 = NULL;
if (start_144 < text_length) {
uint8_t c_144 = text[start_144];
if (c_144 >= 0 && c_144 <= 255) {
result_144 = malloc(sizeof(rnode_t));
result_144->flags = 0;
result_144->type = RANGE_T;
result_144->start = start_144;
result_144->end = start_144 + 1;
result_144->num_children = 0;
result_144->id = 144;
}
}
if (result_144 == NULL) {
free_tree(result_141, IS_CACHED);
free_tree(result_143, IS_CACHED);
goto exit_140;
}
current_position_140 = result_144->end;
result_140 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_140->flags = 0;
result_140->type = SEQUENCE_T;
result_140->start = start_140;
result_140->end = result_144->end;
result_140->num_children = 3;
result_140->children[0] = result_141;
result_140->children[1] = result_143;
result_140->children[2] = result_144;
result_140->id = 140;
exit_140:
if (result_140 != NULL) {
result_139 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_139->flags = 0;
result_139->type = ALTERNATIVE_T;
result_139->start = start_139;
result_139->end = result_140->end;
result_139->num_children = 1;
result_139->children[0] = result_140;
result_139->id = 139;
goto exit_139;
}
uint32_t start_145 = start_139;
rnode_t* result_145 = NULL;
uint32_t current_position_145 = start_145;
uint32_t start_146 = current_position_145;
rnode_t* result_146 = NULL;
uint32_t start_147 = start_146;
rnode_t* result_147 = NULL;
uint8_t bytesbuf_147[] = {93, };
uint8_t c_147;
for (uint32_t i_147 = 0; i_147 < 1; ++i_147) {
c_147 = bytesbuf_147[i_147];
if (i_147 + start_147 < text_length
    && c_147 == text[i_147 + start_147]) {
if (i_147 == 1 - 1) {
result_147 = malloc(sizeof(rnode_t));
result_147->flags = 0;
result_147->type = LITERAL_T;
result_147->start = start_147;
result_147->end = start_147 + 1;
result_147->num_children = 0;
result_147->id = 147;
}
} else {
break;
}
}
if (!result_147) {
result_146 = malloc(sizeof(rnode_t));
result_146->flags = 0;
result_146->type = NOT_T;
result_146->start = start_146;
result_146->end = start_146;
result_146->num_children = 0;
result_146->id = 146;
} else {
free_tree(result_147, IS_CACHED);
}
if (result_146 == NULL) {
goto exit_145;
}
current_position_145 = result_146->end;
uint32_t start_148 = current_position_145;
rnode_t* result_148 = NULL;
if (start_148 < text_length) {
uint8_t c_148 = text[start_148];
if (c_148 >= 0 && c_148 <= 255) {
result_148 = malloc(sizeof(rnode_t));
result_148->flags = 0;
result_148->type = RANGE_T;
result_148->start = start_148;
result_148->end = start_148 + 1;
result_148->num_children = 0;
result_148->id = 148;
}
}
if (result_148 == NULL) {
free_tree(result_146, IS_CACHED);
goto exit_145;
}
current_position_145 = result_148->end;
result_145 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_145->flags = 0;
result_145->type = SEQUENCE_T;
result_145->start = start_145;
result_145->end = result_148->end;
result_145->num_children = 2;
result_145->children[0] = result_146;
result_145->children[1] = result_148;
result_145->id = 145;
exit_145:
if (result_145 != NULL) {
result_139 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_139->flags = 0;
result_139->type = ALTERNATIVE_T;
result_139->start = start_139;
result_139->end = result_145->end;
result_139->num_children = 1;
result_139->children[0] = result_145;
result_139->id = 139;
goto exit_139;
}
exit_139:
if (result_139 != NULL) {
    append_stack(list_138, result_139);
    start_139 = result_139->end;
    ++num_children_138;
}
} while (result_139 != NULL);
result_138 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_138);
result_138->flags = DO_CAPTURE | 0;
result_138->type = STAR_T;
result_138->start = start_138;
result_138->num_children = num_children_138;
if (num_children_138) {
for (uint32_t i = 0; i < num_children_138; ++i) {
result_138->children[i] = list_138->arr[i];
}
result_138->end = ((rnode_t*)list_138->arr[num_children_138 - 1])->end;
} else {
result_138->end = start_138;
}
result_138->id = 138;
free_stack(list_138);
if (result_138 == NULL) {
free_tree(result_137, IS_CACHED);
goto exit_136;
}
current_position_136 = result_138->end;
uint32_t start_149 = current_position_136;
rnode_t* result_149 = NULL;
uint8_t bytesbuf_149[] = {93, };
uint8_t c_149;
for (uint32_t i_149 = 0; i_149 < 1; ++i_149) {
c_149 = bytesbuf_149[i_149];
if (i_149 + start_149 < text_length
    && c_149 == text[i_149 + start_149]) {
if (i_149 == 1 - 1) {
result_149 = malloc(sizeof(rnode_t));
result_149->flags = 0;
result_149->type = LITERAL_T;
result_149->start = start_149;
result_149->end = start_149 + 1;
result_149->num_children = 0;
result_149->id = 149;
}
} else {
break;
}
}
if (result_149 == NULL) {
free_tree(result_137, IS_CACHED);
free_tree(result_138, IS_CACHED);
goto exit_136;
}
current_position_136 = result_149->end;
result_136 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_136->flags = SEMANTIC_ACTION | 0;
result_136->type = SEQUENCE_T;
result_136->start = start_136;
result_136->end = result_149->end;
result_136->num_children = 3;
result_136->children[0] = result_137;
result_136->children[1] = result_138;
result_136->children[2] = result_149;
result_136->id = 136;
exit_136:
return result_136;
}
rnode_t* eval_code(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_150 = pos;
rnode_t* result_150 = NULL;
uint32_t current_position_150 = start_150;
uint32_t start_151 = current_position_150;
rnode_t* result_151 = NULL;
uint8_t bytesbuf_151[] = {123, 123, };
uint8_t c_151;
for (uint32_t i_151 = 0; i_151 < 2; ++i_151) {
c_151 = bytesbuf_151[i_151];
if (i_151 + start_151 < text_length
    && c_151 == text[i_151 + start_151]) {
if (i_151 == 2 - 1) {
result_151 = malloc(sizeof(rnode_t));
result_151->flags = 0;
result_151->type = LITERAL_T;
result_151->start = start_151;
result_151->end = start_151 + 2;
result_151->num_children = 0;
result_151->id = 151;
}
} else {
break;
}
}
if (result_151 == NULL) {
goto exit_150;
}
current_position_150 = result_151->end;
uint32_t start_152 = current_position_150;
rnode_t* result_152 = NULL;
uint32_t start_153 = start_152;
rnode_t* result_153 = NULL;
uint32_t num_children_152 = 0;
stack_t* list_152 = init_stack(64);
do {
result_153 = NULL;
uint32_t start_154 = start_153;
rnode_t* result_154 = NULL;
uint32_t current_position_154 = start_154;
uint32_t start_155 = current_position_154;
rnode_t* result_155 = NULL;
uint32_t start_156 = start_155;
rnode_t* result_156 = NULL;
uint8_t bytesbuf_156[] = {92, };
uint8_t c_156;
for (uint32_t i_156 = 0; i_156 < 1; ++i_156) {
c_156 = bytesbuf_156[i_156];
if (i_156 + start_156 < text_length
    && c_156 == text[i_156 + start_156]) {
if (i_156 == 1 - 1) {
result_156 = malloc(sizeof(rnode_t));
result_156->flags = 0;
result_156->type = LITERAL_T;
result_156->start = start_156;
result_156->end = start_156 + 1;
result_156->num_children = 0;
result_156->id = 156;
}
} else {
break;
}
}
if (result_156) {
result_155 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_155->flags = 0;
result_155->type = AND_T;
result_155->start = start_155;
result_155->end = start_155;
result_155->num_children = 1;
result_155->children[0] = result_156;
result_155->id = 155;
}
if (result_155 == NULL) {
goto exit_154;
}
current_position_154 = result_155->end;
uint32_t start_157 = current_position_154;
rnode_t* result_157 = NULL;
if (start_157 < text_length) {
uint8_t c_157 = text[start_157];
if (c_157 >= 0 && c_157 <= 255) {
result_157 = malloc(sizeof(rnode_t));
result_157->flags = 0;
result_157->type = RANGE_T;
result_157->start = start_157;
result_157->end = start_157 + 1;
result_157->num_children = 0;
result_157->id = 157;
}
}
if (result_157 == NULL) {
free_tree(result_155, IS_CACHED);
goto exit_154;
}
current_position_154 = result_157->end;
uint32_t start_158 = current_position_154;
rnode_t* result_158 = NULL;
if (start_158 < text_length) {
uint8_t c_158 = text[start_158];
if (c_158 >= 0 && c_158 <= 255) {
result_158 = malloc(sizeof(rnode_t));
result_158->flags = 0;
result_158->type = RANGE_T;
result_158->start = start_158;
result_158->end = start_158 + 1;
result_158->num_children = 0;
result_158->id = 158;
}
}
if (result_158 == NULL) {
free_tree(result_155, IS_CACHED);
free_tree(result_157, IS_CACHED);
goto exit_154;
}
current_position_154 = result_158->end;
result_154 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_154->flags = 0;
result_154->type = SEQUENCE_T;
result_154->start = start_154;
result_154->end = result_158->end;
result_154->num_children = 3;
result_154->children[0] = result_155;
result_154->children[1] = result_157;
result_154->children[2] = result_158;
result_154->id = 154;
exit_154:
if (result_154 != NULL) {
result_153 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_153->flags = 0;
result_153->type = ALTERNATIVE_T;
result_153->start = start_153;
result_153->end = result_154->end;
result_153->num_children = 1;
result_153->children[0] = result_154;
result_153->id = 153;
goto exit_153;
}
uint32_t start_159 = start_153;
rnode_t* result_159 = NULL;
uint32_t current_position_159 = start_159;
uint32_t start_160 = current_position_159;
rnode_t* result_160 = NULL;
uint32_t start_161 = start_160;
rnode_t* result_161 = NULL;
uint8_t bytesbuf_161[] = {125, 125, };
uint8_t c_161;
for (uint32_t i_161 = 0; i_161 < 2; ++i_161) {
c_161 = bytesbuf_161[i_161];
if (i_161 + start_161 < text_length
    && c_161 == text[i_161 + start_161]) {
if (i_161 == 2 - 1) {
result_161 = malloc(sizeof(rnode_t));
result_161->flags = 0;
result_161->type = LITERAL_T;
result_161->start = start_161;
result_161->end = start_161 + 2;
result_161->num_children = 0;
result_161->id = 161;
}
} else {
break;
}
}
if (!result_161) {
result_160 = malloc(sizeof(rnode_t));
result_160->flags = 0;
result_160->type = NOT_T;
result_160->start = start_160;
result_160->end = start_160;
result_160->num_children = 0;
result_160->id = 160;
} else {
free_tree(result_161, IS_CACHED);
}
if (result_160 == NULL) {
goto exit_159;
}
current_position_159 = result_160->end;
uint32_t start_162 = current_position_159;
rnode_t* result_162 = NULL;
if (start_162 < text_length) {
uint8_t c_162 = text[start_162];
if (c_162 >= 0 && c_162 <= 255) {
result_162 = malloc(sizeof(rnode_t));
result_162->flags = 0;
result_162->type = RANGE_T;
result_162->start = start_162;
result_162->end = start_162 + 1;
result_162->num_children = 0;
result_162->id = 162;
}
}
if (result_162 == NULL) {
free_tree(result_160, IS_CACHED);
goto exit_159;
}
current_position_159 = result_162->end;
result_159 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_159->flags = 0;
result_159->type = SEQUENCE_T;
result_159->start = start_159;
result_159->end = result_162->end;
result_159->num_children = 2;
result_159->children[0] = result_160;
result_159->children[1] = result_162;
result_159->id = 159;
exit_159:
if (result_159 != NULL) {
result_153 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_153->flags = 0;
result_153->type = ALTERNATIVE_T;
result_153->start = start_153;
result_153->end = result_159->end;
result_153->num_children = 1;
result_153->children[0] = result_159;
result_153->id = 153;
goto exit_153;
}
exit_153:
if (result_153 != NULL) {
    append_stack(list_152, result_153);
    start_153 = result_153->end;
    ++num_children_152;
}
} while (result_153 != NULL);
result_152 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_152);
result_152->flags = DO_CAPTURE | 0;
result_152->type = STAR_T;
result_152->start = start_152;
result_152->num_children = num_children_152;
if (num_children_152) {
for (uint32_t i = 0; i < num_children_152; ++i) {
result_152->children[i] = list_152->arr[i];
}
result_152->end = ((rnode_t*)list_152->arr[num_children_152 - 1])->end;
} else {
result_152->end = start_152;
}
result_152->id = 152;
free_stack(list_152);
if (result_152 == NULL) {
free_tree(result_151, IS_CACHED);
goto exit_150;
}
current_position_150 = result_152->end;
uint32_t start_163 = current_position_150;
rnode_t* result_163 = NULL;
uint8_t bytesbuf_163[] = {125, 125, };
uint8_t c_163;
for (uint32_t i_163 = 0; i_163 < 2; ++i_163) {
c_163 = bytesbuf_163[i_163];
if (i_163 + start_163 < text_length
    && c_163 == text[i_163 + start_163]) {
if (i_163 == 2 - 1) {
result_163 = malloc(sizeof(rnode_t));
result_163->flags = 0;
result_163->type = LITERAL_T;
result_163->start = start_163;
result_163->end = start_163 + 2;
result_163->num_children = 0;
result_163->id = 163;
}
} else {
break;
}
}
if (result_163 == NULL) {
free_tree(result_151, IS_CACHED);
free_tree(result_152, IS_CACHED);
goto exit_150;
}
current_position_150 = result_163->end;
result_150 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_150->flags = 0;
result_150->type = SEQUENCE_T;
result_150->start = start_150;
result_150->end = result_163->end;
result_150->num_children = 3;
result_150->children[0] = result_151;
result_150->children[1] = result_152;
result_150->children[2] = result_163;
result_150->id = 150;
exit_150:
return result_150;
}
rnode_t* eval_dot(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_164 = pos;
rnode_t* result_164 = NULL;
uint8_t bytesbuf_164[] = {46, };
uint8_t c_164;
for (uint32_t i_164 = 0; i_164 < 1; ++i_164) {
c_164 = bytesbuf_164[i_164];
if (i_164 + start_164 < text_length
    && c_164 == text[i_164 + start_164]) {
if (i_164 == 1 - 1) {
result_164 = malloc(sizeof(rnode_t));
result_164->flags = SEMANTIC_ACTION | 0;
result_164->type = LITERAL_T;
result_164->start = start_164;
result_164->end = start_164 + 1;
result_164->num_children = 0;
result_164->id = 164;
}
} else {
break;
}
}
return result_164;
}
#define c(x) (((capture_t*)get_stack(context->capture, x))->str)
#define s(x) (((capture_t*)get_stack(context->capture, x))->start)
#define e(x) (((capture_t*)get_stack(context->capture, x))->end)
#define ccount (context->capture->len)
void semantic_action_0(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** r = (ast_node_t**)(context->alias[4]->arr);
uint32_t countr = context->alias[4]->len;
result = ast_grammar(r, countr);
context->result = result;
return;
}
void alias_allocs_0(context_t* context) {
context->alias[4] = init_stack(16);
return;
}
void semantic_action_18(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** b = (ast_node_t**)(context->alias[24]->arr);
uint32_t countb = context->alias[24]->len;
result = ast_rule(c(0), *b);
context->result = result;
return;
}
void alias_allocs_18(context_t* context) {
context->alias[24] = init_stack(16);
return;
}
void semantic_action_31(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[31]->arr);
uint32_t counto = context->alias[31]->len;
result = *o;
context->result = result;
return;
}
void alias_allocs_31(context_t* context) {
context->alias[31] = init_stack(16);
return;
}
void semantic_action_32(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** first = (ast_node_t**)(context->alias[33]->arr);
uint32_t countfirst = context->alias[33]->len;
ast_node_t** rest = (ast_node_t**)(context->alias[39]->arr);
uint32_t countrest = context->alias[39]->len;
result = ast_Alt(first, rest, countrest + 1);
context->result = result;
return;
}
void alias_allocs_32(context_t* context) {
context->alias[33] = init_stack(16);
context->alias[39] = init_stack(16);
return;
}
void semantic_action_40(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** first = (ast_node_t**)(context->alias[41]->arr);
uint32_t countfirst = context->alias[41]->len;
ast_node_t** rest = (ast_node_t**)(context->alias[45]->arr);
uint32_t countrest = context->alias[45]->len;
result = ast_Seq(first, rest, countrest + 1);
context->result = result;
return;
}
void alias_allocs_40(context_t* context) {
context->alias[41] = init_stack(16);
context->alias[45] = init_stack(16);
return;
}
void semantic_action_47(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[48]->arr);
uint32_t counto = context->alias[48]->len;
if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}
context->result = result;
return;
}
void semantic_action_54(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[55]->arr);
uint32_t counto = context->alias[55]->len;
if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}
context->result = result;
return;
}
void semantic_action_61(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[62]->arr);
uint32_t counto = context->alias[62]->len;
if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}
context->result = result;
return;
}
void alias_allocs_47(context_t* context) {
context->alias[48] = init_stack(16);
return;
}
void alias_allocs_54(context_t* context) {
context->alias[55] = init_stack(16);
return;
}
void alias_allocs_61(context_t* context) {
context->alias[62] = init_stack(16);
return;
}
void semantic_action_69(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[72]->arr);
uint32_t counto = context->alias[72]->len;
result = ast_And(*o);
context->result = result;
return;
}
void semantic_action_73(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[76]->arr);
uint32_t counto = context->alias[76]->len;
result = ast_Not(*o);
context->result = result;
return;
}
void alias_allocs_69(context_t* context) {
context->alias[72] = init_stack(16);
return;
}
void alias_allocs_73(context_t* context) {
context->alias[76] = init_stack(16);
return;
}
void semantic_action_80(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[81]->arr);
uint32_t counto = context->alias[81]->len;
result = ast_Star(*o);
context->result = result;
return;
}
void semantic_action_84(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[85]->arr);
uint32_t counto = context->alias[85]->len;
result = ast_Plus(*o);
context->result = result;
return;
}
void semantic_action_88(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[89]->arr);
uint32_t counto = context->alias[89]->len;
result = ast_Option(*o);
context->result = result;
return;
}
void alias_allocs_80(context_t* context) {
context->alias[81] = init_stack(16);
return;
}
void alias_allocs_84(context_t* context) {
context->alias[85] = init_stack(16);
return;
}
void alias_allocs_88(context_t* context) {
context->alias[89] = init_stack(16);
return;
}
void semantic_action_96(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[99]->arr);
uint32_t counto = context->alias[99]->len;
result = *o;
context->result = result;
return;
}
void semantic_action_102(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[105]->arr);
uint32_t counto = context->alias[105]->len;
result = ast_Capture(*o);
context->result = result;
return;
}
void semantic_action_108(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[108]->arr);
uint32_t counto = context->alias[108]->len;
result = *o;
context->result = result;
return;
}
void alias_allocs_96(context_t* context) {
context->alias[99] = init_stack(16);
return;
}
void alias_allocs_102(context_t* context) {
context->alias[105] = init_stack(16);
return;
}
void alias_allocs_108(context_t* context) {
context->alias[108] = init_stack(16);
return;
}
void semantic_action_110(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[110]->arr);
uint32_t counto = context->alias[110]->len;
result = *o;
context->result = result;
return;
}
void semantic_action_111(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[111]->arr);
uint32_t counto = context->alias[111]->len;
result = *o;
context->result = result;
return;
}
void semantic_action_112(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[112]->arr);
uint32_t counto = context->alias[112]->len;
result = *o;
context->result = result;
return;
}
void semantic_action_113(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[113]->arr);
uint32_t counto = context->alias[113]->len;
result = *o;
context->result = result;
return;
}
void alias_allocs_110(context_t* context) {
context->alias[110] = init_stack(16);
return;
}
void alias_allocs_111(context_t* context) {
context->alias[111] = init_stack(16);
return;
}
void alias_allocs_112(context_t* context) {
context->alias[112] = init_stack(16);
return;
}
void alias_allocs_113(context_t* context) {
context->alias[113] = init_stack(16);
return;
}
void semantic_action_115(context_t* context) {
ast_node_t* result = NULL;
result = ast_AliasedNontm(c(1), c(0));
context->result = result;
return;
}
void semantic_action_121(context_t* context) {
ast_node_t* result = NULL;
result = ast_Nontm(c(0));
context->result = result;
return;
}
void alias_allocs_115(context_t* context) {
return;
}
void alias_allocs_121(context_t* context) {
return;
}
void semantic_action_122(context_t* context) {
ast_node_t* result = NULL;
result = ast_Literal(c(0));
context->result = result;
return;
}
void alias_allocs_122(context_t* context) {
return;
}
void semantic_action_136(context_t* context) {
ast_node_t* result = NULL;
result = ast_CClass(c(0));
context->result = result;
return;
}
void alias_allocs_136(context_t* context) {
return;
}
void semantic_action_164(context_t* context) {
ast_node_t* result = NULL;
result = ast_dot();
context->result = result;
return;
}
void alias_allocs_164(context_t* context) {
return;
}
