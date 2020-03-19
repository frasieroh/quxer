#include <inttypes.h>
#include "internal.h"
rnode_t* eval_grammar(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_ws(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_wsp(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_rule(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_name(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_body(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_alt(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_seq(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_operator(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_prefix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_and(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_not(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_postfix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_star(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_plus(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_option(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_group(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_final(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_nonterminal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_literal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_cclass(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_dot(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_code(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
void semantic_action_0(context_t* context);
void alias_allocs_0(context_t* context);
void semantic_action_18(context_t* context);
void alias_allocs_18(context_t* context);
void semantic_action_31(context_t* context);
void alias_allocs_31(context_t* context);
void semantic_action_32(context_t* context);
void alias_allocs_32(context_t* context);
void semantic_action_40(context_t* context);
void alias_allocs_40(context_t* context);
void semantic_action_47(context_t* context);
void semantic_action_53(context_t* context);
void semantic_action_59(context_t* context);
void alias_allocs_47(context_t* context);
void alias_allocs_53(context_t* context);
void alias_allocs_59(context_t* context);
void semantic_action_66(context_t* context);
void semantic_action_70(context_t* context);
void alias_allocs_66(context_t* context);
void alias_allocs_70(context_t* context);
void semantic_action_77(context_t* context);
void semantic_action_81(context_t* context);
void semantic_action_85(context_t* context);
void alias_allocs_77(context_t* context);
void alias_allocs_81(context_t* context);
void alias_allocs_85(context_t* context);
void semantic_action_93(context_t* context);
void semantic_action_99(context_t* context);
void semantic_action_105(context_t* context);
void alias_allocs_93(context_t* context);
void alias_allocs_99(context_t* context);
void alias_allocs_105(context_t* context);
void semantic_action_107(context_t* context);
void semantic_action_108(context_t* context);
void semantic_action_109(context_t* context);
void semantic_action_110(context_t* context);
void alias_allocs_107(context_t* context);
void alias_allocs_108(context_t* context);
void alias_allocs_109(context_t* context);
void alias_allocs_110(context_t* context);
void semantic_action_112(context_t* context);
void semantic_action_118(context_t* context);
void alias_allocs_112(context_t* context);
void alias_allocs_118(context_t* context);
void semantic_action_119(context_t* context);
void alias_allocs_119(context_t* context);
void semantic_action_133(context_t* context);
void alias_allocs_133(context_t* context);
void semantic_action_147(context_t* context);
void alias_allocs_147(context_t* context);
