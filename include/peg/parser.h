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
rnode_t* eval_code(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_dot(memo_state_t* state, uint8_t* text,
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
void semantic_action_54(context_t* context);
void semantic_action_61(context_t* context);
void alias_allocs_47(context_t* context);
void alias_allocs_54(context_t* context);
void alias_allocs_61(context_t* context);
void semantic_action_69(context_t* context);
void semantic_action_73(context_t* context);
void alias_allocs_69(context_t* context);
void alias_allocs_73(context_t* context);
void semantic_action_80(context_t* context);
void semantic_action_84(context_t* context);
void semantic_action_88(context_t* context);
void alias_allocs_80(context_t* context);
void alias_allocs_84(context_t* context);
void alias_allocs_88(context_t* context);
void semantic_action_96(context_t* context);
void semantic_action_102(context_t* context);
void semantic_action_108(context_t* context);
void alias_allocs_96(context_t* context);
void alias_allocs_102(context_t* context);
void alias_allocs_108(context_t* context);
void semantic_action_110(context_t* context);
void semantic_action_111(context_t* context);
void semantic_action_112(context_t* context);
void semantic_action_113(context_t* context);
void alias_allocs_110(context_t* context);
void alias_allocs_111(context_t* context);
void alias_allocs_112(context_t* context);
void alias_allocs_113(context_t* context);
void semantic_action_115(context_t* context);
void semantic_action_121(context_t* context);
void alias_allocs_115(context_t* context);
void alias_allocs_121(context_t* context);
void semantic_action_122(context_t* context);
void alias_allocs_122(context_t* context);
void semantic_action_136(context_t* context);
void alias_allocs_136(context_t* context);
void semantic_action_164(context_t* context);
void alias_allocs_164(context_t* context);
