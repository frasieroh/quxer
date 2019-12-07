/*
    This file was automatically generated! To make meaningful changes (read:
    not just includes), edit peg.txt in the root directory and run quxer.
*/

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
#define EVAL_dot 21
#define EVAL_code 22
evalfcn_t eval_map[] = {eval_grammar, eval_ws, eval_wsp, eval_rule, eval_name, eval_body, eval_alt, eval_seq, eval_operator, eval_prefix, eval_and, eval_not, eval_postfix, eval_star, eval_plus, eval_option, eval_group, eval_final, eval_nonterminal, eval_literal, eval_cclass, eval_dot, eval_code, };
char* name_map[] = {"grammar", "ws", "wsp", "rule", "name", "body", "alt", "seq", "operator", "prefix", "and", "not", "postfix", "star", "plus", "option", "group", "final", "nonterminal", "literal", "cclass", "dot", "code", };
uint32_t num_rules = 23;
actionfcn_t semantic_action_map[160] = {[0] = semantic_action_0, [16] = semantic_action_16, [29] = semantic_action_29, [30] = semantic_action_30, [38] = semantic_action_38, [45] = semantic_action_45, [51] = semantic_action_51, [57] = semantic_action_57, [64] = semantic_action_64, [68] = semantic_action_68, [75] = semantic_action_75, [79] = semantic_action_79, [83] = semantic_action_83, [91] = semantic_action_91, [97] = semantic_action_97, [103] = semantic_action_103, [105] = semantic_action_105, [106] = semantic_action_106, [107] = semantic_action_107, [108] = semantic_action_108, [110] = semantic_action_110, [116] = semantic_action_116, [117] = semantic_action_117, [131] = semantic_action_131, [145] = semantic_action_145, };
uint32_t num_nodes = 160;
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
arraylist_t* list_1 = init_arraylist(64);
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
    append_arraylist(&list_1, result_2);
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
free(list_1);
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
result_0 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_0->flags = SEMANTIC_ACTION | 0;
result_0->type = SEQUENCE_T;
result_0->start = start_0;
result_0->end = result_5->end;
result_0->num_children = 2;
result_0->children[0] = result_1;
result_0->children[1] = result_5;
result_0->id = 0;
exit_0:
return result_0;
}
rnode_t* eval_ws(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_6 = pos;
rnode_t* result_6 = NULL;
uint32_t start_7 = start_6;
rnode_t* result_7 = NULL;
uint32_t num_children_6 = 0;
arraylist_t* list_6 = init_arraylist(64);
do {
result_7 = NULL;
uint32_t start_8 = start_7;
rnode_t* result_8 = NULL;
uint8_t bytesbuf_8[] = {32, };
uint8_t c_8;
for (uint32_t i_8 = 0; i_8 < 1; ++i_8) {
c_8 = bytesbuf_8[i_8];
if (i_8 + start_8 < text_length
    && c_8 == text[i_8 + start_8]) {
if (i_8 == 1 - 1) {
result_8 = malloc(sizeof(rnode_t));
result_8->flags = 0;
result_8->type = LITERAL_T;
result_8->start = start_8;
result_8->end = start_8 + 1;
result_8->num_children = 0;
result_8->id = 8;
}
} else {
break;
}
}
if (result_8 != NULL) {
result_7 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_7->flags = 0;
result_7->type = ALTERNATIVE_T;
result_7->start = start_7;
result_7->end = result_8->end;
result_7->num_children = 1;
result_7->children[0] = result_8;
result_7->id = 7;
goto exit_7;
}
uint32_t start_9 = start_7;
rnode_t* result_9 = NULL;
uint8_t bytesbuf_9[] = {10, };
uint8_t c_9;
for (uint32_t i_9 = 0; i_9 < 1; ++i_9) {
c_9 = bytesbuf_9[i_9];
if (i_9 + start_9 < text_length
    && c_9 == text[i_9 + start_9]) {
if (i_9 == 1 - 1) {
result_9 = malloc(sizeof(rnode_t));
result_9->flags = 0;
result_9->type = LITERAL_T;
result_9->start = start_9;
result_9->end = start_9 + 1;
result_9->num_children = 0;
result_9->id = 9;
}
} else {
break;
}
}
if (result_9 != NULL) {
result_7 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_7->flags = 0;
result_7->type = ALTERNATIVE_T;
result_7->start = start_7;
result_7->end = result_9->end;
result_7->num_children = 1;
result_7->children[0] = result_9;
result_7->id = 7;
goto exit_7;
}
uint32_t start_10 = start_7;
rnode_t* result_10 = NULL;
uint8_t bytesbuf_10[] = {9, };
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
result_7 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_7->flags = 0;
result_7->type = ALTERNATIVE_T;
result_7->start = start_7;
result_7->end = result_10->end;
result_7->num_children = 1;
result_7->children[0] = result_10;
result_7->id = 7;
goto exit_7;
}
exit_7:
if (result_7 != NULL) {
    append_arraylist(&list_6, result_7);
    start_7 = result_7->end;
    ++num_children_6;
}
} while (result_7 != NULL);
result_6 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_6);
result_6->flags = 0;
result_6->type = STAR_T;
result_6->start = start_6;
result_6->num_children = num_children_6;
if (num_children_6) {
for (uint32_t i = 0; i < num_children_6; ++i) {
result_6->children[i] = list_6->arr[i];
}
result_6->end = ((rnode_t*)list_6->arr[num_children_6 - 1])->end;
} else {
result_6->end = start_6;
}
result_6->id = 6;
free(list_6);
return result_6;
}
rnode_t* eval_wsp(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_11 = pos;
rnode_t* result_11 = NULL;
uint32_t start_12 = start_11;
rnode_t* result_12 = NULL;
uint32_t num_children_11 = 0;
arraylist_t* list_11 = init_arraylist(64);
do {
result_12 = NULL;
uint32_t start_13 = start_12;
rnode_t* result_13 = NULL;
uint8_t bytesbuf_13[] = {32, };
uint8_t c_13;
for (uint32_t i_13 = 0; i_13 < 1; ++i_13) {
c_13 = bytesbuf_13[i_13];
if (i_13 + start_13 < text_length
    && c_13 == text[i_13 + start_13]) {
if (i_13 == 1 - 1) {
result_13 = malloc(sizeof(rnode_t));
result_13->flags = 0;
result_13->type = LITERAL_T;
result_13->start = start_13;
result_13->end = start_13 + 1;
result_13->num_children = 0;
result_13->id = 13;
}
} else {
break;
}
}
if (result_13 != NULL) {
result_12 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_12->flags = 0;
result_12->type = ALTERNATIVE_T;
result_12->start = start_12;
result_12->end = result_13->end;
result_12->num_children = 1;
result_12->children[0] = result_13;
result_12->id = 12;
goto exit_12;
}
uint32_t start_14 = start_12;
rnode_t* result_14 = NULL;
uint8_t bytesbuf_14[] = {10, };
uint8_t c_14;
for (uint32_t i_14 = 0; i_14 < 1; ++i_14) {
c_14 = bytesbuf_14[i_14];
if (i_14 + start_14 < text_length
    && c_14 == text[i_14 + start_14]) {
if (i_14 == 1 - 1) {
result_14 = malloc(sizeof(rnode_t));
result_14->flags = 0;
result_14->type = LITERAL_T;
result_14->start = start_14;
result_14->end = start_14 + 1;
result_14->num_children = 0;
result_14->id = 14;
}
} else {
break;
}
}
if (result_14 != NULL) {
result_12 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_12->flags = 0;
result_12->type = ALTERNATIVE_T;
result_12->start = start_12;
result_12->end = result_14->end;
result_12->num_children = 1;
result_12->children[0] = result_14;
result_12->id = 12;
goto exit_12;
}
uint32_t start_15 = start_12;
rnode_t* result_15 = NULL;
uint8_t bytesbuf_15[] = {9, };
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
result_12 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_12->flags = 0;
result_12->type = ALTERNATIVE_T;
result_12->start = start_12;
result_12->end = result_15->end;
result_12->num_children = 1;
result_12->children[0] = result_15;
result_12->id = 12;
goto exit_12;
}
exit_12:
if (result_12 != NULL) {
    append_arraylist(&list_11, result_12);
    start_12 = result_12->end;
    ++num_children_11;
}
} while (result_12 != NULL);
if (num_children_11) {
result_11 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_11);
result_11->flags = 0;
result_11->type = PLUS_T;
result_11->start = start_11;
result_11->num_children = num_children_11;
for (uint32_t i = 0; i < num_children_11; ++i) {
result_11->children[i] = list_11->arr[i];
}
result_11->end = ((rnode_t*)list_11->arr[num_children_11 - 1])->end;
result_11->id = 11;
}
free(list_11);
return result_11;
}
rnode_t* eval_rule(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_16 = pos;
rnode_t* result_16 = NULL;
uint32_t current_position_16 = start_16;
uint32_t start_17 = current_position_16;
rnode_t* result_17 = NULL;
uint8_t bytesbuf_17[] = {126, };
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
if (result_17 == NULL) {
goto exit_16;
}
current_position_16 = result_17->end;
uint32_t start_18 = current_position_16;
rnode_t* result_18 = NULL;
rnode_t* result_18_nt = call_eval(EVAL_name, state, text, text_length, start_18);
if (result_18_nt) {
result_18 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_18->flags = DO_CAPTURE | 0;
result_18->type = NONTERMINAL_T;
result_18->start = start_18;
result_18->end = result_18_nt->end;
result_18->num_children = 1;
result_18->children[0] = result_18_nt;
result_18->id = 18;
}
if (result_18 == NULL) {
free_tree(result_17, IS_CACHED);
goto exit_16;
}
current_position_16 = result_18->end;
uint32_t start_19 = current_position_16;
rnode_t* result_19 = NULL;
rnode_t* result_19_nt = call_eval(EVAL_ws, state, text, text_length, start_19);
if (result_19_nt) {
result_19 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_19->flags = 0;
result_19->type = NONTERMINAL_T;
result_19->start = start_19;
result_19->end = result_19_nt->end;
result_19->num_children = 1;
result_19->children[0] = result_19_nt;
result_19->id = 19;
}
if (result_19 == NULL) {
free_tree(result_17, IS_CACHED);
free_tree(result_18, IS_CACHED);
goto exit_16;
}
current_position_16 = result_19->end;
uint32_t start_20 = current_position_16;
rnode_t* result_20 = NULL;
uint8_t bytesbuf_20[] = {61, };
uint8_t c_20;
for (uint32_t i_20 = 0; i_20 < 1; ++i_20) {
c_20 = bytesbuf_20[i_20];
if (i_20 + start_20 < text_length
    && c_20 == text[i_20 + start_20]) {
if (i_20 == 1 - 1) {
result_20 = malloc(sizeof(rnode_t));
result_20->flags = 0;
result_20->type = LITERAL_T;
result_20->start = start_20;
result_20->end = start_20 + 1;
result_20->num_children = 0;
result_20->id = 20;
}
} else {
break;
}
}
if (result_20 == NULL) {
free_tree(result_17, IS_CACHED);
free_tree(result_18, IS_CACHED);
free_tree(result_19, IS_CACHED);
goto exit_16;
}
current_position_16 = result_20->end;
uint32_t start_21 = current_position_16;
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
free_tree(result_17, IS_CACHED);
free_tree(result_18, IS_CACHED);
free_tree(result_19, IS_CACHED);
free_tree(result_20, IS_CACHED);
goto exit_16;
}
current_position_16 = result_21->end;
uint32_t start_22 = current_position_16;
rnode_t* result_22 = NULL;
rnode_t* result_22_nt = call_eval(EVAL_body, state, text, text_length, start_22);
if (result_22_nt) {
result_22 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_22->flags = ALIAS | 0;
result_22->type = NONTERMINAL_T;
result_22->start = start_22;
result_22->end = result_22_nt->end;
result_22->num_children = 1;
result_22->children[0] = result_22_nt;
result_22->id = 22;
}
if (result_22 == NULL) {
free_tree(result_17, IS_CACHED);
free_tree(result_18, IS_CACHED);
free_tree(result_19, IS_CACHED);
free_tree(result_20, IS_CACHED);
free_tree(result_21, IS_CACHED);
goto exit_16;
}
current_position_16 = result_22->end;
result_16 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 6);
result_16->flags = SEMANTIC_ACTION | 0;
result_16->type = SEQUENCE_T;
result_16->start = start_16;
result_16->end = result_22->end;
result_16->num_children = 6;
result_16->children[0] = result_17;
result_16->children[1] = result_18;
result_16->children[2] = result_19;
result_16->children[3] = result_20;
result_16->children[4] = result_21;
result_16->children[5] = result_22;
result_16->id = 16;
exit_16:
return result_16;
}
rnode_t* eval_name(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_23 = pos;
rnode_t* result_23 = NULL;
uint32_t start_24 = start_23;
rnode_t* result_24 = NULL;
uint32_t num_children_23 = 0;
arraylist_t* list_23 = init_arraylist(64);
do {
result_24 = NULL;
uint32_t start_25 = start_24;
rnode_t* result_25 = NULL;
if (start_25 < text_length) {
uint8_t c_25 = text[start_25];
if (c_25 >= 65 && c_25 <= 90) {
result_25 = malloc(sizeof(rnode_t));
result_25->flags = 0;
result_25->type = RANGE_T;
result_25->start = start_25;
result_25->end = start_25 + 1;
result_25->num_children = 0;
result_25->id = 25;
}
}
if (result_25 != NULL) {
result_24 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_24->flags = 0;
result_24->type = ALTERNATIVE_T;
result_24->start = start_24;
result_24->end = result_25->end;
result_24->num_children = 1;
result_24->children[0] = result_25;
result_24->id = 24;
goto exit_24;
}
uint32_t start_26 = start_24;
rnode_t* result_26 = NULL;
if (start_26 < text_length) {
uint8_t c_26 = text[start_26];
if (c_26 >= 97 && c_26 <= 122) {
result_26 = malloc(sizeof(rnode_t));
result_26->flags = 0;
result_26->type = RANGE_T;
result_26->start = start_26;
result_26->end = start_26 + 1;
result_26->num_children = 0;
result_26->id = 26;
}
}
if (result_26 != NULL) {
result_24 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_24->flags = 0;
result_24->type = ALTERNATIVE_T;
result_24->start = start_24;
result_24->end = result_26->end;
result_24->num_children = 1;
result_24->children[0] = result_26;
result_24->id = 24;
goto exit_24;
}
uint32_t start_27 = start_24;
rnode_t* result_27 = NULL;
if (start_27 < text_length) {
uint8_t c_27 = text[start_27];
if (c_27 >= 48 && c_27 <= 57) {
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
result_24 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_24->flags = 0;
result_24->type = ALTERNATIVE_T;
result_24->start = start_24;
result_24->end = result_27->end;
result_24->num_children = 1;
result_24->children[0] = result_27;
result_24->id = 24;
goto exit_24;
}
uint32_t start_28 = start_24;
rnode_t* result_28 = NULL;
uint8_t bytesbuf_28[] = {95, };
uint8_t c_28;
for (uint32_t i_28 = 0; i_28 < 1; ++i_28) {
c_28 = bytesbuf_28[i_28];
if (i_28 + start_28 < text_length
    && c_28 == text[i_28 + start_28]) {
if (i_28 == 1 - 1) {
result_28 = malloc(sizeof(rnode_t));
result_28->flags = 0;
result_28->type = LITERAL_T;
result_28->start = start_28;
result_28->end = start_28 + 1;
result_28->num_children = 0;
result_28->id = 28;
}
} else {
break;
}
}
if (result_28 != NULL) {
result_24 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_24->flags = 0;
result_24->type = ALTERNATIVE_T;
result_24->start = start_24;
result_24->end = result_28->end;
result_24->num_children = 1;
result_24->children[0] = result_28;
result_24->id = 24;
goto exit_24;
}
exit_24:
if (result_24 != NULL) {
    append_arraylist(&list_23, result_24);
    start_24 = result_24->end;
    ++num_children_23;
}
} while (result_24 != NULL);
if (num_children_23) {
result_23 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_23);
result_23->flags = 0;
result_23->type = PLUS_T;
result_23->start = start_23;
result_23->num_children = num_children_23;
for (uint32_t i = 0; i < num_children_23; ++i) {
result_23->children[i] = list_23->arr[i];
}
result_23->end = ((rnode_t*)list_23->arr[num_children_23 - 1])->end;
result_23->id = 23;
}
free(list_23);
return result_23;
}
rnode_t* eval_body(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_29 = pos;
rnode_t* result_29 = NULL;
rnode_t* result_29_nt = call_eval(EVAL_alt, state, text, text_length, start_29);
if (result_29_nt) {
result_29 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_29->flags = SEMANTIC_ACTION | ALIAS | 0;
result_29->type = NONTERMINAL_T;
result_29->start = start_29;
result_29->end = result_29_nt->end;
result_29->num_children = 1;
result_29->children[0] = result_29_nt;
result_29->id = 29;
}
return result_29;
}
rnode_t* eval_alt(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_30 = pos;
rnode_t* result_30 = NULL;
uint32_t current_position_30 = start_30;
uint32_t start_31 = current_position_30;
rnode_t* result_31 = NULL;
rnode_t* result_31_nt = call_eval(EVAL_seq, state, text, text_length, start_31);
if (result_31_nt) {
result_31 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_31->flags = ALIAS | 0;
result_31->type = NONTERMINAL_T;
result_31->start = start_31;
result_31->end = result_31_nt->end;
result_31->num_children = 1;
result_31->children[0] = result_31_nt;
result_31->id = 31;
}
if (result_31 == NULL) {
goto exit_30;
}
current_position_30 = result_31->end;
uint32_t start_32 = current_position_30;
rnode_t* result_32 = NULL;
uint32_t start_33 = start_32;
rnode_t* result_33 = NULL;
uint32_t num_children_32 = 0;
arraylist_t* list_32 = init_arraylist(64);
do {
result_33 = NULL;
uint32_t current_position_33 = start_33;
uint32_t start_34 = current_position_33;
rnode_t* result_34 = NULL;
rnode_t* result_34_nt = call_eval(EVAL_ws, state, text, text_length, start_34);
if (result_34_nt) {
result_34 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_34->flags = 0;
result_34->type = NONTERMINAL_T;
result_34->start = start_34;
result_34->end = result_34_nt->end;
result_34->num_children = 1;
result_34->children[0] = result_34_nt;
result_34->id = 34;
}
if (result_34 == NULL) {
goto exit_33;
}
current_position_33 = result_34->end;
uint32_t start_35 = current_position_33;
rnode_t* result_35 = NULL;
uint8_t bytesbuf_35[] = {47, };
uint8_t c_35;
for (uint32_t i_35 = 0; i_35 < 1; ++i_35) {
c_35 = bytesbuf_35[i_35];
if (i_35 + start_35 < text_length
    && c_35 == text[i_35 + start_35]) {
if (i_35 == 1 - 1) {
result_35 = malloc(sizeof(rnode_t));
result_35->flags = 0;
result_35->type = LITERAL_T;
result_35->start = start_35;
result_35->end = start_35 + 1;
result_35->num_children = 0;
result_35->id = 35;
}
} else {
break;
}
}
if (result_35 == NULL) {
free_tree(result_34, IS_CACHED);
goto exit_33;
}
current_position_33 = result_35->end;
uint32_t start_36 = current_position_33;
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
free_tree(result_34, IS_CACHED);
free_tree(result_35, IS_CACHED);
goto exit_33;
}
current_position_33 = result_36->end;
uint32_t start_37 = current_position_33;
rnode_t* result_37 = NULL;
rnode_t* result_37_nt = call_eval(EVAL_seq, state, text, text_length, start_37);
if (result_37_nt) {
result_37 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_37->flags = ALIAS | 0;
result_37->type = NONTERMINAL_T;
result_37->start = start_37;
result_37->end = result_37_nt->end;
result_37->num_children = 1;
result_37->children[0] = result_37_nt;
result_37->id = 37;
}
if (result_37 == NULL) {
free_tree(result_34, IS_CACHED);
free_tree(result_35, IS_CACHED);
free_tree(result_36, IS_CACHED);
goto exit_33;
}
current_position_33 = result_37->end;
result_33 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 4);
result_33->flags = 0;
result_33->type = SEQUENCE_T;
result_33->start = start_33;
result_33->end = result_37->end;
result_33->num_children = 4;
result_33->children[0] = result_34;
result_33->children[1] = result_35;
result_33->children[2] = result_36;
result_33->children[3] = result_37;
result_33->id = 33;
exit_33:
if (result_33 != NULL) {
    append_arraylist(&list_32, result_33);
    start_33 = result_33->end;
    ++num_children_32;
}
} while (result_33 != NULL);
result_32 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_32);
result_32->flags = 0;
result_32->type = STAR_T;
result_32->start = start_32;
result_32->num_children = num_children_32;
if (num_children_32) {
for (uint32_t i = 0; i < num_children_32; ++i) {
result_32->children[i] = list_32->arr[i];
}
result_32->end = ((rnode_t*)list_32->arr[num_children_32 - 1])->end;
} else {
result_32->end = start_32;
}
result_32->id = 32;
free(list_32);
if (result_32 == NULL) {
free_tree(result_31, IS_CACHED);
goto exit_30;
}
current_position_30 = result_32->end;
result_30 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_30->flags = SEMANTIC_ACTION | 0;
result_30->type = SEQUENCE_T;
result_30->start = start_30;
result_30->end = result_32->end;
result_30->num_children = 2;
result_30->children[0] = result_31;
result_30->children[1] = result_32;
result_30->id = 30;
exit_30:
return result_30;
}
rnode_t* eval_seq(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_38 = pos;
rnode_t* result_38 = NULL;
uint32_t current_position_38 = start_38;
uint32_t start_39 = current_position_38;
rnode_t* result_39 = NULL;
rnode_t* result_39_nt = call_eval(EVAL_operator, state, text, text_length, start_39);
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
goto exit_38;
}
current_position_38 = result_39->end;
uint32_t start_40 = current_position_38;
rnode_t* result_40 = NULL;
uint32_t start_41 = start_40;
rnode_t* result_41 = NULL;
uint32_t num_children_40 = 0;
arraylist_t* list_40 = init_arraylist(64);
do {
result_41 = NULL;
uint32_t current_position_41 = start_41;
uint32_t start_42 = current_position_41;
rnode_t* result_42 = NULL;
rnode_t* result_42_nt = call_eval(EVAL_wsp, state, text, text_length, start_42);
if (result_42_nt) {
result_42 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_42->flags = 0;
result_42->type = NONTERMINAL_T;
result_42->start = start_42;
result_42->end = result_42_nt->end;
result_42->num_children = 1;
result_42->children[0] = result_42_nt;
result_42->id = 42;
}
if (result_42 == NULL) {
goto exit_41;
}
current_position_41 = result_42->end;
uint32_t start_43 = current_position_41;
rnode_t* result_43 = NULL;
rnode_t* result_43_nt = call_eval(EVAL_operator, state, text, text_length, start_43);
if (result_43_nt) {
result_43 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_43->flags = ALIAS | 0;
result_43->type = NONTERMINAL_T;
result_43->start = start_43;
result_43->end = result_43_nt->end;
result_43->num_children = 1;
result_43->children[0] = result_43_nt;
result_43->id = 43;
}
if (result_43 == NULL) {
free_tree(result_42, IS_CACHED);
goto exit_41;
}
current_position_41 = result_43->end;
result_41 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_41->flags = 0;
result_41->type = SEQUENCE_T;
result_41->start = start_41;
result_41->end = result_43->end;
result_41->num_children = 2;
result_41->children[0] = result_42;
result_41->children[1] = result_43;
result_41->id = 41;
exit_41:
if (result_41 != NULL) {
    append_arraylist(&list_40, result_41);
    start_41 = result_41->end;
    ++num_children_40;
}
} while (result_41 != NULL);
result_40 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_40);
result_40->flags = 0;
result_40->type = STAR_T;
result_40->start = start_40;
result_40->num_children = num_children_40;
if (num_children_40) {
for (uint32_t i = 0; i < num_children_40; ++i) {
result_40->children[i] = list_40->arr[i];
}
result_40->end = ((rnode_t*)list_40->arr[num_children_40 - 1])->end;
} else {
result_40->end = start_40;
}
result_40->id = 40;
free(list_40);
if (result_40 == NULL) {
free_tree(result_39, IS_CACHED);
goto exit_38;
}
current_position_38 = result_40->end;
result_38 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_38->flags = SEMANTIC_ACTION | 0;
result_38->type = SEQUENCE_T;
result_38->start = start_38;
result_38->end = result_40->end;
result_38->num_children = 2;
result_38->children[0] = result_39;
result_38->children[1] = result_40;
result_38->id = 38;
exit_38:
return result_38;
}
rnode_t* eval_operator(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_44 = pos;
rnode_t* result_44 = NULL;
uint32_t start_45 = start_44;
rnode_t* result_45 = NULL;
uint32_t current_position_45 = start_45;
uint32_t start_46 = current_position_45;
rnode_t* result_46 = NULL;
rnode_t* result_46_nt = call_eval(EVAL_prefix, state, text, text_length, start_46);
if (result_46_nt) {
result_46 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_46->flags = ALIAS | 0;
result_46->type = NONTERMINAL_T;
result_46->start = start_46;
result_46->end = result_46_nt->end;
result_46->num_children = 1;
result_46->children[0] = result_46_nt;
result_46->id = 46;
}
if (result_46 == NULL) {
goto exit_45;
}
current_position_45 = result_46->end;
uint32_t start_47 = current_position_45;
rnode_t* result_47 = NULL;
uint32_t start_48 = start_47;
rnode_t* result_48 = NULL;
uint32_t current_position_48 = start_48;
uint32_t start_49 = current_position_48;
rnode_t* result_49 = NULL;
rnode_t* result_49_nt = call_eval(EVAL_ws, state, text, text_length, start_49);
if (result_49_nt) {
result_49 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_49->flags = 0;
result_49->type = NONTERMINAL_T;
result_49->start = start_49;
result_49->end = result_49_nt->end;
result_49->num_children = 1;
result_49->children[0] = result_49_nt;
result_49->id = 49;
}
if (result_49 == NULL) {
goto exit_48;
}
current_position_48 = result_49->end;
uint32_t start_50 = current_position_48;
rnode_t* result_50 = NULL;
rnode_t* result_50_nt = call_eval(EVAL_code, state, text, text_length, start_50);
if (result_50_nt) {
result_50 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_50->flags = DO_CAPTURE | 0;
result_50->type = NONTERMINAL_T;
result_50->start = start_50;
result_50->end = result_50_nt->end;
result_50->num_children = 1;
result_50->children[0] = result_50_nt;
result_50->id = 50;
}
if (result_50 == NULL) {
free_tree(result_49, IS_CACHED);
goto exit_48;
}
current_position_48 = result_50->end;
result_48 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_48->flags = 0;
result_48->type = SEQUENCE_T;
result_48->start = start_48;
result_48->end = result_50->end;
result_48->num_children = 2;
result_48->children[0] = result_49;
result_48->children[1] = result_50;
result_48->id = 48;
exit_48:
if (result_48) {
result_47 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_47->flags = 0;
result_47->end = result_48->end;
result_47->num_children = 1;
result_47->children[0] = result_48;
} else {
result_47 = malloc(sizeof(rnode_t));
result_47->end = start_47;
result_47->num_children = 0;
}
result_47->type = OPTIONAL_T;
result_47->start = start_47;
result_47->id = 47;
if (result_47 == NULL) {
free_tree(result_46, IS_CACHED);
goto exit_45;
}
current_position_45 = result_47->end;
result_45 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_45->flags = SEMANTIC_ACTION | 0;
result_45->type = SEQUENCE_T;
result_45->start = start_45;
result_45->end = result_47->end;
result_45->num_children = 2;
result_45->children[0] = result_46;
result_45->children[1] = result_47;
result_45->id = 45;
exit_45:
if (result_45 != NULL) {
result_44 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_44->flags = 0;
result_44->type = ALTERNATIVE_T;
result_44->start = start_44;
result_44->end = result_45->end;
result_44->num_children = 1;
result_44->children[0] = result_45;
result_44->id = 44;
goto exit_44;
}
uint32_t start_51 = start_44;
rnode_t* result_51 = NULL;
uint32_t current_position_51 = start_51;
uint32_t start_52 = current_position_51;
rnode_t* result_52 = NULL;
rnode_t* result_52_nt = call_eval(EVAL_postfix, state, text, text_length, start_52);
if (result_52_nt) {
result_52 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_52->flags = ALIAS | 0;
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
uint32_t start_54 = start_53;
rnode_t* result_54 = NULL;
uint32_t current_position_54 = start_54;
uint32_t start_55 = current_position_54;
rnode_t* result_55 = NULL;
rnode_t* result_55_nt = call_eval(EVAL_ws, state, text, text_length, start_55);
if (result_55_nt) {
result_55 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_55->flags = 0;
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
rnode_t* result_56_nt = call_eval(EVAL_code, state, text, text_length, start_56);
if (result_56_nt) {
result_56 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_56->flags = DO_CAPTURE | 0;
result_56->type = NONTERMINAL_T;
result_56->start = start_56;
result_56->end = result_56_nt->end;
result_56->num_children = 1;
result_56->children[0] = result_56_nt;
result_56->id = 56;
}
if (result_56 == NULL) {
free_tree(result_55, IS_CACHED);
goto exit_54;
}
current_position_54 = result_56->end;
result_54 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_54->flags = 0;
result_54->type = SEQUENCE_T;
result_54->start = start_54;
result_54->end = result_56->end;
result_54->num_children = 2;
result_54->children[0] = result_55;
result_54->children[1] = result_56;
result_54->id = 54;
exit_54:
if (result_54) {
result_53 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_53->flags = 0;
result_53->end = result_54->end;
result_53->num_children = 1;
result_53->children[0] = result_54;
} else {
result_53 = malloc(sizeof(rnode_t));
result_53->end = start_53;
result_53->num_children = 0;
}
result_53->type = OPTIONAL_T;
result_53->start = start_53;
result_53->id = 53;
if (result_53 == NULL) {
free_tree(result_52, IS_CACHED);
goto exit_51;
}
current_position_51 = result_53->end;
result_51 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_51->flags = SEMANTIC_ACTION | 0;
result_51->type = SEQUENCE_T;
result_51->start = start_51;
result_51->end = result_53->end;
result_51->num_children = 2;
result_51->children[0] = result_52;
result_51->children[1] = result_53;
result_51->id = 51;
exit_51:
if (result_51 != NULL) {
result_44 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_44->flags = 0;
result_44->type = ALTERNATIVE_T;
result_44->start = start_44;
result_44->end = result_51->end;
result_44->num_children = 1;
result_44->children[0] = result_51;
result_44->id = 44;
goto exit_44;
}
uint32_t start_57 = start_44;
rnode_t* result_57 = NULL;
uint32_t current_position_57 = start_57;
uint32_t start_58 = current_position_57;
rnode_t* result_58 = NULL;
rnode_t* result_58_nt = call_eval(EVAL_group, state, text, text_length, start_58);
if (result_58_nt) {
result_58 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_58->flags = ALIAS | 0;
result_58->type = NONTERMINAL_T;
result_58->start = start_58;
result_58->end = result_58_nt->end;
result_58->num_children = 1;
result_58->children[0] = result_58_nt;
result_58->id = 58;
}
if (result_58 == NULL) {
goto exit_57;
}
current_position_57 = result_58->end;
uint32_t start_59 = current_position_57;
rnode_t* result_59 = NULL;
uint32_t start_60 = start_59;
rnode_t* result_60 = NULL;
uint32_t current_position_60 = start_60;
uint32_t start_61 = current_position_60;
rnode_t* result_61 = NULL;
rnode_t* result_61_nt = call_eval(EVAL_ws, state, text, text_length, start_61);
if (result_61_nt) {
result_61 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_61->flags = 0;
result_61->type = NONTERMINAL_T;
result_61->start = start_61;
result_61->end = result_61_nt->end;
result_61->num_children = 1;
result_61->children[0] = result_61_nt;
result_61->id = 61;
}
if (result_61 == NULL) {
goto exit_60;
}
current_position_60 = result_61->end;
uint32_t start_62 = current_position_60;
rnode_t* result_62 = NULL;
rnode_t* result_62_nt = call_eval(EVAL_code, state, text, text_length, start_62);
if (result_62_nt) {
result_62 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_62->flags = DO_CAPTURE | 0;
result_62->type = NONTERMINAL_T;
result_62->start = start_62;
result_62->end = result_62_nt->end;
result_62->num_children = 1;
result_62->children[0] = result_62_nt;
result_62->id = 62;
}
if (result_62 == NULL) {
free_tree(result_61, IS_CACHED);
goto exit_60;
}
current_position_60 = result_62->end;
result_60 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_60->flags = 0;
result_60->type = SEQUENCE_T;
result_60->start = start_60;
result_60->end = result_62->end;
result_60->num_children = 2;
result_60->children[0] = result_61;
result_60->children[1] = result_62;
result_60->id = 60;
exit_60:
if (result_60) {
result_59 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_59->flags = 0;
result_59->end = result_60->end;
result_59->num_children = 1;
result_59->children[0] = result_60;
} else {
result_59 = malloc(sizeof(rnode_t));
result_59->end = start_59;
result_59->num_children = 0;
}
result_59->type = OPTIONAL_T;
result_59->start = start_59;
result_59->id = 59;
if (result_59 == NULL) {
free_tree(result_58, IS_CACHED);
goto exit_57;
}
current_position_57 = result_59->end;
result_57 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_57->flags = SEMANTIC_ACTION | 0;
result_57->type = SEQUENCE_T;
result_57->start = start_57;
result_57->end = result_59->end;
result_57->num_children = 2;
result_57->children[0] = result_58;
result_57->children[1] = result_59;
result_57->id = 57;
exit_57:
if (result_57 != NULL) {
result_44 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_44->flags = 0;
result_44->type = ALTERNATIVE_T;
result_44->start = start_44;
result_44->end = result_57->end;
result_44->num_children = 1;
result_44->children[0] = result_57;
result_44->id = 44;
goto exit_44;
}
exit_44:
return result_44;
}
rnode_t* eval_prefix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_63 = pos;
rnode_t* result_63 = NULL;
uint32_t start_64 = start_63;
rnode_t* result_64 = NULL;
uint32_t current_position_64 = start_64;
uint32_t start_65 = current_position_64;
rnode_t* result_65 = NULL;
rnode_t* result_65_nt = call_eval(EVAL_and, state, text, text_length, start_65);
if (result_65_nt) {
result_65 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_65->flags = 0;
result_65->type = NONTERMINAL_T;
result_65->start = start_65;
result_65->end = result_65_nt->end;
result_65->num_children = 1;
result_65->children[0] = result_65_nt;
result_65->id = 65;
}
if (result_65 == NULL) {
goto exit_64;
}
current_position_64 = result_65->end;
uint32_t start_66 = current_position_64;
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
free_tree(result_65, IS_CACHED);
goto exit_64;
}
current_position_64 = result_66->end;
uint32_t start_67 = current_position_64;
rnode_t* result_67 = NULL;
rnode_t* result_67_nt = call_eval(EVAL_group, state, text, text_length, start_67);
if (result_67_nt) {
result_67 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_67->flags = ALIAS | 0;
result_67->type = NONTERMINAL_T;
result_67->start = start_67;
result_67->end = result_67_nt->end;
result_67->num_children = 1;
result_67->children[0] = result_67_nt;
result_67->id = 67;
}
if (result_67 == NULL) {
free_tree(result_65, IS_CACHED);
free_tree(result_66, IS_CACHED);
goto exit_64;
}
current_position_64 = result_67->end;
result_64 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_64->flags = SEMANTIC_ACTION | 0;
result_64->type = SEQUENCE_T;
result_64->start = start_64;
result_64->end = result_67->end;
result_64->num_children = 3;
result_64->children[0] = result_65;
result_64->children[1] = result_66;
result_64->children[2] = result_67;
result_64->id = 64;
exit_64:
if (result_64 != NULL) {
result_63 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_63->flags = 0;
result_63->type = ALTERNATIVE_T;
result_63->start = start_63;
result_63->end = result_64->end;
result_63->num_children = 1;
result_63->children[0] = result_64;
result_63->id = 63;
goto exit_63;
}
uint32_t start_68 = start_63;
rnode_t* result_68 = NULL;
uint32_t current_position_68 = start_68;
uint32_t start_69 = current_position_68;
rnode_t* result_69 = NULL;
rnode_t* result_69_nt = call_eval(EVAL_not, state, text, text_length, start_69);
if (result_69_nt) {
result_69 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_69->flags = 0;
result_69->type = NONTERMINAL_T;
result_69->start = start_69;
result_69->end = result_69_nt->end;
result_69->num_children = 1;
result_69->children[0] = result_69_nt;
result_69->id = 69;
}
if (result_69 == NULL) {
goto exit_68;
}
current_position_68 = result_69->end;
uint32_t start_70 = current_position_68;
rnode_t* result_70 = NULL;
rnode_t* result_70_nt = call_eval(EVAL_ws, state, text, text_length, start_70);
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
free_tree(result_69, IS_CACHED);
goto exit_68;
}
current_position_68 = result_70->end;
uint32_t start_71 = current_position_68;
rnode_t* result_71 = NULL;
rnode_t* result_71_nt = call_eval(EVAL_group, state, text, text_length, start_71);
if (result_71_nt) {
result_71 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_71->flags = ALIAS | 0;
result_71->type = NONTERMINAL_T;
result_71->start = start_71;
result_71->end = result_71_nt->end;
result_71->num_children = 1;
result_71->children[0] = result_71_nt;
result_71->id = 71;
}
if (result_71 == NULL) {
free_tree(result_69, IS_CACHED);
free_tree(result_70, IS_CACHED);
goto exit_68;
}
current_position_68 = result_71->end;
result_68 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_68->flags = SEMANTIC_ACTION | 0;
result_68->type = SEQUENCE_T;
result_68->start = start_68;
result_68->end = result_71->end;
result_68->num_children = 3;
result_68->children[0] = result_69;
result_68->children[1] = result_70;
result_68->children[2] = result_71;
result_68->id = 68;
exit_68:
if (result_68 != NULL) {
result_63 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_63->flags = 0;
result_63->type = ALTERNATIVE_T;
result_63->start = start_63;
result_63->end = result_68->end;
result_63->num_children = 1;
result_63->children[0] = result_68;
result_63->id = 63;
goto exit_63;
}
exit_63:
return result_63;
}
rnode_t* eval_and(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_72 = pos;
rnode_t* result_72 = NULL;
uint8_t bytesbuf_72[] = {38, };
uint8_t c_72;
for (uint32_t i_72 = 0; i_72 < 1; ++i_72) {
c_72 = bytesbuf_72[i_72];
if (i_72 + start_72 < text_length
    && c_72 == text[i_72 + start_72]) {
if (i_72 == 1 - 1) {
result_72 = malloc(sizeof(rnode_t));
result_72->flags = 0;
result_72->type = LITERAL_T;
result_72->start = start_72;
result_72->end = start_72 + 1;
result_72->num_children = 0;
result_72->id = 72;
}
} else {
break;
}
}
return result_72;
}
rnode_t* eval_not(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_73 = pos;
rnode_t* result_73 = NULL;
uint8_t bytesbuf_73[] = {33, };
uint8_t c_73;
for (uint32_t i_73 = 0; i_73 < 1; ++i_73) {
c_73 = bytesbuf_73[i_73];
if (i_73 + start_73 < text_length
    && c_73 == text[i_73 + start_73]) {
if (i_73 == 1 - 1) {
result_73 = malloc(sizeof(rnode_t));
result_73->flags = 0;
result_73->type = LITERAL_T;
result_73->start = start_73;
result_73->end = start_73 + 1;
result_73->num_children = 0;
result_73->id = 73;
}
} else {
break;
}
}
return result_73;
}
rnode_t* eval_postfix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_74 = pos;
rnode_t* result_74 = NULL;
uint32_t start_75 = start_74;
rnode_t* result_75 = NULL;
uint32_t current_position_75 = start_75;
uint32_t start_76 = current_position_75;
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
goto exit_75;
}
current_position_75 = result_76->end;
uint32_t start_77 = current_position_75;
rnode_t* result_77 = NULL;
rnode_t* result_77_nt = call_eval(EVAL_ws, state, text, text_length, start_77);
if (result_77_nt) {
result_77 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_77->flags = 0;
result_77->type = NONTERMINAL_T;
result_77->start = start_77;
result_77->end = result_77_nt->end;
result_77->num_children = 1;
result_77->children[0] = result_77_nt;
result_77->id = 77;
}
if (result_77 == NULL) {
free_tree(result_76, IS_CACHED);
goto exit_75;
}
current_position_75 = result_77->end;
uint32_t start_78 = current_position_75;
rnode_t* result_78 = NULL;
rnode_t* result_78_nt = call_eval(EVAL_star, state, text, text_length, start_78);
if (result_78_nt) {
result_78 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_78->flags = 0;
result_78->type = NONTERMINAL_T;
result_78->start = start_78;
result_78->end = result_78_nt->end;
result_78->num_children = 1;
result_78->children[0] = result_78_nt;
result_78->id = 78;
}
if (result_78 == NULL) {
free_tree(result_76, IS_CACHED);
free_tree(result_77, IS_CACHED);
goto exit_75;
}
current_position_75 = result_78->end;
result_75 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_75->flags = SEMANTIC_ACTION | 0;
result_75->type = SEQUENCE_T;
result_75->start = start_75;
result_75->end = result_78->end;
result_75->num_children = 3;
result_75->children[0] = result_76;
result_75->children[1] = result_77;
result_75->children[2] = result_78;
result_75->id = 75;
exit_75:
if (result_75 != NULL) {
result_74 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_74->flags = 0;
result_74->type = ALTERNATIVE_T;
result_74->start = start_74;
result_74->end = result_75->end;
result_74->num_children = 1;
result_74->children[0] = result_75;
result_74->id = 74;
goto exit_74;
}
uint32_t start_79 = start_74;
rnode_t* result_79 = NULL;
uint32_t current_position_79 = start_79;
uint32_t start_80 = current_position_79;
rnode_t* result_80 = NULL;
rnode_t* result_80_nt = call_eval(EVAL_group, state, text, text_length, start_80);
if (result_80_nt) {
result_80 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_80->flags = ALIAS | 0;
result_80->type = NONTERMINAL_T;
result_80->start = start_80;
result_80->end = result_80_nt->end;
result_80->num_children = 1;
result_80->children[0] = result_80_nt;
result_80->id = 80;
}
if (result_80 == NULL) {
goto exit_79;
}
current_position_79 = result_80->end;
uint32_t start_81 = current_position_79;
rnode_t* result_81 = NULL;
rnode_t* result_81_nt = call_eval(EVAL_ws, state, text, text_length, start_81);
if (result_81_nt) {
result_81 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_81->flags = 0;
result_81->type = NONTERMINAL_T;
result_81->start = start_81;
result_81->end = result_81_nt->end;
result_81->num_children = 1;
result_81->children[0] = result_81_nt;
result_81->id = 81;
}
if (result_81 == NULL) {
free_tree(result_80, IS_CACHED);
goto exit_79;
}
current_position_79 = result_81->end;
uint32_t start_82 = current_position_79;
rnode_t* result_82 = NULL;
rnode_t* result_82_nt = call_eval(EVAL_plus, state, text, text_length, start_82);
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
free_tree(result_80, IS_CACHED);
free_tree(result_81, IS_CACHED);
goto exit_79;
}
current_position_79 = result_82->end;
result_79 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_79->flags = SEMANTIC_ACTION | 0;
result_79->type = SEQUENCE_T;
result_79->start = start_79;
result_79->end = result_82->end;
result_79->num_children = 3;
result_79->children[0] = result_80;
result_79->children[1] = result_81;
result_79->children[2] = result_82;
result_79->id = 79;
exit_79:
if (result_79 != NULL) {
result_74 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_74->flags = 0;
result_74->type = ALTERNATIVE_T;
result_74->start = start_74;
result_74->end = result_79->end;
result_74->num_children = 1;
result_74->children[0] = result_79;
result_74->id = 74;
goto exit_74;
}
uint32_t start_83 = start_74;
rnode_t* result_83 = NULL;
uint32_t current_position_83 = start_83;
uint32_t start_84 = current_position_83;
rnode_t* result_84 = NULL;
rnode_t* result_84_nt = call_eval(EVAL_group, state, text, text_length, start_84);
if (result_84_nt) {
result_84 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_84->flags = ALIAS | 0;
result_84->type = NONTERMINAL_T;
result_84->start = start_84;
result_84->end = result_84_nt->end;
result_84->num_children = 1;
result_84->children[0] = result_84_nt;
result_84->id = 84;
}
if (result_84 == NULL) {
goto exit_83;
}
current_position_83 = result_84->end;
uint32_t start_85 = current_position_83;
rnode_t* result_85 = NULL;
rnode_t* result_85_nt = call_eval(EVAL_ws, state, text, text_length, start_85);
if (result_85_nt) {
result_85 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_85->flags = 0;
result_85->type = NONTERMINAL_T;
result_85->start = start_85;
result_85->end = result_85_nt->end;
result_85->num_children = 1;
result_85->children[0] = result_85_nt;
result_85->id = 85;
}
if (result_85 == NULL) {
free_tree(result_84, IS_CACHED);
goto exit_83;
}
current_position_83 = result_85->end;
uint32_t start_86 = current_position_83;
rnode_t* result_86 = NULL;
rnode_t* result_86_nt = call_eval(EVAL_option, state, text, text_length, start_86);
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
free_tree(result_84, IS_CACHED);
free_tree(result_85, IS_CACHED);
goto exit_83;
}
current_position_83 = result_86->end;
result_83 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_83->flags = SEMANTIC_ACTION | 0;
result_83->type = SEQUENCE_T;
result_83->start = start_83;
result_83->end = result_86->end;
result_83->num_children = 3;
result_83->children[0] = result_84;
result_83->children[1] = result_85;
result_83->children[2] = result_86;
result_83->id = 83;
exit_83:
if (result_83 != NULL) {
result_74 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_74->flags = 0;
result_74->type = ALTERNATIVE_T;
result_74->start = start_74;
result_74->end = result_83->end;
result_74->num_children = 1;
result_74->children[0] = result_83;
result_74->id = 74;
goto exit_74;
}
exit_74:
return result_74;
}
rnode_t* eval_star(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_87 = pos;
rnode_t* result_87 = NULL;
uint8_t bytesbuf_87[] = {42, };
uint8_t c_87;
for (uint32_t i_87 = 0; i_87 < 1; ++i_87) {
c_87 = bytesbuf_87[i_87];
if (i_87 + start_87 < text_length
    && c_87 == text[i_87 + start_87]) {
if (i_87 == 1 - 1) {
result_87 = malloc(sizeof(rnode_t));
result_87->flags = 0;
result_87->type = LITERAL_T;
result_87->start = start_87;
result_87->end = start_87 + 1;
result_87->num_children = 0;
result_87->id = 87;
}
} else {
break;
}
}
return result_87;
}
rnode_t* eval_plus(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_88 = pos;
rnode_t* result_88 = NULL;
uint8_t bytesbuf_88[] = {43, };
uint8_t c_88;
for (uint32_t i_88 = 0; i_88 < 1; ++i_88) {
c_88 = bytesbuf_88[i_88];
if (i_88 + start_88 < text_length
    && c_88 == text[i_88 + start_88]) {
if (i_88 == 1 - 1) {
result_88 = malloc(sizeof(rnode_t));
result_88->flags = 0;
result_88->type = LITERAL_T;
result_88->start = start_88;
result_88->end = start_88 + 1;
result_88->num_children = 0;
result_88->id = 88;
}
} else {
break;
}
}
return result_88;
}
rnode_t* eval_option(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_89 = pos;
rnode_t* result_89 = NULL;
uint8_t bytesbuf_89[] = {63, };
uint8_t c_89;
for (uint32_t i_89 = 0; i_89 < 1; ++i_89) {
c_89 = bytesbuf_89[i_89];
if (i_89 + start_89 < text_length
    && c_89 == text[i_89 + start_89]) {
if (i_89 == 1 - 1) {
result_89 = malloc(sizeof(rnode_t));
result_89->flags = 0;
result_89->type = LITERAL_T;
result_89->start = start_89;
result_89->end = start_89 + 1;
result_89->num_children = 0;
result_89->id = 89;
}
} else {
break;
}
}
return result_89;
}
rnode_t* eval_group(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_90 = pos;
rnode_t* result_90 = NULL;
uint32_t start_91 = start_90;
rnode_t* result_91 = NULL;
uint32_t current_position_91 = start_91;
uint32_t start_92 = current_position_91;
rnode_t* result_92 = NULL;
uint8_t bytesbuf_92[] = {40, };
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
if (result_92 == NULL) {
goto exit_91;
}
current_position_91 = result_92->end;
uint32_t start_93 = current_position_91;
rnode_t* result_93 = NULL;
rnode_t* result_93_nt = call_eval(EVAL_ws, state, text, text_length, start_93);
if (result_93_nt) {
result_93 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_93->flags = 0;
result_93->type = NONTERMINAL_T;
result_93->start = start_93;
result_93->end = result_93_nt->end;
result_93->num_children = 1;
result_93->children[0] = result_93_nt;
result_93->id = 93;
}
if (result_93 == NULL) {
free_tree(result_92, IS_CACHED);
goto exit_91;
}
current_position_91 = result_93->end;
uint32_t start_94 = current_position_91;
rnode_t* result_94 = NULL;
rnode_t* result_94_nt = call_eval(EVAL_body, state, text, text_length, start_94);
if (result_94_nt) {
result_94 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_94->flags = ALIAS | 0;
result_94->type = NONTERMINAL_T;
result_94->start = start_94;
result_94->end = result_94_nt->end;
result_94->num_children = 1;
result_94->children[0] = result_94_nt;
result_94->id = 94;
}
if (result_94 == NULL) {
free_tree(result_92, IS_CACHED);
free_tree(result_93, IS_CACHED);
goto exit_91;
}
current_position_91 = result_94->end;
uint32_t start_95 = current_position_91;
rnode_t* result_95 = NULL;
rnode_t* result_95_nt = call_eval(EVAL_ws, state, text, text_length, start_95);
if (result_95_nt) {
result_95 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_95->flags = 0;
result_95->type = NONTERMINAL_T;
result_95->start = start_95;
result_95->end = result_95_nt->end;
result_95->num_children = 1;
result_95->children[0] = result_95_nt;
result_95->id = 95;
}
if (result_95 == NULL) {
free_tree(result_92, IS_CACHED);
free_tree(result_93, IS_CACHED);
free_tree(result_94, IS_CACHED);
goto exit_91;
}
current_position_91 = result_95->end;
uint32_t start_96 = current_position_91;
rnode_t* result_96 = NULL;
uint8_t bytesbuf_96[] = {41, };
uint8_t c_96;
for (uint32_t i_96 = 0; i_96 < 1; ++i_96) {
c_96 = bytesbuf_96[i_96];
if (i_96 + start_96 < text_length
    && c_96 == text[i_96 + start_96]) {
if (i_96 == 1 - 1) {
result_96 = malloc(sizeof(rnode_t));
result_96->flags = 0;
result_96->type = LITERAL_T;
result_96->start = start_96;
result_96->end = start_96 + 1;
result_96->num_children = 0;
result_96->id = 96;
}
} else {
break;
}
}
if (result_96 == NULL) {
free_tree(result_92, IS_CACHED);
free_tree(result_93, IS_CACHED);
free_tree(result_94, IS_CACHED);
free_tree(result_95, IS_CACHED);
goto exit_91;
}
current_position_91 = result_96->end;
result_91 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 5);
result_91->flags = SEMANTIC_ACTION | 0;
result_91->type = SEQUENCE_T;
result_91->start = start_91;
result_91->end = result_96->end;
result_91->num_children = 5;
result_91->children[0] = result_92;
result_91->children[1] = result_93;
result_91->children[2] = result_94;
result_91->children[3] = result_95;
result_91->children[4] = result_96;
result_91->id = 91;
exit_91:
if (result_91 != NULL) {
result_90 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_90->flags = 0;
result_90->type = ALTERNATIVE_T;
result_90->start = start_90;
result_90->end = result_91->end;
result_90->num_children = 1;
result_90->children[0] = result_91;
result_90->id = 90;
goto exit_90;
}
uint32_t start_97 = start_90;
rnode_t* result_97 = NULL;
uint32_t current_position_97 = start_97;
uint32_t start_98 = current_position_97;
rnode_t* result_98 = NULL;
uint8_t bytesbuf_98[] = {60, };
uint8_t c_98;
for (uint32_t i_98 = 0; i_98 < 1; ++i_98) {
c_98 = bytesbuf_98[i_98];
if (i_98 + start_98 < text_length
    && c_98 == text[i_98 + start_98]) {
if (i_98 == 1 - 1) {
result_98 = malloc(sizeof(rnode_t));
result_98->flags = 0;
result_98->type = LITERAL_T;
result_98->start = start_98;
result_98->end = start_98 + 1;
result_98->num_children = 0;
result_98->id = 98;
}
} else {
break;
}
}
if (result_98 == NULL) {
goto exit_97;
}
current_position_97 = result_98->end;
uint32_t start_99 = current_position_97;
rnode_t* result_99 = NULL;
rnode_t* result_99_nt = call_eval(EVAL_ws, state, text, text_length, start_99);
if (result_99_nt) {
result_99 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_99->flags = 0;
result_99->type = NONTERMINAL_T;
result_99->start = start_99;
result_99->end = result_99_nt->end;
result_99->num_children = 1;
result_99->children[0] = result_99_nt;
result_99->id = 99;
}
if (result_99 == NULL) {
free_tree(result_98, IS_CACHED);
goto exit_97;
}
current_position_97 = result_99->end;
uint32_t start_100 = current_position_97;
rnode_t* result_100 = NULL;
rnode_t* result_100_nt = call_eval(EVAL_body, state, text, text_length, start_100);
if (result_100_nt) {
result_100 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_100->flags = ALIAS | 0;
result_100->type = NONTERMINAL_T;
result_100->start = start_100;
result_100->end = result_100_nt->end;
result_100->num_children = 1;
result_100->children[0] = result_100_nt;
result_100->id = 100;
}
if (result_100 == NULL) {
free_tree(result_98, IS_CACHED);
free_tree(result_99, IS_CACHED);
goto exit_97;
}
current_position_97 = result_100->end;
uint32_t start_101 = current_position_97;
rnode_t* result_101 = NULL;
rnode_t* result_101_nt = call_eval(EVAL_ws, state, text, text_length, start_101);
if (result_101_nt) {
result_101 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_101->flags = 0;
result_101->type = NONTERMINAL_T;
result_101->start = start_101;
result_101->end = result_101_nt->end;
result_101->num_children = 1;
result_101->children[0] = result_101_nt;
result_101->id = 101;
}
if (result_101 == NULL) {
free_tree(result_98, IS_CACHED);
free_tree(result_99, IS_CACHED);
free_tree(result_100, IS_CACHED);
goto exit_97;
}
current_position_97 = result_101->end;
uint32_t start_102 = current_position_97;
rnode_t* result_102 = NULL;
uint8_t bytesbuf_102[] = {62, };
uint8_t c_102;
for (uint32_t i_102 = 0; i_102 < 1; ++i_102) {
c_102 = bytesbuf_102[i_102];
if (i_102 + start_102 < text_length
    && c_102 == text[i_102 + start_102]) {
if (i_102 == 1 - 1) {
result_102 = malloc(sizeof(rnode_t));
result_102->flags = 0;
result_102->type = LITERAL_T;
result_102->start = start_102;
result_102->end = start_102 + 1;
result_102->num_children = 0;
result_102->id = 102;
}
} else {
break;
}
}
if (result_102 == NULL) {
free_tree(result_98, IS_CACHED);
free_tree(result_99, IS_CACHED);
free_tree(result_100, IS_CACHED);
free_tree(result_101, IS_CACHED);
goto exit_97;
}
current_position_97 = result_102->end;
result_97 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 5);
result_97->flags = SEMANTIC_ACTION | 0;
result_97->type = SEQUENCE_T;
result_97->start = start_97;
result_97->end = result_102->end;
result_97->num_children = 5;
result_97->children[0] = result_98;
result_97->children[1] = result_99;
result_97->children[2] = result_100;
result_97->children[3] = result_101;
result_97->children[4] = result_102;
result_97->id = 97;
exit_97:
if (result_97 != NULL) {
result_90 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_90->flags = 0;
result_90->type = ALTERNATIVE_T;
result_90->start = start_90;
result_90->end = result_97->end;
result_90->num_children = 1;
result_90->children[0] = result_97;
result_90->id = 90;
goto exit_90;
}
uint32_t start_103 = start_90;
rnode_t* result_103 = NULL;
rnode_t* result_103_nt = call_eval(EVAL_final, state, text, text_length, start_103);
if (result_103_nt) {
result_103 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_103->flags = SEMANTIC_ACTION | ALIAS | 0;
result_103->type = NONTERMINAL_T;
result_103->start = start_103;
result_103->end = result_103_nt->end;
result_103->num_children = 1;
result_103->children[0] = result_103_nt;
result_103->id = 103;
}
if (result_103 != NULL) {
result_90 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_90->flags = 0;
result_90->type = ALTERNATIVE_T;
result_90->start = start_90;
result_90->end = result_103->end;
result_90->num_children = 1;
result_90->children[0] = result_103;
result_90->id = 90;
goto exit_90;
}
exit_90:
return result_90;
}
rnode_t* eval_final(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_104 = pos;
rnode_t* result_104 = NULL;
uint32_t start_105 = start_104;
rnode_t* result_105 = NULL;
rnode_t* result_105_nt = call_eval(EVAL_nonterminal, state, text, text_length, start_105);
if (result_105_nt) {
result_105 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_105->flags = SEMANTIC_ACTION | ALIAS | 0;
result_105->type = NONTERMINAL_T;
result_105->start = start_105;
result_105->end = result_105_nt->end;
result_105->num_children = 1;
result_105->children[0] = result_105_nt;
result_105->id = 105;
}
if (result_105 != NULL) {
result_104 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_104->flags = 0;
result_104->type = ALTERNATIVE_T;
result_104->start = start_104;
result_104->end = result_105->end;
result_104->num_children = 1;
result_104->children[0] = result_105;
result_104->id = 104;
goto exit_104;
}
uint32_t start_106 = start_104;
rnode_t* result_106 = NULL;
rnode_t* result_106_nt = call_eval(EVAL_literal, state, text, text_length, start_106);
if (result_106_nt) {
result_106 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_106->flags = SEMANTIC_ACTION | ALIAS | 0;
result_106->type = NONTERMINAL_T;
result_106->start = start_106;
result_106->end = result_106_nt->end;
result_106->num_children = 1;
result_106->children[0] = result_106_nt;
result_106->id = 106;
}
if (result_106 != NULL) {
result_104 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_104->flags = 0;
result_104->type = ALTERNATIVE_T;
result_104->start = start_104;
result_104->end = result_106->end;
result_104->num_children = 1;
result_104->children[0] = result_106;
result_104->id = 104;
goto exit_104;
}
uint32_t start_107 = start_104;
rnode_t* result_107 = NULL;
rnode_t* result_107_nt = call_eval(EVAL_cclass, state, text, text_length, start_107);
if (result_107_nt) {
result_107 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_107->flags = SEMANTIC_ACTION | ALIAS | 0;
result_107->type = NONTERMINAL_T;
result_107->start = start_107;
result_107->end = result_107_nt->end;
result_107->num_children = 1;
result_107->children[0] = result_107_nt;
result_107->id = 107;
}
if (result_107 != NULL) {
result_104 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_104->flags = 0;
result_104->type = ALTERNATIVE_T;
result_104->start = start_104;
result_104->end = result_107->end;
result_104->num_children = 1;
result_104->children[0] = result_107;
result_104->id = 104;
goto exit_104;
}
uint32_t start_108 = start_104;
rnode_t* result_108 = NULL;
rnode_t* result_108_nt = call_eval(EVAL_dot, state, text, text_length, start_108);
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
result_104 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_104->flags = 0;
result_104->type = ALTERNATIVE_T;
result_104->start = start_104;
result_104->end = result_108->end;
result_104->num_children = 1;
result_104->children[0] = result_108;
result_104->id = 104;
goto exit_104;
}
exit_104:
return result_104;
}
rnode_t* eval_nonterminal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_109 = pos;
rnode_t* result_109 = NULL;
uint32_t start_110 = start_109;
rnode_t* result_110 = NULL;
uint32_t current_position_110 = start_110;
uint32_t start_111 = current_position_110;
rnode_t* result_111 = NULL;
rnode_t* result_111_nt = call_eval(EVAL_name, state, text, text_length, start_111);
if (result_111_nt) {
result_111 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_111->flags = DO_CAPTURE | 0;
result_111->type = NONTERMINAL_T;
result_111->start = start_111;
result_111->end = result_111_nt->end;
result_111->num_children = 1;
result_111->children[0] = result_111_nt;
result_111->id = 111;
}
if (result_111 == NULL) {
goto exit_110;
}
current_position_110 = result_111->end;
uint32_t start_112 = current_position_110;
rnode_t* result_112 = NULL;
rnode_t* result_112_nt = call_eval(EVAL_ws, state, text, text_length, start_112);
if (result_112_nt) {
result_112 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_112->flags = 0;
result_112->type = NONTERMINAL_T;
result_112->start = start_112;
result_112->end = result_112_nt->end;
result_112->num_children = 1;
result_112->children[0] = result_112_nt;
result_112->id = 112;
}
if (result_112 == NULL) {
free_tree(result_111, IS_CACHED);
goto exit_110;
}
current_position_110 = result_112->end;
uint32_t start_113 = current_position_110;
rnode_t* result_113 = NULL;
uint8_t bytesbuf_113[] = {58, };
uint8_t c_113;
for (uint32_t i_113 = 0; i_113 < 1; ++i_113) {
c_113 = bytesbuf_113[i_113];
if (i_113 + start_113 < text_length
    && c_113 == text[i_113 + start_113]) {
if (i_113 == 1 - 1) {
result_113 = malloc(sizeof(rnode_t));
result_113->flags = 0;
result_113->type = LITERAL_T;
result_113->start = start_113;
result_113->end = start_113 + 1;
result_113->num_children = 0;
result_113->id = 113;
}
} else {
break;
}
}
if (result_113 == NULL) {
free_tree(result_111, IS_CACHED);
free_tree(result_112, IS_CACHED);
goto exit_110;
}
current_position_110 = result_113->end;
uint32_t start_114 = current_position_110;
rnode_t* result_114 = NULL;
rnode_t* result_114_nt = call_eval(EVAL_ws, state, text, text_length, start_114);
if (result_114_nt) {
result_114 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_114->flags = 0;
result_114->type = NONTERMINAL_T;
result_114->start = start_114;
result_114->end = result_114_nt->end;
result_114->num_children = 1;
result_114->children[0] = result_114_nt;
result_114->id = 114;
}
if (result_114 == NULL) {
free_tree(result_111, IS_CACHED);
free_tree(result_112, IS_CACHED);
free_tree(result_113, IS_CACHED);
goto exit_110;
}
current_position_110 = result_114->end;
uint32_t start_115 = current_position_110;
rnode_t* result_115 = NULL;
rnode_t* result_115_nt = call_eval(EVAL_name, state, text, text_length, start_115);
if (result_115_nt) {
result_115 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_115->flags = DO_CAPTURE | 0;
result_115->type = NONTERMINAL_T;
result_115->start = start_115;
result_115->end = result_115_nt->end;
result_115->num_children = 1;
result_115->children[0] = result_115_nt;
result_115->id = 115;
}
if (result_115 == NULL) {
free_tree(result_111, IS_CACHED);
free_tree(result_112, IS_CACHED);
free_tree(result_113, IS_CACHED);
free_tree(result_114, IS_CACHED);
goto exit_110;
}
current_position_110 = result_115->end;
result_110 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 5);
result_110->flags = SEMANTIC_ACTION | 0;
result_110->type = SEQUENCE_T;
result_110->start = start_110;
result_110->end = result_115->end;
result_110->num_children = 5;
result_110->children[0] = result_111;
result_110->children[1] = result_112;
result_110->children[2] = result_113;
result_110->children[3] = result_114;
result_110->children[4] = result_115;
result_110->id = 110;
exit_110:
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
uint32_t start_116 = start_109;
rnode_t* result_116 = NULL;
rnode_t* result_116_nt = call_eval(EVAL_name, state, text, text_length, start_116);
if (result_116_nt) {
result_116 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 1);
result_116->flags = DO_CAPTURE | SEMANTIC_ACTION | 0;
result_116->type = NONTERMINAL_T;
result_116->start = start_116;
result_116->end = result_116_nt->end;
result_116->num_children = 1;
result_116->children[0] = result_116_nt;
result_116->id = 116;
}
if (result_116 != NULL) {
result_109 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_109->flags = 0;
result_109->type = ALTERNATIVE_T;
result_109->start = start_109;
result_109->end = result_116->end;
result_109->num_children = 1;
result_109->children[0] = result_116;
result_109->id = 109;
goto exit_109;
}
exit_109:
return result_109;
}
rnode_t* eval_literal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_117 = pos;
rnode_t* result_117 = NULL;
uint32_t current_position_117 = start_117;
uint32_t start_118 = current_position_117;
rnode_t* result_118 = NULL;
uint8_t bytesbuf_118[] = {34, };
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
goto exit_117;
}
current_position_117 = result_118->end;
uint32_t start_119 = current_position_117;
rnode_t* result_119 = NULL;
uint32_t start_120 = start_119;
rnode_t* result_120 = NULL;
uint32_t num_children_119 = 0;
arraylist_t* list_119 = init_arraylist(64);
do {
result_120 = NULL;
uint32_t start_121 = start_120;
rnode_t* result_121 = NULL;
uint32_t current_position_121 = start_121;
uint32_t start_122 = current_position_121;
rnode_t* result_122 = NULL;
uint32_t start_123 = start_122;
rnode_t* result_123 = NULL;
uint8_t bytesbuf_123[] = {92, };
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
if (result_123) {
result_122 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_122->flags = 0;
result_122->type = AND_T;
result_122->start = start_122;
result_122->end = start_122;
result_122->num_children = 1;
result_122->children[0] = result_123;
result_122->id = 122;
}
if (result_122 == NULL) {
goto exit_121;
}
current_position_121 = result_122->end;
uint32_t start_124 = current_position_121;
rnode_t* result_124 = NULL;
if (start_124 < text_length) {
uint8_t c_124 = text[start_124];
if (c_124 >= 0 && c_124 <= 255) {
result_124 = malloc(sizeof(rnode_t));
result_124->flags = 0;
result_124->type = RANGE_T;
result_124->start = start_124;
result_124->end = start_124 + 1;
result_124->num_children = 0;
result_124->id = 124;
}
}
if (result_124 == NULL) {
free_tree(result_122, IS_CACHED);
goto exit_121;
}
current_position_121 = result_124->end;
uint32_t start_125 = current_position_121;
rnode_t* result_125 = NULL;
if (start_125 < text_length) {
uint8_t c_125 = text[start_125];
if (c_125 >= 0 && c_125 <= 255) {
result_125 = malloc(sizeof(rnode_t));
result_125->flags = 0;
result_125->type = RANGE_T;
result_125->start = start_125;
result_125->end = start_125 + 1;
result_125->num_children = 0;
result_125->id = 125;
}
}
if (result_125 == NULL) {
free_tree(result_122, IS_CACHED);
free_tree(result_124, IS_CACHED);
goto exit_121;
}
current_position_121 = result_125->end;
result_121 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_121->flags = 0;
result_121->type = SEQUENCE_T;
result_121->start = start_121;
result_121->end = result_125->end;
result_121->num_children = 3;
result_121->children[0] = result_122;
result_121->children[1] = result_124;
result_121->children[2] = result_125;
result_121->id = 121;
exit_121:
if (result_121 != NULL) {
result_120 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_120->flags = 0;
result_120->type = ALTERNATIVE_T;
result_120->start = start_120;
result_120->end = result_121->end;
result_120->num_children = 1;
result_120->children[0] = result_121;
result_120->id = 120;
goto exit_120;
}
uint32_t start_126 = start_120;
rnode_t* result_126 = NULL;
uint32_t current_position_126 = start_126;
uint32_t start_127 = current_position_126;
rnode_t* result_127 = NULL;
uint32_t start_128 = start_127;
rnode_t* result_128 = NULL;
uint8_t bytesbuf_128[] = {34, };
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
if (!result_128) {
result_127 = malloc(sizeof(rnode_t));
result_127->flags = 0;
result_127->type = NOT_T;
result_127->start = start_127;
result_127->end = start_127;
result_127->num_children = 0;
result_127->id = 127;
} else {
free_tree(result_128, IS_CACHED);
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
result_126 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_126->flags = 0;
result_126->type = SEQUENCE_T;
result_126->start = start_126;
result_126->end = result_129->end;
result_126->num_children = 2;
result_126->children[0] = result_127;
result_126->children[1] = result_129;
result_126->id = 126;
exit_126:
if (result_126 != NULL) {
result_120 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_120->flags = 0;
result_120->type = ALTERNATIVE_T;
result_120->start = start_120;
result_120->end = result_126->end;
result_120->num_children = 1;
result_120->children[0] = result_126;
result_120->id = 120;
goto exit_120;
}
exit_120:
if (result_120 != NULL) {
    append_arraylist(&list_119, result_120);
    start_120 = result_120->end;
    ++num_children_119;
}
} while (result_120 != NULL);
result_119 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_119);
result_119->flags = DO_CAPTURE | 0;
result_119->type = STAR_T;
result_119->start = start_119;
result_119->num_children = num_children_119;
if (num_children_119) {
for (uint32_t i = 0; i < num_children_119; ++i) {
result_119->children[i] = list_119->arr[i];
}
result_119->end = ((rnode_t*)list_119->arr[num_children_119 - 1])->end;
} else {
result_119->end = start_119;
}
result_119->id = 119;
free(list_119);
if (result_119 == NULL) {
free_tree(result_118, IS_CACHED);
goto exit_117;
}
current_position_117 = result_119->end;
uint32_t start_130 = current_position_117;
rnode_t* result_130 = NULL;
uint8_t bytesbuf_130[] = {34, };
uint8_t c_130;
for (uint32_t i_130 = 0; i_130 < 1; ++i_130) {
c_130 = bytesbuf_130[i_130];
if (i_130 + start_130 < text_length
    && c_130 == text[i_130 + start_130]) {
if (i_130 == 1 - 1) {
result_130 = malloc(sizeof(rnode_t));
result_130->flags = 0;
result_130->type = LITERAL_T;
result_130->start = start_130;
result_130->end = start_130 + 1;
result_130->num_children = 0;
result_130->id = 130;
}
} else {
break;
}
}
if (result_130 == NULL) {
free_tree(result_118, IS_CACHED);
free_tree(result_119, IS_CACHED);
goto exit_117;
}
current_position_117 = result_130->end;
result_117 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_117->flags = SEMANTIC_ACTION | 0;
result_117->type = SEQUENCE_T;
result_117->start = start_117;
result_117->end = result_130->end;
result_117->num_children = 3;
result_117->children[0] = result_118;
result_117->children[1] = result_119;
result_117->children[2] = result_130;
result_117->id = 117;
exit_117:
return result_117;
}
rnode_t* eval_cclass(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_131 = pos;
rnode_t* result_131 = NULL;
uint32_t current_position_131 = start_131;
uint32_t start_132 = current_position_131;
rnode_t* result_132 = NULL;
uint8_t bytesbuf_132[] = {91, };
uint8_t c_132;
for (uint32_t i_132 = 0; i_132 < 1; ++i_132) {
c_132 = bytesbuf_132[i_132];
if (i_132 + start_132 < text_length
    && c_132 == text[i_132 + start_132]) {
if (i_132 == 1 - 1) {
result_132 = malloc(sizeof(rnode_t));
result_132->flags = 0;
result_132->type = LITERAL_T;
result_132->start = start_132;
result_132->end = start_132 + 1;
result_132->num_children = 0;
result_132->id = 132;
}
} else {
break;
}
}
if (result_132 == NULL) {
goto exit_131;
}
current_position_131 = result_132->end;
uint32_t start_133 = current_position_131;
rnode_t* result_133 = NULL;
uint32_t start_134 = start_133;
rnode_t* result_134 = NULL;
uint32_t num_children_133 = 0;
arraylist_t* list_133 = init_arraylist(64);
do {
result_134 = NULL;
uint32_t start_135 = start_134;
rnode_t* result_135 = NULL;
uint32_t current_position_135 = start_135;
uint32_t start_136 = current_position_135;
rnode_t* result_136 = NULL;
uint32_t start_137 = start_136;
rnode_t* result_137 = NULL;
uint8_t bytesbuf_137[] = {92, };
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
if (result_137) {
result_136 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_136->flags = 0;
result_136->type = AND_T;
result_136->start = start_136;
result_136->end = start_136;
result_136->num_children = 1;
result_136->children[0] = result_137;
result_136->id = 136;
}
if (result_136 == NULL) {
goto exit_135;
}
current_position_135 = result_136->end;
uint32_t start_138 = current_position_135;
rnode_t* result_138 = NULL;
if (start_138 < text_length) {
uint8_t c_138 = text[start_138];
if (c_138 >= 0 && c_138 <= 255) {
result_138 = malloc(sizeof(rnode_t));
result_138->flags = 0;
result_138->type = RANGE_T;
result_138->start = start_138;
result_138->end = start_138 + 1;
result_138->num_children = 0;
result_138->id = 138;
}
}
if (result_138 == NULL) {
free_tree(result_136, IS_CACHED);
goto exit_135;
}
current_position_135 = result_138->end;
uint32_t start_139 = current_position_135;
rnode_t* result_139 = NULL;
if (start_139 < text_length) {
uint8_t c_139 = text[start_139];
if (c_139 >= 0 && c_139 <= 255) {
result_139 = malloc(sizeof(rnode_t));
result_139->flags = 0;
result_139->type = RANGE_T;
result_139->start = start_139;
result_139->end = start_139 + 1;
result_139->num_children = 0;
result_139->id = 139;
}
}
if (result_139 == NULL) {
free_tree(result_136, IS_CACHED);
free_tree(result_138, IS_CACHED);
goto exit_135;
}
current_position_135 = result_139->end;
result_135 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_135->flags = 0;
result_135->type = SEQUENCE_T;
result_135->start = start_135;
result_135->end = result_139->end;
result_135->num_children = 3;
result_135->children[0] = result_136;
result_135->children[1] = result_138;
result_135->children[2] = result_139;
result_135->id = 135;
exit_135:
if (result_135 != NULL) {
result_134 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_134->flags = 0;
result_134->type = ALTERNATIVE_T;
result_134->start = start_134;
result_134->end = result_135->end;
result_134->num_children = 1;
result_134->children[0] = result_135;
result_134->id = 134;
goto exit_134;
}
uint32_t start_140 = start_134;
rnode_t* result_140 = NULL;
uint32_t current_position_140 = start_140;
uint32_t start_141 = current_position_140;
rnode_t* result_141 = NULL;
uint32_t start_142 = start_141;
rnode_t* result_142 = NULL;
uint8_t bytesbuf_142[] = {93, };
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
if (!result_142) {
result_141 = malloc(sizeof(rnode_t));
result_141->flags = 0;
result_141->type = NOT_T;
result_141->start = start_141;
result_141->end = start_141;
result_141->num_children = 0;
result_141->id = 141;
} else {
free_tree(result_142, IS_CACHED);
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
result_140 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_140->flags = 0;
result_140->type = SEQUENCE_T;
result_140->start = start_140;
result_140->end = result_143->end;
result_140->num_children = 2;
result_140->children[0] = result_141;
result_140->children[1] = result_143;
result_140->id = 140;
exit_140:
if (result_140 != NULL) {
result_134 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_134->flags = 0;
result_134->type = ALTERNATIVE_T;
result_134->start = start_134;
result_134->end = result_140->end;
result_134->num_children = 1;
result_134->children[0] = result_140;
result_134->id = 134;
goto exit_134;
}
exit_134:
if (result_134 != NULL) {
    append_arraylist(&list_133, result_134);
    start_134 = result_134->end;
    ++num_children_133;
}
} while (result_134 != NULL);
result_133 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_133);
result_133->flags = DO_CAPTURE | 0;
result_133->type = STAR_T;
result_133->start = start_133;
result_133->num_children = num_children_133;
if (num_children_133) {
for (uint32_t i = 0; i < num_children_133; ++i) {
result_133->children[i] = list_133->arr[i];
}
result_133->end = ((rnode_t*)list_133->arr[num_children_133 - 1])->end;
} else {
result_133->end = start_133;
}
result_133->id = 133;
free(list_133);
if (result_133 == NULL) {
free_tree(result_132, IS_CACHED);
goto exit_131;
}
current_position_131 = result_133->end;
uint32_t start_144 = current_position_131;
rnode_t* result_144 = NULL;
uint8_t bytesbuf_144[] = {93, };
uint8_t c_144;
for (uint32_t i_144 = 0; i_144 < 1; ++i_144) {
c_144 = bytesbuf_144[i_144];
if (i_144 + start_144 < text_length
    && c_144 == text[i_144 + start_144]) {
if (i_144 == 1 - 1) {
result_144 = malloc(sizeof(rnode_t));
result_144->flags = 0;
result_144->type = LITERAL_T;
result_144->start = start_144;
result_144->end = start_144 + 1;
result_144->num_children = 0;
result_144->id = 144;
}
} else {
break;
}
}
if (result_144 == NULL) {
free_tree(result_132, IS_CACHED);
free_tree(result_133, IS_CACHED);
goto exit_131;
}
current_position_131 = result_144->end;
result_131 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_131->flags = SEMANTIC_ACTION | 0;
result_131->type = SEQUENCE_T;
result_131->start = start_131;
result_131->end = result_144->end;
result_131->num_children = 3;
result_131->children[0] = result_132;
result_131->children[1] = result_133;
result_131->children[2] = result_144;
result_131->id = 131;
exit_131:
return result_131;
}
rnode_t* eval_dot(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_145 = pos;
rnode_t* result_145 = NULL;
uint8_t bytesbuf_145[] = {46, };
uint8_t c_145;
for (uint32_t i_145 = 0; i_145 < 1; ++i_145) {
c_145 = bytesbuf_145[i_145];
if (i_145 + start_145 < text_length
    && c_145 == text[i_145 + start_145]) {
if (i_145 == 1 - 1) {
result_145 = malloc(sizeof(rnode_t));
result_145->flags = SEMANTIC_ACTION | 0;
result_145->type = LITERAL_T;
result_145->start = start_145;
result_145->end = start_145 + 1;
result_145->num_children = 0;
result_145->id = 145;
}
} else {
break;
}
}
return result_145;
}
rnode_t* eval_code(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos) {
uint32_t start_146 = pos;
rnode_t* result_146 = NULL;
uint32_t current_position_146 = start_146;
uint32_t start_147 = current_position_146;
rnode_t* result_147 = NULL;
uint8_t bytesbuf_147[] = {123, 123, };
uint8_t c_147;
for (uint32_t i_147 = 0; i_147 < 2; ++i_147) {
c_147 = bytesbuf_147[i_147];
if (i_147 + start_147 < text_length
    && c_147 == text[i_147 + start_147]) {
if (i_147 == 2 - 1) {
result_147 = malloc(sizeof(rnode_t));
result_147->flags = 0;
result_147->type = LITERAL_T;
result_147->start = start_147;
result_147->end = start_147 + 2;
result_147->num_children = 0;
result_147->id = 147;
}
} else {
break;
}
}
if (result_147 == NULL) {
goto exit_146;
}
current_position_146 = result_147->end;
uint32_t start_148 = current_position_146;
rnode_t* result_148 = NULL;
uint32_t start_149 = start_148;
rnode_t* result_149 = NULL;
uint32_t num_children_148 = 0;
arraylist_t* list_148 = init_arraylist(64);
do {
result_149 = NULL;
uint32_t start_150 = start_149;
rnode_t* result_150 = NULL;
uint32_t current_position_150 = start_150;
uint32_t start_151 = current_position_150;
rnode_t* result_151 = NULL;
uint32_t start_152 = start_151;
rnode_t* result_152 = NULL;
uint8_t bytesbuf_152[] = {92, };
uint8_t c_152;
for (uint32_t i_152 = 0; i_152 < 1; ++i_152) {
c_152 = bytesbuf_152[i_152];
if (i_152 + start_152 < text_length
    && c_152 == text[i_152 + start_152]) {
if (i_152 == 1 - 1) {
result_152 = malloc(sizeof(rnode_t));
result_152->flags = 0;
result_152->type = LITERAL_T;
result_152->start = start_152;
result_152->end = start_152 + 1;
result_152->num_children = 0;
result_152->id = 152;
}
} else {
break;
}
}
if (result_152) {
result_151 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_151->flags = 0;
result_151->type = AND_T;
result_151->start = start_151;
result_151->end = start_151;
result_151->num_children = 1;
result_151->children[0] = result_152;
result_151->id = 151;
}
if (result_151 == NULL) {
goto exit_150;
}
current_position_150 = result_151->end;
uint32_t start_153 = current_position_150;
rnode_t* result_153 = NULL;
if (start_153 < text_length) {
uint8_t c_153 = text[start_153];
if (c_153 >= 0 && c_153 <= 255) {
result_153 = malloc(sizeof(rnode_t));
result_153->flags = 0;
result_153->type = RANGE_T;
result_153->start = start_153;
result_153->end = start_153 + 1;
result_153->num_children = 0;
result_153->id = 153;
}
}
if (result_153 == NULL) {
free_tree(result_151, IS_CACHED);
goto exit_150;
}
current_position_150 = result_153->end;
uint32_t start_154 = current_position_150;
rnode_t* result_154 = NULL;
if (start_154 < text_length) {
uint8_t c_154 = text[start_154];
if (c_154 >= 0 && c_154 <= 255) {
result_154 = malloc(sizeof(rnode_t));
result_154->flags = 0;
result_154->type = RANGE_T;
result_154->start = start_154;
result_154->end = start_154 + 1;
result_154->num_children = 0;
result_154->id = 154;
}
}
if (result_154 == NULL) {
free_tree(result_151, IS_CACHED);
free_tree(result_153, IS_CACHED);
goto exit_150;
}
current_position_150 = result_154->end;
result_150 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_150->flags = 0;
result_150->type = SEQUENCE_T;
result_150->start = start_150;
result_150->end = result_154->end;
result_150->num_children = 3;
result_150->children[0] = result_151;
result_150->children[1] = result_153;
result_150->children[2] = result_154;
result_150->id = 150;
exit_150:
if (result_150 != NULL) {
result_149 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_149->flags = 0;
result_149->type = ALTERNATIVE_T;
result_149->start = start_149;
result_149->end = result_150->end;
result_149->num_children = 1;
result_149->children[0] = result_150;
result_149->id = 149;
goto exit_149;
}
uint32_t start_155 = start_149;
rnode_t* result_155 = NULL;
uint32_t current_position_155 = start_155;
uint32_t start_156 = current_position_155;
rnode_t* result_156 = NULL;
uint32_t start_157 = start_156;
rnode_t* result_157 = NULL;
uint8_t bytesbuf_157[] = {125, 125, };
uint8_t c_157;
for (uint32_t i_157 = 0; i_157 < 2; ++i_157) {
c_157 = bytesbuf_157[i_157];
if (i_157 + start_157 < text_length
    && c_157 == text[i_157 + start_157]) {
if (i_157 == 2 - 1) {
result_157 = malloc(sizeof(rnode_t));
result_157->flags = 0;
result_157->type = LITERAL_T;
result_157->start = start_157;
result_157->end = start_157 + 2;
result_157->num_children = 0;
result_157->id = 157;
}
} else {
break;
}
}
if (!result_157) {
result_156 = malloc(sizeof(rnode_t));
result_156->flags = 0;
result_156->type = NOT_T;
result_156->start = start_156;
result_156->end = start_156;
result_156->num_children = 0;
result_156->id = 156;
} else {
free_tree(result_157, IS_CACHED);
}
if (result_156 == NULL) {
goto exit_155;
}
current_position_155 = result_156->end;
uint32_t start_158 = current_position_155;
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
free_tree(result_156, IS_CACHED);
goto exit_155;
}
current_position_155 = result_158->end;
result_155 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 2);
result_155->flags = 0;
result_155->type = SEQUENCE_T;
result_155->start = start_155;
result_155->end = result_158->end;
result_155->num_children = 2;
result_155->children[0] = result_156;
result_155->children[1] = result_158;
result_155->id = 155;
exit_155:
if (result_155 != NULL) {
result_149 = malloc(sizeof(rnode_t) + sizeof(rnode_t*));
result_149->flags = 0;
result_149->type = ALTERNATIVE_T;
result_149->start = start_149;
result_149->end = result_155->end;
result_149->num_children = 1;
result_149->children[0] = result_155;
result_149->id = 149;
goto exit_149;
}
exit_149:
if (result_149 != NULL) {
    append_arraylist(&list_148, result_149);
    start_149 = result_149->end;
    ++num_children_148;
}
} while (result_149 != NULL);
result_148 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * num_children_148);
result_148->flags = 0;
result_148->type = STAR_T;
result_148->start = start_148;
result_148->num_children = num_children_148;
if (num_children_148) {
for (uint32_t i = 0; i < num_children_148; ++i) {
result_148->children[i] = list_148->arr[i];
}
result_148->end = ((rnode_t*)list_148->arr[num_children_148 - 1])->end;
} else {
result_148->end = start_148;
}
result_148->id = 148;
free(list_148);
if (result_148 == NULL) {
free_tree(result_147, IS_CACHED);
goto exit_146;
}
current_position_146 = result_148->end;
uint32_t start_159 = current_position_146;
rnode_t* result_159 = NULL;
uint8_t bytesbuf_159[] = {125, 125, };
uint8_t c_159;
for (uint32_t i_159 = 0; i_159 < 2; ++i_159) {
c_159 = bytesbuf_159[i_159];
if (i_159 + start_159 < text_length
    && c_159 == text[i_159 + start_159]) {
if (i_159 == 2 - 1) {
result_159 = malloc(sizeof(rnode_t));
result_159->flags = 0;
result_159->type = LITERAL_T;
result_159->start = start_159;
result_159->end = start_159 + 2;
result_159->num_children = 0;
result_159->id = 159;
}
} else {
break;
}
}
if (result_159 == NULL) {
free_tree(result_147, IS_CACHED);
free_tree(result_148, IS_CACHED);
goto exit_146;
}
current_position_146 = result_159->end;
result_146 = malloc(sizeof(rnode_t) + sizeof(rnode_t*) * 3);
result_146->flags = 0;
result_146->type = SEQUENCE_T;
result_146->start = start_146;
result_146->end = result_159->end;
result_146->num_children = 3;
result_146->children[0] = result_147;
result_146->children[1] = result_148;
result_146->children[2] = result_159;
result_146->id = 146;
exit_146:
return result_146;
}
#define c(x) (((capture_t*)get_arraylist(context->capture, x))->str)
#define s(x) (((capture_t*)get_arraylist(context->capture, x))->start)
#define e(x) (((capture_t*)get_arraylist(context->capture, x))->end)
#define ccount (context->capture->len)
void semantic_action_0(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** r = (ast_node_t**)(context->alias[4]->arr);
uint32_t countr = context->alias[4]->len;
{{ result = ast_grammar(r, countr); }}
context->result = result;
return;
}
void semantic_action_16(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** b = (ast_node_t**)(context->alias[22]->arr);
uint32_t countb = context->alias[22]->len;
{{
  result = ast_rule(c(0), *b);
}}
context->result = result;
return;
}
void semantic_action_29(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[29]->arr);
uint32_t counto = context->alias[29]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_30(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** first = (ast_node_t**)(context->alias[31]->arr);
uint32_t countfirst = context->alias[31]->len;
ast_node_t** rest = (ast_node_t**)(context->alias[37]->arr);
uint32_t countrest = context->alias[37]->len;
{{
  result = ast_Alt(first, rest, countrest + 1);
}}
context->result = result;
return;
}
void semantic_action_38(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** first = (ast_node_t**)(context->alias[39]->arr);
uint32_t countfirst = context->alias[39]->len;
ast_node_t** rest = (ast_node_t**)(context->alias[43]->arr);
uint32_t countrest = context->alias[43]->len;
{{
  result = ast_Seq(first, rest, countrest + 1);
}}
context->result = result;
return;
}
void semantic_action_45(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[46]->arr);
uint32_t counto = context->alias[46]->len;
{{
  if (ccount) { result = ast_with_code(c(0), *o); } else { result = *o; }
}}
context->result = result;
return;
}
void semantic_action_51(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[52]->arr);
uint32_t counto = context->alias[52]->len;
{{
  if (ccount) { result = ast_with_code(c(0), *o); } else { result = *o; }
}}
context->result = result;
return;
}
void semantic_action_57(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[58]->arr);
uint32_t counto = context->alias[58]->len;
{{
  if (ccount) { result = ast_with_code(c(0), *o); } else { result = *o; }
}}
context->result = result;
return;
}
void semantic_action_64(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[67]->arr);
uint32_t counto = context->alias[67]->len;
{{ result = ast_And(*o); }}
context->result = result;
return;
}
void semantic_action_68(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[71]->arr);
uint32_t counto = context->alias[71]->len;
{{ result = ast_Not(*o); }}
context->result = result;
return;
}
void semantic_action_75(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[76]->arr);
uint32_t counto = context->alias[76]->len;
{{ result = ast_Star(*o); }}
context->result = result;
return;
}
void semantic_action_79(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[80]->arr);
uint32_t counto = context->alias[80]->len;
{{ result = ast_Plus(*o); }}
context->result = result;
return;
}
void semantic_action_83(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[84]->arr);
uint32_t counto = context->alias[84]->len;
{{ result = ast_Option(*o); }}
context->result = result;
return;
}
void semantic_action_91(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[94]->arr);
uint32_t counto = context->alias[94]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_97(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[100]->arr);
uint32_t counto = context->alias[100]->len;
{{ result = ast_Capture(*o); }}
context->result = result;
return;
}
void semantic_action_103(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[103]->arr);
uint32_t counto = context->alias[103]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_105(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[105]->arr);
uint32_t counto = context->alias[105]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_106(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[106]->arr);
uint32_t counto = context->alias[106]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_107(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[107]->arr);
uint32_t counto = context->alias[107]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_108(context_t* context) {
ast_node_t* result = NULL;
ast_node_t** o = (ast_node_t**)(context->alias[108]->arr);
uint32_t counto = context->alias[108]->len;
{{ result = *o; }}
context->result = result;
return;
}
void semantic_action_110(context_t* context) {
ast_node_t* result = NULL;
{{
  result = ast_AliasedNontm(c(1), c(0));
}}
context->result = result;
return;
}
void semantic_action_116(context_t* context) {
ast_node_t* result = NULL;
{{
  result = ast_Nontm(c(0));
}}
context->result = result;
return;
}
void semantic_action_117(context_t* context) {
ast_node_t* result = NULL;
{{
  result = ast_Literal(c(0));
}}
context->result = result;
return;
}
void semantic_action_131(context_t* context) {
ast_node_t* result = NULL;
{{
  result = ast_CClass(c(0));
}}
context->result = result;
return;
}
void semantic_action_145(context_t* context) {
ast_node_t* result = NULL;
{{ result = ast_dot(); }}
context->result = result;
return;
}
